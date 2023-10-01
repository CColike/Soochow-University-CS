//=======================================================================================
//文件名称：main.s
//功能概要：实现将一组数进行选择排序
//版权所有：张昊
//版本更新：20220501
//=======================================================================================
.include "include.inc"    //头文件中主要定义了程序中需要使用到的一些常量
//（0）数据段与代码段的定义
//（0.1）定义数据存储data段开始，实际数据存储在RAM中
.section .data
//（0.1.1）定义需要输出的字符串，标号即为字符串首地址,\0为字符串为结束标志
hello_information:           //字符串标号
.ascii "----------------------------------------------------------------------\n"
.ascii "金葫芦提示：\n"
.ascii "    本工程实现将一组数进行选择排序，并将结果输出！    \n"
.ascii "----------------------------------------------------------------------\n\0"
string_first_2:                         //字符串标签
.string "Serial port information start\n"
uart_bef:
.string "before Sort:"	//排序前的数的提示信息
uart_aft:
.string "\nafter Sort:"	//排序后的数的提示信息
string_control:
.string "%d,"			//输出十进制数

    
    
//（0.1.2）定义变量
.align 4               //.word格式四字节对齐
mMainLoopCount:    //定义主循环次数变量
    .word 0
//（0.1.3）定义数组
//.global array,count		//声明所定义的数组和数组长度是全局变量
.section .data
.align 1

array1:					   //定义需排序的数组
    .byte 12,15,8,14,16,2,45
    .align 1
    
.equ count1,7				//count1=数组array1长度，用于记录外循环次数


    
.equ MainLoopNUM,4556677  //主循环次数设定值（常量）
    
//（0.2）定义代码存储text段开始，实际代码存储在Flash中
.section   .text
.syntax unified           		  //指示下方指令为ARM和thumb通用格式
.thumb                    		  //Thumb指令集
.type main function               //声明main为函数类型
.global main               	      //将main定义成全局函数，便于芯片初始化之后调用
.align 2                          //指令和数据采用2字节对齐，兼容Thumb指令集
    
//----------------------------------------------------------------------                        
//声明使用到的内部函数
//main.c使用的内部函数声明处
    
//----------------------------------------------------------------------
//主函数，一般情况下可以认为程序从此开始运行（实际上有启动过程，参见书稿）
main:
//（1）======启动部分（开头）主循环前的初始化工作==========================================
//（1.1）声明main函数使用的局部变量
    
//（1.2）【不变】关总中断
    cpsid i   
//（1.3）给主函数使用的局部变量赋初值
    
//（1.4）给全局变量赋初值
    
//（1.5）用户外设模块初始化
//  初始化蓝灯, r0、r1、r2是gpio_init的入口参数
    ldr r0,=LIGHT_BLUE     //r0指明端口和引脚（用=，是因为常量>=256，且要用ldr指令）
    mov r1,#GPIO_OUTPUT    //r1指明引脚方向为输出
    mov r2,#LIGHT_ON       //r2指明引脚的初始状态为亮
    bl  gpio_init          //调用gpio初始化函数
    
//（1.6）使能模块中断
    
//（1.7）【不变】开总中断
    cpsie  i  
        
    //显示金葫芦提示
    ldr r0,=hello_information      //r0=待显示字符串
    bl  printf		               //调用printf显示字符串

//bl .   //在此打桩(.表示当前地址)


    ldr r0,=string_first_2      //串口输出数据前的提示信息
    bl printf
    ldr r0,=uart_bef
    bl printf
    mov r7,#0	
//输出排序前的数组
loop_bub_bef:
    ldr r2,=array1					//r2=获取数组的首地址
    ldrb r1,[r2,r7]
    ldr r0,=string_control
    bl printf
    add r7,r7,#1			        //r7=r7+1，每次取完数后，地址+1
    ldr r6,=count1
    cmp r7,r6			            //比较r7和数组长度大小
    blt loop_bub_bef	            //若r7<数组长度，则没有输出完，则继续输出
	bge ctn
ctn:
//进行选择排序
    ldr r0,=array1
    ldr r1,=count1
    bl selectionSort_up				//调用选择排序函数
    ldr r0,=uart_aft	            //排序后的信息
    bl printf
    mov r7,#0			          //需要移动的相对地址数
    
loop_bub_aft:                     //串口输出数据提示信息前的显示标签
    ldr r2,=array1				  //r2=获取数组的首地址
    ldr r0,=string_control
    ldrb r1,[r2,r7]
    bl printf 
    add r7,r7,#1			      //r7=r7+1
    ldr r6,=count1
    cmp r7,#7
    blt loop_bub_aft	          //没有输出完，则继续输出
    bge endd
endd:
	b endd