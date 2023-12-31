//======================================================================
//文件名称：gpio.s
//功能概要：STM32L432RC GPIO底层驱动构件（汇编）程序文件
//版权所有：苏州大学嵌入式与物联网研究中心(sumcu.suda.edu.cn)
//更新记录：2019-09-27 V2.0
//======================================================================

.include "gpio.inc"

//定义代码存储text段开始，实际代码存储在Flash中
.section   .text
.syntax unified           		  //指示下方指令为ARM和thumb通用格式
.thumb                    		  //Thumb指令集
.align 2                          //指令和数据采用2字节对齐，兼容Thumb指令集

//-----------------------以下为内部函数存放处---------------------------------
//======================================================================
//函数名称：gpio_port_pin_resolution
//函数返回：无
//参数说明：r0：端口号|引脚号,例:(PTB_NUM|(5u))表示B口5脚,头文件中有宏定义
//功能概要：将传进参数r0进行解析，得出具体端口号与引脚号（如：PORTB|(5)
//          解析为PORTB与5，并将其分别赋值给r0与r1）。
//======================================================================
gpio_port_pin_resolution:
//（1）保存现场
      push {lr}             //lr进栈（lr中为进入中断前pc的值）
//（2）解析入口参数r0：端口号|引脚号，得到具体端口号和引脚号，并将其分别赋值给r0与r1
      mov r4,r0             //r4=r0=端口号|引脚号
      mov r5,r0             //r5=r0=端口号|引脚号
      lsr r4,#8             //逻辑左移获得端口号，r4=端口号
      mov r0,r4             //r0=r4=端口号
      mov r6,#0x000000ff
      and r5,r6             //r5=引脚号
      mov r1,r5             //r1=r5=引脚号
//（3）恢复现场
      pop {pc}              //恢复现场，lr出栈到pc（即子程序返回）
//======================================================================
//-----------------------内部函数结束-----------------------------------------

//---------------------以下为外部接口函数------------------------------------
//======================================================================
// 函数名称：gpio_init
// 函数返回：无
// 参数说明：r0:(端口号|(引脚号)),例:(PTB_NUM|(5u))表示B口5脚,头文件中有宏定义
//           r1:引脚方向（0=输入,1=输出,可用引脚方向宏定义）
//           r2:端口引脚初始状态（0=低电平，1=高电平）
// 功能概要：初始化指定端口引脚作为GPIO引脚功能，并定义为输入或输出。若是输出，
//           还指定初始状态是低电平或高电平
// 备    注：端口x的每个引脚控制寄存器PORTx_PCRn的地址=PORT_PCR_BASE+x*0x1000+n*4
//           其中:x=0~4，对应A~E;n=0~31
//======================================================================
.type gpio_init function          //声明gpio_init为函数类型                     
.global gpio_init                 //将gpio_init定义成全局函数，便于芯片初始化之后调用
gpio_init:
//（1）保存现场
      push {r0-r7,lr}              //保存现场，pc(lr)入栈
      //将入口参数r1、r2转存至r2、r3，预留出r1保存引脚号
      mov r3,r2                    //r3=r2=端口引脚初始状态
      mov r2,r1                    //r2=r1=引脚方向
//------------------------------------------------------------------------
//（2）调用内部函数，从入口参数r0中解析出端口号引脚号，分别放在r0和r1中
      bl gpio_port_pin_resolution  //调用内部解析函数,r0=端口号,r1=引脚号
//（3）获得待操作端口时钟的RCC->AHB2ENR寄存器的地址
      ldr r7,=RCC_AHB2ENR_BASE     //r7=RCC->AHB2ENR寄存器基地址
      ldr r5,[r7]                  //r5=RCC->AHB2ENR寄存器中的内容
      mov r6,#1                    //r6=1
      lsl r6,r6,r0                 //r6=待操作RCC->AHB2ENR掩码（为1的位由r1决定）
      orr r5,r6                    //或运算设GPIOxEN=1，GPIOx时钟使能
      str r5,[r7]                  //将r5中的GPIOxEN值更新到RCC->AHB2ENR寄存器中
//（4）获得待操作端口的GPIO寄存器的地址
      mov r7,r0                    //r7=r0=端口号
      ldr r4,=0x400                //r4=各端口基地址差值(0x400)
      mul r7,r7,r4                 //r7=待操作端口与A口的偏移地址
      ldr r4,=GPIO_BASE            //r4=端口GPIOA基地址(即GPIO_BASE)
      add r7,r4                    //r7=待操作端口GPIO寄存器的地址
      mov r4,#2                    //r4=2
      mov r6,r1                    //r6=r1=引脚号
      mul r6,r6,r4                 //r6=2*r1=待操作引脚左移量(GPIO_MODER_MODE_Pos)
      mov r4,#3                    //r4=3=GPIO_MODER_MODE_Msk
      lsl r4,r6                    //r4=待操作GPIO_MODER补码（为1的位由r1决定）
      mvn r4,r4                    //r4取反
      ldr r5,[r7]                  //r5=GPIO_MODER寄存器中的内容
      and r5,r4                    //与运算设~GPIOx_MODER，GPIOx_MODER清0
//（5）根据入口参数r2设定引脚输入输出状态
      cmp r2,#1                    //判断入口参数r2的值
      bne gpio_init_2              //若要设置为输入，转到gpio_init_2，将GPIOx_MODER相应位为00
//（5.1）若要设置为输出，继续执行，将GPIOx_MODER相应位为01
      mov r4,#1                    //r4=2
      lsl r4,r4,r6                 //r4=待操作GPIO_MODER掩码（为1的位由r1决定）
      orr r5,r4                    //或运算设GPIOx_MODER=01，引脚被配置为GPIO输出功能
      str r5,[r7]                  //将r5中的GPIOx_MODER值更新到该寄存器中
      cmp r3,#1                    //判断引脚初始状态
      bne gpio_init_1              //若为低电平，转到gpio_init_1，将BRR相应位置1
//（5.1.1）若为高电平，继续执行，将BSRR相应位置1
      mov r5,r7                    //r5=r7=待操作端口GPIO寄存器的地址
      add r5,#0x18                 //r5=待操作端口GPIO->BSRR寄存器的地址
      ldr r4,[r5]                  //r4=待操作端口GPIO->BSRR寄存器中的内容
      mov r6,#1                    //r6=1
      lsl r6,r6,r1                 //r6=待操作GPIO_BSRR掩码（为1的位由r1决定）
      orr r4,r6                    //或运算设GPIOx_BSRR=1
      str r4,[r5]                  //将r4中的GPIOx_BSRR值更新到该寄存器中
      bl  gpio_init_3              //跳转到gpio_init_2
//（5.1.2）若为低电平，转到gpio_init_1，将BRR相应位置1
gpio_init_1:
      mov r5,r7                    //r5=r7=待操作端口GPIO寄存器的地址
      add r5,#0x28                 //r5=待操作端口GPIO->BRR寄存器的地址
      ldr r4,[r5]                  //r4=待操作端口GPIO->BRR寄存器中的内容
      mov r6,#1                    //r6=1
      lsl r6,r6,r1                 //r6=待操作GPIO_BRR掩码（为1的位由r1决定）
      orr r4,r6                    //或运算设GPIOx_BRR=1
      str r4,[r5]                  //将r4中的GPIOx_BRR值更新到该寄存器中
      bl  gpio_init_3
//（5.2）若要设置为输入，转到gpio_init_2，将GPIOx_MODER相应位为00，引脚被配置为GPIO输入功能
gpio_init_2:
//（5.1）若要设置为输出，继续执行，将GPIOx_MODER相应位为01
      mov r4,#3                    //r4=2
      lsl r4,r4,r6                 //r4=待操作GPIO_MODER掩码（为1的位由r1决定）
      bic r5,r5,r4
      //and r5,r4                    //或运算设GPIOx_MODER=01，引脚被配置为GPIO输出功能
      str r5,[r7]                  //将r5中的GPIOx_MODER值更新到该寄存器中
  gpio_init_3:
//-----------------------------------------------------------------------
//（6）恢复现场
      pop {r0-r7, pc}              //恢复现场，lr出栈到pc（即子程序返回）


//=====================================================================
//函数名称：gpio_set
//函数返回：无
// 参数说明：r0:(端口号|(引脚号)),例:(PTB_NUM|(5u))表示B口5脚,头文件中有宏定义
//           r1:希望设置的端口引脚状态（0=低电平，1=高电平）
//功能概要：当指定引脚被定义为GPIO功能且为输出时，本函数设定引脚状态
// 备    注：端口x的每个引脚控制寄存器PORTx_PCRn的地址=PORT_PCR_BASE+x*0x1000+n*4
//           其中:x=0~4，对应A~E;n=0~31
//=====================================================================
.type gpio_set function           //声明gpio_set为函数类型                     
.global gpio_set               	  //将gpio_set定义成全局函数，便于芯片初始化之后调用
gpio_set:
//（1）保存现场
      push {r0-r7,lr}              //保存现场，pc(lr)入栈
      //将入口参数r1转存至r3，预留出r1保存引脚号
      mov r3,r1                    //r3=r1=端口引脚初始状态
//------------------------------------------------------------------------
//（2）从入口参数r0中解析出端口号引脚号，分别放在r0和r1中
      bl gpio_port_pin_resolution  //调用内部函数，r0=端口号,r1=引脚号
      mov r5,r0                    //r5=r0=端口号
      ldr r6,=0x400                //r6=各GPIO口的基地址差值（400h）
      mul r6,r6,r5                 //r6=待操作GPIO口与GPIOA的地址偏移
//（3）根据入口参数r3，设定引脚状态（0=低电平，1=高电平）
      cmp r3,#1                    //判断引脚初始状态
      bne gpio_set_1               //若为低电平，转到gpio_set_1，将BRR相应位置1
//（3.1）若为低电平，继续执行，将BSRR相应位置1
      ldr r5,=GPIO_BASE+0x18       //r5=第一个端口GPIO->BSRR寄存器的地址
      add r5,r6                    //r5=待操作端口GPIO->BSRR寄存器的地址
      ldr r4,[r5]                  //r4=待操作端口GPIO->BSRR寄存器中的内容
      mov r6,#1                    //r6=1
      lsl r6,r6,r1                 //r6=待操作GPIO_BSRR掩码（为1的位由r1决定）
      orr r4,r6                    //或运算设GPIOx_BSRR=1
      str r4,[r5]                  //将r4中的GPIOx_BSRR值更新到该寄存器中
      bl  gpio_set_2               //跳转到gpio_set_2
//（3.2）若为低电平，转到gpio_set_1，将GPIOx_BRR相应位置1
gpio_set_1:
      ldr r5,=GPIO_BASE+0x28       //r5=第一个端口GPIO->BRR寄存器的地址
      add r5,r6                    //r5=待操作端口GPIO->BRR寄存器的地址
      ldr r4,[r5]                  //r4=待操作端口GPIO->BRR寄存器中的内容
      mov r6,#1                    //r6=1
      lsl r6,r6,r1                 //r6=待操作GPIO_BRR掩码（为1的位由r1决定）
      orr r4,r6                    //或运算设GPIOx_BRR=1
      str r4,[r5]                  //将r4中的GPIOx_BRR值更新到该寄存器中
gpio_set_2:
//------------------------------------------------------------------------
//（4）恢复现场
      pop {r0-r7,pc}               //恢复现场，lr出栈到pc（即子程序返回）

//======================================================================
// 函数名称：gpio_reverse
// 函数返回：无
// 参数说明：r0:(端口号)|(引脚号),例:(PTB_NUM|(5u))表示B口5脚,头文件中有宏定义
// 功能概要：反转指定引脚状态
//======================================================================
.type gpio_reverse function       //声明gpio_reverse为函数类型                     
.global gpio_reverse              //将gpio_reverse定义成全局函数，便于芯片初始化之后调用
gpio_reverse:
//（1）保存现场
      push {r0-r7,lr}              //保存现场，pc(lr)入栈
//------------------------------------------------------------------------
//（2）从入口参数r0中解析出端口号引脚号，分别放在r0和r1中
      bl gpio_port_pin_resolution  //调用内部函数，r0=端口号,r1=引脚号
//（3）求待操作GPIO口的基地址（也就是PTOR的地址）
      mov r5,r0                    //r5=r0=端口号
      ldr r6,=0x400                //r6=各GPIO口的基地址差值（400h）
      mul r6,r6,r5                 //r6=待操作GPIO口与GPIOA的地址偏移
      ldr r5,=GPIO_BASE+0x14       //r5=第一个端口GPIO->ODR寄存器的地址
      add r5,r6                    //r5=待操作端口GPIO->BRR寄存器的地址
      ldr r7,[r5]                  //r7=待操作端口GPIO->BRR寄存器中的内容
      mov r4,#1                    //r4=1
      lsl r4,r4,r1                 //r4=待操作GPIO_ODR掩码（为1的位由r1决定）
      and r4,r7                    //与运算设GPIO_ODR
//（4）判断当前引脚状态
      cmp r4,#0                    //判断目前引脚输出状态
      bne gpio_reverse_1           //若为高电平，转到gpio_reverse_1，将BRR相应位置1
//（4.1）若为低电平，继续执行，将BSRR相应位置1，即将其反转为高电平
      ldr r5,=GPIO_BASE+0x18       //r5=第一个端口GPIO->BSRR寄存器的地址
      add r5,r6                    //r5=待操作端口GPIO->BSRR寄存器的地址
      ldr r4,[r5]                  //r4=待操作端口GPIO->BSRR寄存器中的内容
      mov r6,#1                    //r6=1
      lsl r6,r6,r1                 //r6=待操作GPIO_BSRR掩码（为1的位由r1决定）
      orr r4,r6                    //或运算设GPIOx_BSRR=1
      str r4,[r5]                  //将r4中的GPIOx_BSRR值更新到该寄存器中
      bl  gpio_reverse_2
//（4.2）若为高电平，转到gpio_reverse_1，将BRR相应位置1，即将其反转为低电平
gpio_reverse_1:
      ldr r5,=GPIO_BASE+0x28       //r5=第一个端口GPIO->BRR寄存器的地址
      add r5,r6                    //r5=待操作端口GPIO->BRR寄存器的地址
      ldr r4,[r5]                  //r4=待操作端口GPIO->BRR寄存器中的内容
      mov r6,#1                    //r6=1
      lsl r6,r6,r1                 //r6=待操作GPIO_BRR掩码（为1的位由r1决定）
      orr r4,r6                    //或运算设GPIOx_BRR=1
      str r4,[r5]                  //将r4中的GPIOx_BRR值更新到该寄存器中
gpio_reverse_2:
//（5）恢复现场
      pop {r0-r7,pc}               //恢复现场，lr出栈到pc（即子程序返回）
//======================================================================

//======================================================================
// 函数名称：gpio_get
// 函数返回：r2:指定端口引脚的状态（1或0）
// 参数说明：r0:(端口号)|(引脚号),例:(PTB_NUM|(5u))表示B口5脚,头文件中有宏定义
// 功能概要：当指定端口引脚被定义为GPIO功能且为输入时，本函数获取指定引脚状态
//======================================================================
.type gpio_get function           //声明gpio_get为函数类型                     
.global gpio_get               	  //将gpio_get定义成全局函数，便于芯片初始化之后调用
gpio_get:
//（1）保存现场
      push {lr}              //保存现场，pc(lr)入栈
//------------------------------------------------------------------------
//（2）从入口参数r0中解析出端口号引脚号，分别放在r0和r1中
      bl gpio_port_pin_resolution  //调用内部函数，r0=端口号,r1=引脚号
//（3）求待操作GPIO口的基地址（也就是PTOR的地址）
      mov r5,r0                    //r5=r0=端口号
      ldr r6,=0x400                //r6=各GPIO口的基地址差值（400h）
      mul r6,r6,r5                 //r6=待操作GPIO口与GPIOA的地址偏移
      ldr r5,=GPIO_BASE+0x10       //r5=第一个端口GPIO->IDR寄存器的地址
      add r5,r6                    //r5=待操作端口GPIO->IDR寄存器的地址
      ldr r7,[r5]                  //r7=待操作端口GPIO->IDR寄存器中的内容
      mov r4,#1                    //r4=1
      lsl r4,r4,r1                 //r4=待操作GPIO_IDR掩码（为1的位由r1决定）
      and r4,r7                    //与运算设GPIO_IDR
//（4）判断当前引脚状态
      cmp r4,#0                    //判断目前引脚输出状态
      bne gpio_get_1
      mov r2,#0                    //r2=指定引脚状态
      bl gpio_get_2
gpio_get_1:
      mov r2,#1                    //r2=指定引脚状态
gpio_get_2:
//------------------------------------------------------------------------
      pop {pc}               //恢复现场，lr出栈到pc（即子程序返回）
//-----------------------外部接口函数结束------------------------------------
