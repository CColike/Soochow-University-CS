//======================================================================
//文件名称：user.inc
//功能概要：包含工程中用到的头文件
//版权所有：SD-ARM(sumcu.suda.edu.cn)
//版本更新：2019-09-01 V1.0
//======================================================================
.include "gpio.inc"

//指示灯端口及引脚定义
.equ LIGHT_RED,(PTB_NUM|7)    	//红色RUN灯使用的端口/引脚
.equ LIGHT_GREEN,(PTB_NUM|8)  	//绿色RUN灯使用的端口/引脚
.equ LIGHT_BLUE,(PTB_NUM|9)    	//蓝色RUN灯使用的端口/引脚

//灯状态宏定义（灯亮、灯暗对应的物理电平由硬件接法决定）
.equ LIGHT_ON,0     			//灯亮
.equ LIGHT_OFF,1    			//灯暗

//串口宏定义
//用户串口：用三芯TTL-USB串口线（接插线）：黑线-地，接着是白线（TX)，随后是绿线（RX)
.equ UART_User, 2         //TX引脚：GEC_10；RX引脚：GEC_8(实物板上标识UART0)

//宏定义相关数据
.equ DELAY_NUM,1000000  		//延时数（约1秒），控制小灯闪烁频率
.equ UART_BAUD,115200           //串口波特率

//myprintf重定义
.equ printf, myprintf

//定义原中断处理程序名【20200317】
.type  USART2_IRQHandler, function
.global USART2_IRQHandler

//定义新中断处理程序名【20200317】
.type  UART_User_Handler, function
.global UART_User_Handler

//建立新旧中断处理程序名的映射【20200317】
.equ USART2_IRQHandler,UART_User_Handler

