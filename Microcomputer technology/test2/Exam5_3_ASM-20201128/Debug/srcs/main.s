//=======================================================================================
//文件名称：main.s
//功能概要：本工程实现1~100这100个数相加，并将结果通过串口输出（利用printf输出提示信息）
//版权所有：SD-ARM(sumcu.suda.edu.cn)
//版本更新：20180810-20191022
//=======================================================================================
.include "include.inc"    //头文件中主要定义了程序中需要使用到的一些常量
//（0）数据段与代码段的定义
//（0.1）定义数据存储data段开始，实际数据存储在RAM中
.section .data
//（0.1.1）定义需要输出的字符串，标号即为字符串首地址,\0为字符串xfgi结束标志
hello_information:           //字符串标号
    .ascii "----------------------------------------------------------------------\n"
    .ascii "金葫芦提示：\n"
    .ascii "    本工程实现100以内奇数之和，运行结果如下所示！    \n"
    .ascii "----------------------------------------------------------------------\n\0"
string_result:                                 //串口输出结果前的提示信息
    .string "sum:%d\n"

//（0.1.2）定义变量
.align 4               //.word格式四字节对齐
  mMainLoopCount:		   //定义主循环次数变量
	.word 0
	
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
	ldr r0,=hello_information   //r0=待显示字符串
	bl  printf		            //调用printf显示字符串

	mov r0,#1                    //r0=1
	mov r1,#0                    //r1为sum         
add_loop:
 	and r2,r0,#1                //r2=r0%2
 	cmp r2,#0                   //判断r2是否为偶数
 	beq pass_loop               //如果为偶数，那么跳转到pass_loop，不将r0加到r1
	add r1,r1,r0                  
pass_loop:
	add r0,r0,#1
	cmp r0,#100
	bne add_loop
	ldr r0, =string_result	      //r0指明字符串
	bl  printf				      //调用printf
.end       