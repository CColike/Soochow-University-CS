	.include "include.inc" //总头文件，只包含user.inc
//（0）数据段与代码段的定义
//（0.1）定义数据存储data段开始，实际数据存储在RAM中
	.section .data
//（0.1.1）定义需要输出的字符串，标号即为字符串首地址,\0为字符串结束标志
	hello_information: //字符串标号
	.ascii "-------------------------------------------------------\n"
	.ascii " 使用GPIO点亮七种颜色的二极管\n"
	.ascii "------------------------------------------------------\n\0"
light_off:
	.asciz "LIGHT:OFF--\n" //灯暗状态提示
light_red_on:
	.asciz "LIGHT_RED:ON--\n" //红灯亮状态提示
light_green_on:
	.asciz "LIGHT_GREEN:ON--\n" //绿灯亮状态提示
light_blue_on:
	.asciz "LIGHT_BLUE:ON--\n" //蓝灯亮状态提示
light_count:
	.asciz "灯的闪烁次数mLightCount=%d\n" //闪烁次数提示
light_type:
	.asciz "灯的闪烁类型mLightType=%d\n" //闪烁类型提示
//（0.1.2）定义变量
	.align 4 //.word格式4字节对齐
	mMainLoopCount: //定义主循环次数变量
	.word 0
	mFlag: //定义灯的状态标志
	.byte 'L'
	.align 4
	mLightCount: //定义灯的闪烁次数
	.word 0
	.align 4
	mLightType: //定义灯的类型，数据格式为字，初始值为0，按照0123456顺序循环
	.word 0
	.equ MainLoopNUM,5566770 //主循环次数设定值（常量）
//（0.2）定义代码存储text段开始，实际代码存储在Flash中
	.section .text
	.syntax unified     //指示下方指令为ARM和thumb通用格式
	.thumb              //Thumb指令集
	.type main function //声明main为函数类型
	.global main        //将main定义成全局函数，便于芯片初始化之后调用
	.align 2            //指令和数据采用2字节对齐，兼容Thumb指令集
//-------------------------------------------------------------------- 
//main.c使用的内部函数声明处
//--------------------------------------------------------------------
	main: //主函数
//（1）======启动部分（开头）主循环前的初始化工作======================
//（1.1）声明main函数使用的局部变量
//（1.2）【不变】关总中断
	cpsid i 
//（1.3）给主函数使用的局部变量赋初值
//（1.4）给全局变量赋初值
//（1.5）用户外设模块初始化
//初始化红灯, r0、r1、r2是gpio_init的入口参数
	ldr r0,=LIGHT_RED //r0<-端口和引脚
	mov r1,#GPIO_OUTPUT //r1<-引脚方向为输出
	mov r2,#LIGHT_OFF //r2<-引脚的初始状态为暗
	bl gpio_init //调用gpio初始化函数
//初始化绿灯, r0、r1、r2是gpio_init的入口参数
	ldr r0,=LIGHT_GREEN //r0<-端口和引脚
	mov r1,#GPIO_OUTPUT //r1<-引脚方向为输出
	mov r2,#LIGHT_OFF //r2<-引脚的初始状态为暗
	bl gpio_init //调用gpio初始化函数
//初始化蓝灯, r0、r1、r2是gpio_init的入口参数
	ldr r0,=LIGHT_BLUE //r0<-端口和引脚
	mov r1,#GPIO_OUTPUT //r1<-引脚方向为输出
	mov r2,#LIGHT_OFF //r2<-引脚的初始状态为暗
	bl gpio_init //调用gpio初始化函数
//（1.6）使能模块中断
//（1.7）【不变】开总中断（初始化结束）
	cpsie i 
	ldr r0,=hello_information //待显示字符串首地址
	bl printf //调用printf显示字符串
//bl . //在此打桩
//（1）======启动部分（结尾）=======================================
//（2）======主循环部分（开头）=====================================
	main_loop: //主循环标签（开头）
//（2.1）主循环次数变量mMainLoopCount+1
	ldr r2,=mMainLoopCount //r2←mMainLoopCount的地址
	ldr r1, [r2] 
	add r1,#1 
	str r1,[r2] 
//（2.2）未达到主循环次数设定值，继续循环
	ldr r2,=MainLoopNUM 
	cmp r1,r2 
	blO main_loop //未达到，继续循环
//（2.3）达到主循环次数设定值，执行下列语句，进行灯的亮暗处理
//（2.3.1）清除循环次数变量 
	ldr r2,=mMainLoopCount //r2←mMainLoopCount的地址
	mov r1,#0 
	str r1,[r2] 
//（2.3.2）如灯状态标志mFlag为'L'，灯的闪烁次数+1并显示，改变灯状态及标志
//判断灯的状态标志
	ldr r2,=mFlag 
	ldr r6,[r2]
	cmp r6,#'L'
	bne main_light_off //mFlag不等于'L'，这时需要关灯
//mFlag等于'L'情况，这时需要开灯
	ldr r3,=mLightCount //灯的闪烁次数mLightCount+1
	ldr r1,[r3]
	add r1,#1
	str r1,[r3]
	ldr r0,=light_count //显示灯的闪烁次数值
	ldr r2,=mLightCount
	ldr r1,[r2]
	bl printf
	ldr r2,=mFlag //灯的状态标志改为'A'（下一步是灭灯）
	mov r7,#'A'
	str r7,[r2] 
//输出此时的灯的颜色类型
	ldr r0,=light_type //显示灯的类型mLightType
	ldr r2,=mLightType
	ldr r1,[r2]
	bl printf
//依次判断light_type枚举到哪一种灯的颜色，亮相应的灯
	ldr r2,=mLightType 
	ldr r1,[r2]  //r1<-mLightType
	cmp r1,#0
	bne light_type_1 //不等于0,跳转判断1
//light_type=0:red
	ldr r0,=LIGHT_RED //亮红灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_red_on //显示红灯亮提示
	bl printf
	b end_light_type 
light_type_1:
	ldr r2,=mLightType 
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#1
	bne light_type_2 //不等于1,跳转判断2
//light_type=1:green
	ldr r0,=LIGHT_GREEN //亮绿灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_green_on //显示绿灯亮提示
	bl printf
	b end_light_type //break
light_type_2:
	ldr r2,=mLightType
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#2
	bne light_type_3 //不等于2,跳转判断3
//light_type=2:blue
	ldr r0,=LIGHT_BLUE //亮蓝灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_blue_on //显示蓝灯亮提示
	bl printf
	b end_light_type //break
light_type_3:
	ldr r2,=mLightType 
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#3
	bne light_type_4 //不等于3,跳转判断4
//light_type=3:yellow=red+green
	ldr r0,=LIGHT_RED //亮红灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_red_on //显示红灯亮提示
	bl printf
	ldr r0,=LIGHT_GREEN //亮绿灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_green_on //显示绿灯亮提示
	bl printf
	b end_light_type //break
light_type_4:
	ldr r2,=mLightType
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#4
	bne light_type_5 //不等于4,跳转判断5
//light_type=4:purple=red+blue
	ldr r0,=LIGHT_RED //亮红灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_red_on //显示红灯亮提示
	bl printf
	ldr r0,=LIGHT_BLUE //亮蓝灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_blue_on //显示蓝灯亮提示
	bl printf
	b end_light_type //break
light_type_5:
	ldr r2,=mLightType 
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#5
	bne light_type_6 //不等于5,跳转6
//light_type=5:cyan=green+blue
	ldr r0,=LIGHT_GREEN //亮绿灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_green_on //显示绿灯亮提示
	bl printf
	ldr r0,=LIGHT_BLUE //亮蓝灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_blue_on //显示蓝灯亮提示
	bl printf
	b end_light_type //break
light_type_6:
//light_type=6:white=red+green+blue
	ldr r0,=LIGHT_RED //亮红灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_red_on //显示红灯亮提示
	bl printf
	ldr r0,=LIGHT_GREEN //亮绿灯
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_green_on //显示绿灯亮提示
	bl printf
	ldr r0,=LIGHT_BLUE //亮蓝灯
	ldr r1,=LIGHT_ON
	bl gpio_set 
	ldr r0, =light_blue_on //显示蓝灯亮提示
	bl printf
end_light_type:
//修改灯的类型mLightType+1，若mLightType>=7，mLightType=0
	ldr r3,=mLightType 
	ldr r1,[r3] //r1<-mLightType
	add r1,#1 //mLightType++
	cmp r1,#7
	blo type_not_to_zero //若mLightType>=7，mLightType=0
	mov r1,#0
	type_not_to_zero: //若mLightType<7，mLightType++后不改变
	str r1,[r3]
//mFlag等于'L'情况处理完毕，转
	b main_exit 
//（2.3.3）如灯状态标志mFlag为'A'，改变灯状态及标志，灭所有的灯
main_light_off:
	ldr r2,=mFlag //灯的状态标志改为'L'
	mov r7,#'L'
	str r7,[r2] 
	ldr r0,=LIGHT_RED //灭红灯
	ldr r1,=LIGHT_OFF
	bl gpio_set
	ldr r0,=LIGHT_GREEN //灭绿灯
	ldr r1,=LIGHT_OFF
	bl gpio_set
	ldr r0,=LIGHT_BLUE //灭蓝灯
	ldr r1,=LIGHT_OFF
	bl gpio_set
	ldr r0, =light_off //显示提示
	bl printf
main_exit:
	b main_loop //继续循环
//（2）======主循环部分（结尾）=====================================
	.end //整个程序结束标志（结尾）
	
