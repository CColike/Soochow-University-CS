//======================================================================
//文件名称：cpu.h（cpu头文件）
//制作单位：SD-Arm(sumcu.suda.edu.cn)
//更新记录：20181201-20200627
//======================================================================
#ifndef CPU_H     //防止重复定义（CPU_H 开头）
#define CPU_H

//（1）【变动】包含所有芯片头文件，因CPU不同而异
#include "cmsis_compiler.h"
#include "cmsis_gcc.h"
#include "cmsis_version.h"
#include "core_cm4.h"

//（3）【变动】复位相关
// 按键复位
#define IS_PIN_RESET_OCCURED    ((RCC->CSR & RCC_CSR_PINRSTF_Msk) \
                                 && (!(RCC->CSR & 0xFB000000)))   
// 上电复位
#define IS_POWERON_RESET          (RCC->CSR & RCC_CSR_BORRSTF_Msk)
//写1清引脚复位标志位
#define CLEAR_PIN_RESET_FLAG      (RCC->CSR |= RCC_CSR_RMVF_Msk) 
//（3）【固定】中断宏定义,若是ARM架构，则不变动
#define ENABLE_INTERRUPTS        __ASM("cpsie i")     // 开总中断()
#define DISABLE_INTERRUPTS       __ASM("cpsid i")     // 关总中断()
//（4）【固定】不优化类型别名宏定义
typedef volatile uint8_t      vuint8_t;   // 不优化无符号8位数，字节
typedef volatile uint16_t     vuint16_t;  // 不优化无符号16位数，字
typedef volatile uint32_t     vuint32_t;  // 不优化无符号32位数，长字
typedef volatile int8_t       vint_8;     // 不优化有符号8位数
typedef volatile int16_t      vint_16;    // 不优化有符号16位数
typedef volatile int16_t      vint_32;    // 不优化有符号32位数
//（5）【固定】位操作宏函数（置位、清位、获得寄存器一位的状态）
#define BSET(bit,Register)  ((Register)|= (1<<(bit)))    //置寄存器的一位
#define BCLR(bit,Register)  ((Register) &= ~(1<<(bit)))  //清寄存器的一位
#define BGET(bit,Register)  (((Register) >> (bit)) & 1)  //获得寄存器一位的状态

#endif //防止重复定义（CPU_H 结尾）
