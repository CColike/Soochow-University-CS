#ifndef _IWDG_H   //��ֹ�ظ����壨_IWDG_H  ��ͷ)
#define _IWDG_H

//1 ͷ�ļ�


//��Ƶϵ���궨��
#define IWDG_PRESCALER_4     ((uint8_t)0x00)
#define IWDG_PRESCALER_8     ((uint8_t)(IWDG_PR_PR_0))
#define IWDG_PRESCALER_16    ((uint8_t)(IWDG_PR_PR_1))
#define IWDG_PRESCALER_32    ((uint8_t)(IWDG_PR_PR_1 | IWDG_PR_PR_0))
#define IWDG_PRESCALER_64    ((uint8_t)(IWDG_PR_PR_2))
#define IWDG_PRESCALER_128   ((uint8_t)(IWDG_PR_PR_2 | IWDG_PR_PR_0))
#define IWDG_PRESCALER_256   ((uint8_t)(IWDG_PR_PR_2 | IWDG_PR_PR_1))

//KR�Ĵ�������ָ��
#define IWDG_KEY_RELOAD                    ((uint32_t)0xAAAA)  /*!< IWDG Reload Counter Enable   */
#define IWDG_KEY_ENABLE                    ((uint32_t)0xCCCC)  /*!< IWDG Peripheral Enable       */
#define IWDG_KEY_WRITE_ACCESS_ENABLE        ((uint32_t)0x5555)  /*!< IWDG KR Write Access Enable  */
#define IWDG_KEY_WRITE_ACCESS_DISABLE       ((uint32_t)0x0000)  /*!< IWDG KR Write Access Disable */


//1 ͷ�ļ�
#include "mcu.h"

#define TIMEOUT1   1     //32ms
#define TIMEOUT2   2     //256ms
#define TIMEOUT3   3     //1024ms

#define ENABLE_WDOG	   1      //�����Ƿ������Ź�

// ===========================================================================
// �������ƣ�wdog_start
// ����������timeout:������װ�ص�ʱ��
// �������أ���
// ���ܸ�Ҫ�� �������Ź�ģ��
// ===========================================================================
void wdog_start(uint32_t timeout);

//=========================================================================
//�������ƣ�wdog_feed
//���ܸ�Ҫ��ι�����忴�Ź�������
//����˵������
//�������أ���
//=========================================================================
void wdog_feed(void);

void wdog_stop(void);

#endif
