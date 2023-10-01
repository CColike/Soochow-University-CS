///=====================================================================
//�ļ����ƣ�printf.h�ļ�
//������λ��SD-Arm(sumcu.suda.edu.cn)
//���¼�¼��
//��20200816��XSX����������ĸ�������������Լ��������Ż��ȼ��������
//��20201119��LX,����ˡ�������С��������Ϊ���0�����ܻ���������⣬Դ�����3��
//��20210421��CL���޸ĸ���������ֻ�����10λ���������޸�Ϊ���Դ�ӡ��20λ��������
//=====================================================================
#ifndef	PRINT_H //��ֹ�ظ����壨PRINT_H ��ͷ��
#define PRINT_H

#include "uart.h"
#include "string.h"

#define UART_printf  UART_3   //printf����ʹ�õĴ��ں�

#define printf   myprintf

#define va_start _crt_va_start
#define va_arg _crt_va_arg
#define va_end _crt_va_end


//typedef char *  va_list;
//���º������ڶԲ�ȷ�����������ĺ������в���ָ�붨λ
//��n�ĳ��Ȼ�Ϊint���ȵ�������
#define _INTSIZEOF(n)   ((sizeof(n) + sizeof(int) - 1) & ~(sizeof(int) - 1))
//��ʼ��λ���������ָ��λ��
#define _crt_va_start(ap,v) ( ap = (char *)&(v) + _INTSIZEOF(v) )
//���ζ�ȡ���������ֵ
#define _crt_va_arg(ap,t)   ( *(t *)((ap+=_INTSIZEOF(t)),ap-_INTSIZEOF(t)) )
//�ſ�apָ��Ϊ��һ�ε�����׼��
#define _crt_va_end(ap)     ( ap = (char *)0 )

//���ڴ����ַ�����������Ϣ�ṹ��
typedef struct {
	int dest;                         //ȷ����Ϣ�ṹ������ͣ�Ĭ�����ͻ��ַ�������
	void (*func)(char);       //����������ܺ���
	char *loc;                        //�����ַ���ģʽ���ڴ洢�ַ�β��ַ
} PRINTK_INFO;


//======================================================================
//�������ƣ�myprintf
//���ܸ�Ҫ����������Ĳ������н���Ȼ������ͨ�����ڴ��
//����˵����const char *:��ӡ�����ַ�������������ַ������н���������ʽ���
//       ���磺 printf("c=%c\n",c); ��c��char�ͽ������
//�������أ��ַ�������
//======================================================================
int myprintf(const char *, ...);


#define DEST_CONSOLE    (1)
#define DEST_STRING     (2)
//���ڷֱ�%f��%lf�ĺ궨���ַ�
#define LENMOD_l  1
#define LENMOD_L  2
//�����ж�%�������ʽ�ĺ궨��
#define FLAGS_MINUS     (0x01)
#define FLAGS_PLUS      (0x02)
#define FLAGS_SPACE     (0x04)
#define FLAGS_ZERO      (0x08)
#define FLAGS_POUND     (0x10)

#define IS_FLAG_MINUS(a)    (a & FLAGS_MINUS)
#define IS_FLAG_PLUS(a)     (a & FLAGS_PLUS)
#define IS_FLAG_SPACE(a)    (a & FLAGS_SPACE)
#define IS_FLAG_ZERO(a)     (a & FLAGS_ZERO)
#define IS_FLAG_POUND(a)    (a & FLAGS_POUND)


#ifdef	FALSE
#undef	FALSE
#endif
#define FALSE	(0)

#ifdef	TRUE
#undef	TRUE
#endif
#define	TRUE	(1)

#endif  //��ֹ�ظ����壨PRINT_H ��β��


//======================================================================
/*��¼һ
 *
 *C.1 ���������printf���õ�һ���ʽ
 ���������printf�������õ�һ����ʽΪ��
 ��ţ�
     .ascii ����ʽ�����ַ���\0��
 ldr r0,=���
 ldr r1,=����б��������1
 ldr r2,=����б��������2
 ...
 ���и�ʽ�����ַ�������ָ�������ʽ����ʽ���ƴ����ɸ�ʽ�ַ����ͷǸ�ʽ�ַ���
 ������ɡ���ʽ�ַ�������%��ͷ���ַ�������%������и��ָ�ʽ�ַ�����˵�����
 ���ݵ����͡���ʽ�����ȡ�С��λ���ȡ��磺
     �� %d����ʾ��ʮ�������������
   �� %ld����ʾ��ʮ���Ƴ����������
   �� %f����ʾ�����������
   �� %lf����ʾdouble�������
   �� %c����ʾ���ַ��������
   �� \n����ʾ���з��ȡ�
�Ǹ�ʽ�ַ���ԭ�����������ʾ������ʾ���á���������и����˸�������Ҫ���
ʽ�ַ����͸��������������������Ӧ��һһ��Ӧ��
��ſ���ȷ�����뵱ǰλ�õĳ����������PC��ֵ��

ע��������ı�����float��double���ַ���ʱ������printf����ʽ���в�ͬ
����
1.float�ͣ�
	mf:
		.float 1.123456
	
	data_format1:
    	.ascii "%f\n\0"
    
    ldr r0,=mf
	ldr r0,[r0]
	bl __aeabi_f2d   //���ÿ⺯��Ԥ����������r0,r1
	mov r2,r0
	mov r3,r1
	ldr r0,=data_format2
	bl printf       //ʵ�ʴ���r0,r2,r3
2.double�ͣ�
	mlf:
		.double 3.145678
	
	data_format2:
    	.ascii "%lf\n\0" 
    
	ldr r1,=mlf
    ldrd r2,r3,[r1]
    ldr r0,=data_format3
    bl printf    //ʵ�ʴ���r0,r2,r3

3. �ַ����ͣ�
	mstring��
		.ascii "light\0"
		
	data_format3:
		.ascii "%s\n\0"
		
	ldr r0,=data_format3
	ldr r1,=mstring
	bl printf
	
C.1.1 ��ʽ�����ַ���
       ��ʽ�����ַ�����һ����ʽΪ��[��־][�����С����][����][����]���ͣ�����
       ������[]�е���Ϊ��ѡ�����˵����������塣
1. ����
�����ַ����Ա�ʾ������ݵ����ͣ����ʽ�����������C-1��ʾ��
��C-1 �����ַ�
��ʽ�ַ�	                             ����
  d	             ��ʮ������ʽ�������������(�������������)
  o	             �԰˽�����ʽ����޷�������(�����ǰ׺0)
 x,X	   ��ʮ��������ʽ����޷�������(�����ǰ׺Ox)
  u	             ��ʮ������ʽ����޷�������
  f	             ��С����ʽ�������˫����ʵ��
 e,E	   ��ָ����ʽ�������˫����ʵ��
 g,G	   ��%f��%e�н϶̵���������������˫����ʵ��
  c	             ��������ַ�
  s	             ����ַ���
2. ��־
��־�ַ�Ϊ -��+��# �Ϳո����֣����������C-2��ʾ��
��־	                           ����
 -	            �������룬�ұ���ո�
 +	            �������(���Ż򸺺�)
�ո�            ���ֵΪ��ʱ���Կո�Ϊ��ʱ���Ը���
 #              ��c��s��d��u����Ӱ�죻��o�࣬�����ʱ��ǰ׺o����x�࣬�����ʱ��ǰ׺0x��
                ��e��g��f �൱�����С��ʱ�Ÿ���С���㡣
 
3. �����С����
        ��ʮ������������ʾ���������λ������ʵ��λ�����ڶ���Ŀ��ȣ���ʵ��λ���������ʵ��λ�����ڶ���
�Ŀ������Կո����벹0���������Сλ��ǰ��0��
4. ����
        ���ȸ�ʽ���ԡ�.����ͷ�����ʮ��������������������ǣ����������֣����ʾС����λ������������
���ַ������ʾ����ַ��ĸ�������ʵ��λ������������ľ����������ȥ�����Ĳ��֡�
5. ����
���ȸ�ʽ��Ϊh��l���֣�h��ʾ���������������l��ʾ���������������



��¼��
 *
 *C.2 prinf���õ�һ���ʽ
printf������һ����׼�⺯�����������ｫ�����������������
printf�������õ�һ����ʽΪ��printf(����ʽ�����ַ�����, �������)��
���и�ʽ�����ַ�������ָ�������ʽ����ʽ���ƴ����ɸ�ʽ�ַ����ͷǸ�ʽ�ַ���������ɡ���ʽ�ַ�������%��ͷ
���ַ�������%������и��ָ�ʽ�ַ�����˵��������ݵ����͡���ʽ�����ȡ�С��λ���ȡ��磺
   �� %d����ʾ��ʮ�������������
   �� %ld����ʾ��ʮ���Ƴ����������
   �� %f����ʾ�����������
   �� %lf����ʾdouble�������
   �� %c����ʾ���ַ��������
   �� \n����ʾ���з��ȡ�
       �Ǹ�ʽ�ַ���ԭ�����������ʾ������ʾ���á���������и����˸�������Ҫ���ʽ�ַ����͸������������
��������Ӧ��һһ��Ӧ��
C.1.1 ��ʽ�ַ���
       ��ʽ�ַ�����һ����ʽΪ��[��־][�����С����][����][����]���ͣ����з�����[]�е���Ϊ��ѡ�
����˵����������塣
1. ����
�����ַ����Ա�ʾ������ݵ����ͣ����ʽ�����������C-1��ʾ��
��C-1 �����ַ�
��ʽ�ַ�	                             ����
  d	             ��ʮ������ʽ�������������(�������������)
  o	             �԰˽�����ʽ����޷�������(�����ǰ׺0)
 x,X	   ��ʮ��������ʽ����޷�������(�����ǰ׺Ox)
  u	             ��ʮ������ʽ����޷�������
  f	             ��С����ʽ�������˫����ʵ��
 e,E	   ��ָ����ʽ�������˫����ʵ��
 g,G	   ��%f��%e�н϶̵���������������˫����ʵ��
  c	             ��������ַ�
  s	             ����ַ���
2. ��־
��־�ַ�Ϊ -��+��# �Ϳո����֣����������C-2��ʾ��
��־	                           ����
 -	            �������룬�ұ���ո�
 +	            �������(���Ż򸺺�)
3. �����С����
        ��ʮ������������ʾ���������λ������ʵ��λ�����ڶ���Ŀ��ȣ���ʵ��λ���������ʵ��λ�����ڶ���
�Ŀ������Կո��0��
4. ����
        ���ȸ�ʽ���ԡ�.����ͷ�����ʮ��������������������ǣ����������֣����ʾС����λ������������
���ַ������ʾ����ַ��ĸ�������ʵ��λ������������ľ����������ȥ�����Ĳ��֡�
5. ����
���ȸ�ʽ��Ϊh��l���֣�h��ʾ���������������l��ʾ���������������



����������˵����
	      �������Է��ָ������ľ���ΪС�����5λ��
                �������������λ��������������KEA128оƬ���ں��й�,�������Է�������ͬ�ں˵�KL25����
        ͬ�������⡣
 *
 */


/*
         ʵ�����������
 	char c,s[20];
    int a;
    float f;
    double x;
    a=1234;
    f=3.14159322;
    x=0.123456789123456789;
    c='A';
    strcpy(s,"Hello,World");
    uart_init(UART_Printf,9600);      //����2ʹ������ʱ��20MHz
    printf("���ݴ�ѧǶ��ʽʵ����KEA128-printf������������!\n");
    //���������������������
    printf("���������������:\n");
    printf("����a=%d\n", a);        //����ʮ����������ʽ�������ʾ a=1234
    printf("����a=%d%%\n", a);      //���%�� ��� a=1234%
    printf("����a=%6d\n", a);       //���6λʮ�������� ��߲��ո���ʾ a= 1234
    printf("����a=%06d\n", a);      //���6λʮ�������� ��߲�0����ʾ a=001234
    printf("����a=%2d\n", a);       //a����2λ����ʵ����� a=1234
    printf("����a=%-6d\n", a);      //���6λʮ�������� �ұ߲��ո���ʾ a=1234
    printf("\n");
    //���������������������
    printf("�����������������:\n");
    printf("������f=%f\n", f);                  //��������Ч������7λ�����f=3.14159297
    printf("������fhavassda  =  %6.4f\n", f);   //���6�У�С�����4λ����� f=3.1416
    printf("double����x=%lf\n", x);            //����������� x=0.12345678912345678
    printf("double����x=%18.15lf\n", x);       //���18�У�С�����15λ��x=0.123456789123456
    printf("\n");
    //�ַ����������������
    printf("�ַ����������������:\n");
    printf("�ַ���c=%c\n", c);           //����ַ� c=A
    printf("ASCII��c=%x\n", c);         //��ʮ����������ַ���ASCII�� c=41
    printf("�ַ���s[]=%s\n", s);         //��������ַ���s[]=Hello,World
    printf("�ַ���s[]=%6.9s\n", s);      //������9���ַ����ַ��� s[]=Hello,World
 */