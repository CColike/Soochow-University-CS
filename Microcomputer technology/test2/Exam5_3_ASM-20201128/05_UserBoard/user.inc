//======================================================================
//�ļ����ƣ�user.inc
//���ܸ�Ҫ�������������õ���ͷ�ļ�
//��Ȩ���У�SD-ARM(sumcu.suda.edu.cn)
//�汾���£�2019-09-01 V1.0
//======================================================================
.include "gpio.inc"

//ָʾ�ƶ˿ڼ����Ŷ���
.equ LIGHT_RED,(PTB_NUM|7)    	//��ɫRUN��ʹ�õĶ˿�/����
.equ LIGHT_GREEN,(PTB_NUM|8)  	//��ɫRUN��ʹ�õĶ˿�/����
.equ LIGHT_BLUE,(PTB_NUM|9)    	//��ɫRUN��ʹ�õĶ˿�/����

//��״̬�궨�壨�������ư���Ӧ��������ƽ��Ӳ���ӷ�������
.equ LIGHT_ON,0     			//����
.equ LIGHT_OFF,1    			//�ư�

//���ں궨��
//�û����ڣ�����оTTL-USB�����ߣ��Ӳ��ߣ�������-�أ������ǰ��ߣ�TX)����������ߣ�RX)
.equ UART_User, 2         //TX���ţ�GEC_10��RX���ţ�GEC_8(ʵ����ϱ�ʶUART0)

//�궨���������
.equ DELAY_NUM,1000000  		//��ʱ����Լ1�룩������С����˸Ƶ��
.equ UART_BAUD,115200           //���ڲ�����

//myprintf�ض���
.equ printf, myprintf

//����ԭ�жϴ�����������20200317��
.type  USART2_IRQHandler, function
.global USART2_IRQHandler

//�������жϴ�����������20200317��
.type  UART_User_Handler, function
.global UART_User_Handler

//�����¾��жϴ�����������ӳ�䡾20200317��
.equ USART2_IRQHandler,UART_User_Handler
