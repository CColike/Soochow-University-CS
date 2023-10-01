	.include "include.inc" //��ͷ�ļ���ֻ����user.inc
//��0�����ݶ������εĶ���
//��0.1���������ݴ洢data�ο�ʼ��ʵ�����ݴ洢��RAM��
	.section .data
//��0.1.1��������Ҫ������ַ�������ż�Ϊ�ַ����׵�ַ,\0Ϊ�ַ���������־
	hello_information: //�ַ������
	.ascii "-------------------------------------------------------\n"
	.ascii " ʹ��GPIO����������ɫ�Ķ�����\n"
	.ascii "------------------------------------------------------\n\0"
light_off:
	.asciz "LIGHT:OFF--\n" //�ư�״̬��ʾ
light_red_on:
	.asciz "LIGHT_RED:ON--\n" //�����״̬��ʾ
light_green_on:
	.asciz "LIGHT_GREEN:ON--\n" //�̵���״̬��ʾ
light_blue_on:
	.asciz "LIGHT_BLUE:ON--\n" //������״̬��ʾ
light_count:
	.asciz "�Ƶ���˸����mLightCount=%d\n" //��˸������ʾ
light_type:
	.asciz "�Ƶ���˸����mLightType=%d\n" //��˸������ʾ
//��0.1.2���������
	.align 4 //.word��ʽ4�ֽڶ���
	mMainLoopCount: //������ѭ����������
	.word 0
	mFlag: //����Ƶ�״̬��־
	.byte 'L'
	.align 4
	mLightCount: //����Ƶ���˸����
	.word 0
	.align 4
	mLightType: //����Ƶ����ͣ����ݸ�ʽΪ�֣���ʼֵΪ0������0123456˳��ѭ��
	.word 0
	.equ MainLoopNUM,5566770 //��ѭ�������趨ֵ��������
//��0.2���������洢text�ο�ʼ��ʵ�ʴ���洢��Flash��
	.section .text
	.syntax unified     //ָʾ�·�ָ��ΪARM��thumbͨ�ø�ʽ
	.thumb              //Thumbָ�
	.type main function //����mainΪ��������
	.global main        //��main�����ȫ�ֺ���������оƬ��ʼ��֮�����
	.align 2            //ָ������ݲ���2�ֽڶ��룬����Thumbָ�
//-------------------------------------------------------------------- 
//main.cʹ�õ��ڲ�����������
//--------------------------------------------------------------------
	main: //������
//��1��======�������֣���ͷ����ѭ��ǰ�ĳ�ʼ������======================
//��1.1������main����ʹ�õľֲ�����
//��1.2�������䡿�����ж�
	cpsid i 
//��1.3����������ʹ�õľֲ���������ֵ
//��1.4����ȫ�ֱ�������ֵ
//��1.5���û�����ģ���ʼ��
//��ʼ�����, r0��r1��r2��gpio_init����ڲ���
	ldr r0,=LIGHT_RED //r0<-�˿ں�����
	mov r1,#GPIO_OUTPUT //r1<-���ŷ���Ϊ���
	mov r2,#LIGHT_OFF //r2<-���ŵĳ�ʼ״̬Ϊ��
	bl gpio_init //����gpio��ʼ������
//��ʼ���̵�, r0��r1��r2��gpio_init����ڲ���
	ldr r0,=LIGHT_GREEN //r0<-�˿ں�����
	mov r1,#GPIO_OUTPUT //r1<-���ŷ���Ϊ���
	mov r2,#LIGHT_OFF //r2<-���ŵĳ�ʼ״̬Ϊ��
	bl gpio_init //����gpio��ʼ������
//��ʼ������, r0��r1��r2��gpio_init����ڲ���
	ldr r0,=LIGHT_BLUE //r0<-�˿ں�����
	mov r1,#GPIO_OUTPUT //r1<-���ŷ���Ϊ���
	mov r2,#LIGHT_OFF //r2<-���ŵĳ�ʼ״̬Ϊ��
	bl gpio_init //����gpio��ʼ������
//��1.6��ʹ��ģ���ж�
//��1.7�������䡿�����жϣ���ʼ��������
	cpsie i 
	ldr r0,=hello_information //����ʾ�ַ����׵�ַ
	bl printf //����printf��ʾ�ַ���
//bl . //�ڴ˴�׮
//��1��======�������֣���β��=======================================
//��2��======��ѭ�����֣���ͷ��=====================================
	main_loop: //��ѭ����ǩ����ͷ��
//��2.1����ѭ����������mMainLoopCount+1
	ldr r2,=mMainLoopCount //r2��mMainLoopCount�ĵ�ַ
	ldr r1, [r2] 
	add r1,#1 
	str r1,[r2] 
//��2.2��δ�ﵽ��ѭ�������趨ֵ������ѭ��
	ldr r2,=MainLoopNUM 
	cmp r1,r2 
	blO main_loop //δ�ﵽ������ѭ��
//��2.3���ﵽ��ѭ�������趨ֵ��ִ��������䣬���еƵ���������
//��2.3.1�����ѭ���������� 
	ldr r2,=mMainLoopCount //r2��mMainLoopCount�ĵ�ַ
	mov r1,#0 
	str r1,[r2] 
//��2.3.2�����״̬��־mFlagΪ'L'���Ƶ���˸����+1����ʾ���ı��״̬����־
//�жϵƵ�״̬��־
	ldr r2,=mFlag 
	ldr r6,[r2]
	cmp r6,#'L'
	bne main_light_off //mFlag������'L'����ʱ��Ҫ�ص�
//mFlag����'L'�������ʱ��Ҫ����
	ldr r3,=mLightCount //�Ƶ���˸����mLightCount+1
	ldr r1,[r3]
	add r1,#1
	str r1,[r3]
	ldr r0,=light_count //��ʾ�Ƶ���˸����ֵ
	ldr r2,=mLightCount
	ldr r1,[r2]
	bl printf
	ldr r2,=mFlag //�Ƶ�״̬��־��Ϊ'A'����һ������ƣ�
	mov r7,#'A'
	str r7,[r2] 
//�����ʱ�ĵƵ���ɫ����
	ldr r0,=light_type //��ʾ�Ƶ�����mLightType
	ldr r2,=mLightType
	ldr r1,[r2]
	bl printf
//�����ж�light_typeö�ٵ���һ�ֵƵ���ɫ������Ӧ�ĵ�
	ldr r2,=mLightType 
	ldr r1,[r2]  //r1<-mLightType
	cmp r1,#0
	bne light_type_1 //������0,��ת�ж�1
//light_type=0:red
	ldr r0,=LIGHT_RED //�����
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_red_on //��ʾ�������ʾ
	bl printf
	b end_light_type 
light_type_1:
	ldr r2,=mLightType 
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#1
	bne light_type_2 //������1,��ת�ж�2
//light_type=1:green
	ldr r0,=LIGHT_GREEN //���̵�
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_green_on //��ʾ�̵�����ʾ
	bl printf
	b end_light_type //break
light_type_2:
	ldr r2,=mLightType
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#2
	bne light_type_3 //������2,��ת�ж�3
//light_type=2:blue
	ldr r0,=LIGHT_BLUE //������
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_blue_on //��ʾ��������ʾ
	bl printf
	b end_light_type //break
light_type_3:
	ldr r2,=mLightType 
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#3
	bne light_type_4 //������3,��ת�ж�4
//light_type=3:yellow=red+green
	ldr r0,=LIGHT_RED //�����
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_red_on //��ʾ�������ʾ
	bl printf
	ldr r0,=LIGHT_GREEN //���̵�
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_green_on //��ʾ�̵�����ʾ
	bl printf
	b end_light_type //break
light_type_4:
	ldr r2,=mLightType
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#4
	bne light_type_5 //������4,��ת�ж�5
//light_type=4:purple=red+blue
	ldr r0,=LIGHT_RED //�����
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_red_on //��ʾ�������ʾ
	bl printf
	ldr r0,=LIGHT_BLUE //������
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_blue_on //��ʾ��������ʾ
	bl printf
	b end_light_type //break
light_type_5:
	ldr r2,=mLightType 
	ldr r1,[r2] //r1<-mLightType
	cmp r1,#5
	bne light_type_6 //������5,��ת6
//light_type=5:cyan=green+blue
	ldr r0,=LIGHT_GREEN //���̵�
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_green_on //��ʾ�̵�����ʾ
	bl printf
	ldr r0,=LIGHT_BLUE //������
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_blue_on //��ʾ��������ʾ
	bl printf
	b end_light_type //break
light_type_6:
//light_type=6:white=red+green+blue
	ldr r0,=LIGHT_RED //�����
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_red_on //��ʾ�������ʾ
	bl printf
	ldr r0,=LIGHT_GREEN //���̵�
	ldr r1,=LIGHT_ON
	bl gpio_set
	ldr r0, =light_green_on //��ʾ�̵�����ʾ
	bl printf
	ldr r0,=LIGHT_BLUE //������
	ldr r1,=LIGHT_ON
	bl gpio_set 
	ldr r0, =light_blue_on //��ʾ��������ʾ
	bl printf
end_light_type:
//�޸ĵƵ�����mLightType+1����mLightType>=7��mLightType=0
	ldr r3,=mLightType 
	ldr r1,[r3] //r1<-mLightType
	add r1,#1 //mLightType++
	cmp r1,#7
	blo type_not_to_zero //��mLightType>=7��mLightType=0
	mov r1,#0
	type_not_to_zero: //��mLightType<7��mLightType++�󲻸ı�
	str r1,[r3]
//mFlag����'L'���������ϣ�ת
	b main_exit 
//��2.3.3�����״̬��־mFlagΪ'A'���ı��״̬����־�������еĵ�
main_light_off:
	ldr r2,=mFlag //�Ƶ�״̬��־��Ϊ'L'
	mov r7,#'L'
	str r7,[r2] 
	ldr r0,=LIGHT_RED //����
	ldr r1,=LIGHT_OFF
	bl gpio_set
	ldr r0,=LIGHT_GREEN //���̵�
	ldr r1,=LIGHT_OFF
	bl gpio_set
	ldr r0,=LIGHT_BLUE //������
	ldr r1,=LIGHT_OFF
	bl gpio_set
	ldr r0, =light_off //��ʾ��ʾ
	bl printf
main_exit:
	b main_loop //����ѭ��
//��2��======��ѭ�����֣���β��=====================================
	.end //�������������־����β��
	
