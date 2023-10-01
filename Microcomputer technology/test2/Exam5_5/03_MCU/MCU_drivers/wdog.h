#ifndef _IWDG_H   //防止重复定义（_IWDG_H  开头)
#define _IWDG_H

//1 头文件


//分频系数宏定义
#define IWDG_PRESCALER_4     ((uint8_t)0x00)
#define IWDG_PRESCALER_8     ((uint8_t)(IWDG_PR_PR_0))
#define IWDG_PRESCALER_16    ((uint8_t)(IWDG_PR_PR_1))
#define IWDG_PRESCALER_32    ((uint8_t)(IWDG_PR_PR_1 | IWDG_PR_PR_0))
#define IWDG_PRESCALER_64    ((uint8_t)(IWDG_PR_PR_2))
#define IWDG_PRESCALER_128   ((uint8_t)(IWDG_PR_PR_2 | IWDG_PR_PR_0))
#define IWDG_PRESCALER_256   ((uint8_t)(IWDG_PR_PR_2 | IWDG_PR_PR_1))

//KR寄存器操作指令
#define IWDG_KEY_RELOAD                    ((uint32_t)0xAAAA)  /*!< IWDG Reload Counter Enable   */
#define IWDG_KEY_ENABLE                    ((uint32_t)0xCCCC)  /*!< IWDG Peripheral Enable       */
#define IWDG_KEY_WRITE_ACCESS_ENABLE        ((uint32_t)0x5555)  /*!< IWDG KR Write Access Enable  */
#define IWDG_KEY_WRITE_ACCESS_DISABLE       ((uint32_t)0x0000)  /*!< IWDG KR Write Access Disable */


//1 头文件
#include "mcu.h"

#define TIMEOUT1   1     //32ms
#define TIMEOUT2   2     //256ms
#define TIMEOUT3   3     //1024ms

#define ENABLE_WDOG	   1      //设置是否开启看门狗

// ===========================================================================
// 函数名称：wdog_start
// 函数参数：timeout:设置重装载的时间
// 函数返回：无
// 功能概要： 启动看门狗模块
// ===========================================================================
void wdog_start(uint32_t timeout);

//=========================================================================
//函数名称：wdog_feed
//功能概要：喂狗，清看门狗计数器
//参数说明：无
//函数返回：无
//=========================================================================
void wdog_feed(void);

void wdog_stop(void);

#endif
