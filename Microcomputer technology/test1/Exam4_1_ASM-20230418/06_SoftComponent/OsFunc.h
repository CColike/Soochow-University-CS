//======================================================================
//�ļ����ƣ�OsFunc.h��RTOS�����ӿ�ͷ�ļ���
//������λ���մ�arm��������(sumcu.suda.edu.cn)
//���¼�¼��20200927
//======================================================================
#ifndef OSFUNC_H   //��ֹ�ظ����壨OSFUNC_H ��ͷ��
#define OSFUNC_H

//��1��RT-Thread��غ곣������
//�¼�
#define RT_EVENT_FLAG_AND               0x01            /**< logic and */
#define RT_EVENT_FLAG_OR                0x02            /**< logic or */
#define RT_EVENT_FLAG_CLEAR             0x04            /**< clear flag */
//IPC��ر�־
#define RT_IPC_FLAG_FIFO                0x00            /**< FIFOed IPC. @ref IPC. */
#define RT_IPC_FLAG_PRIO                0x01            /**< PRIOed IPC. @ref IPC. */

#define RT_IPC_CMD_UNKNOWN              0x00            /**< unknown IPC command */
#define RT_IPC_CMD_RESET                0x01            /**< reset IPC object */

#define RT_WAITING_FOREVER              -1              /**< Block forever until get resource. */
#define RT_WAITING_NO                   0               /**< Non-block. */

#define RT_EOK                          0               /**< There is no error */


//��2��RT-Thread��غ�������===================================================
#define OS_start  ((void (*)(void (*func)(void)))(component_fun[34]))
#define thread_create  ((uint8_t (*)(const char *name,void (*entry)(void *parameter),\
                                          void *parameter,uint32_t stack_size,uint8_t priority,\
                                                 uint32_t tick))(component_fun[35]))
#define thread_start  ((void (*)(uint8_t threadIndex))(component_fun[36]))
#define thread_wait  ((void (*)(uint32_t millisec))(component_fun[37]))
#define heap_init  ((void (*)(uint32_t userHeapBase))(component_fun[33]))
#define get_thread_self  ((uint32_t (*)(void))(component_fun[38]))
//�¼�
#define event_create  ((uint8_t (*)(const char *name, uint8_t flag))(component_fun[41]))
#define event_recv  ((void (*)(uint8_t EventIndex, uint32_t set, uint8_t option,\
                                     uint32_t timeout,uint32_t *recved))(component_fun[42]))
#define event_send  ((void (*)(uint8_t EventIndex,uint32_t set))(component_fun[43]))
//�ź���
#define rt_sem_create  ((uint8_t (*)(const char *name, uint32_t value, uint8_t flag))(component_fun[46]))
#define rt_sem_take  ((void (*)(uint8_t SpIndex, uint32_t time))(component_fun[47]))
#define rt_sem_release  ((void (*)(uint8_t SpIndex))(component_fun[48]))
#define sem_getNum  ((uint8_t (*)(uint8_t SpIndex))(component_fun[49]))
//������
#define rt_mutex_create  ((uint8_t (*)(const char *name,uint8_t flag))(component_fun[52]))
#define rt_mutex_take  ((void (*)(uint8_t MutexIndex, uint32_t time))(component_fun[53]))
#define rt_mutex_release  ((void (*)(uint8_t MutexIndex))(component_fun[54]))
//��Ϣ����
#define rt_mq_create  ((uint8_t (*)(const char *name,uint32_t msg_size,\
                                            uint32_t max_msgs,uint8_t flag))(component_fun[57]))
#define rt_mq_send  ((uint32_t (*)(uint8_t MqIndex, void *buffer, uint32_t size))(component_fun[58]))
#define rt_mq_recv  ((uint8_t (*)(uint8_t MqIndex, void *buffer,\
                                            uint32_t size,uint32_t timeout))(component_fun[59]))
#define rt_malloc  ((char* (*)(uint32_t size))(component_fun[60]))
#define rt_sprintf  ((void (*)(char *buf, const char *format, ...))(component_fun[61]))
#define mq_getIndex  ((uint8_t (*)(uint8_t MqIndex))(component_fun[62]))
//ϵͳʱ�亯��
#define rt_tick_get ((uint32_t (*)(void))(component_fun[63]))


#endif    