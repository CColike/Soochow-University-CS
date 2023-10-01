//======================================================================
//�ļ����ƣ�mcu.h��mcuͷ�ļ���
//������λ��SD-Arm(sumcu.suda.edu.cn)
//���¼�¼��20181201-20200627
//======================================================================
#ifndef MCU_H     //��ֹ�ظ����壨MCU_H ��ͷ��
#define MCU_H

//��1�����䶯������оƬͷ�ļ�
#include "stm32l4xx.h"
//��2�����̶�������cpuͷ�ļ�
#include "cpu.h"
//��3�����䶯��MCU������Ϣ��غ곣��
//                            "1234567890123456789"
#define MCU_TYPE              "AHL-STM32L431-V3.9 "  //MCU�ͺţ�19�ֽڣ�
//                            "123456789"
#define BIOS_TYPE             "20201116 "       //BIOS�汾�ţ�9�ֽڣ�
#define MCU_SECTORSIZE        2048              //������С��B��
#define MCU_SECTOR_NUM        128               //MCU��������
#define MCU_STACKTOP          0x2000ffff        //ջ����ַ��RAM��ߵ�ַ��
#define MCU_FLASH_ADDR_START  0x08000000        //MCU��FLASH��ʼ��ַ
#define MCU_FLASH_ADDR_LENGTH 0x00040000        //MCU��FLASH���ȣ�128KB��
#define MCU_RAM_ADDR_START    0x20000000	    //MCU��RAM��ʼ��ַ
#define MCU_RAM_ADDR_LENGTH   0x00010000	    //MCU��RAM���ȣ�16KB��

#endif    //��ֹ�ظ����壨MCU_H ��β��