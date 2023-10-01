//======================================================================
//�ļ����ƣ�isr.c
//���ܸ�Ҫ�� �жϵײ���������Դ�ļ�
//��Ȩ���У�SD-ARM(sumcu.suda.edu.cn)
//���¼�¼��2019-09-27 V1.0
//======================================================================
.include "include.inc"

//start ������������
.type  USART2_IRQHandler, function
.global USART2_IRQHandler
//end  ������������

//========================�жϺ�����������===================================
.section .text
//======================================================================
//�������ƣ�UART_User_Handler��UARTA�����жϴ�������
//�����������յ�һ���ֽڴ���
//�����ܣ��ط����յ����ֽ�
//======================================================================
UART_User_Handler:
//��1�������жϣ����ұ����ֳ�
      cpsid  i          //�ؿ������ж�
      push {r7,lr}      //r7,lr��ջ������r7��������ռ��ã�lr��Ϊ�����ж�ǰpc��ֵ��
      //uint_8 flag
	  sub sp,#4         //ͨ���ƶ�spָ���ȡ��ַ
	  mov r7,sp         //����ȡ���ĵ�ַ����r7
//��2�������ֽ�
      mov r1,r7         //r1=r7 ��Ϊ����һ���ֽڵĵ�ַ
      mov r0,#UART_User		//r0ָ�����ں�
      bl  uart_re1      //���ý���һ���ֽ��Ӻ���
//��3�������ֽ�
      mov r1,r0			//r1��Ŵ��ڽ��յ������ݣ���Ϊuart_send1����ڲ���
      mov r0,#UART_User		//r0ָ�����ں�
      bl  uart_send1    //��ԭ���ڻط�
//��4��������Σ����һָ��ֳ�
      cpsie   i         //��������ж�
      add r7,#4         //��ԭr7
      mov sp,r7         //��ԭsp
      pop {r7,pc}       //r7,pc��ջ����ԭr7��ֵ��pc��lr,�������ж�ǰ�������ִ��