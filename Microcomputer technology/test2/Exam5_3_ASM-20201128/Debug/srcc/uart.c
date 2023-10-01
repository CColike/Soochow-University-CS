//======================================================================
//�ļ����ƣ�uart.c
//���ܸ�Ҫ��uart�ײ���������Դ�ļ�
//��Ȩ���У����ݴ�ѧǶ��ʽϵͳ���������о���(sumcu.suda.edu.cn)
//���¼�¼��2019-05-20 V1.0 GXY
//======================================================================
#include "uart.h"

#if(USE_BIOS_UART==0)//1�������̳���BIOS��0����ʹ���Դ�����

USART_TypeDef *USART_ARR[] = {(USART_TypeDef*)USART1_BASE, (USART_TypeDef*)USART2_BASE, (USART_TypeDef*)USART3_BASE};

//====���崮��IRQ�Ŷ�Ӧ��====
IRQn_Type table_irq_uart[3] = {USART1_IRQn, USART2_IRQn, USART3_IRQn};
//�ڲ���������
uint8_t uart_is_uartNo(uint8_t uartNo);

//======================================================================
//�������ƣ�uart_init
//���ܸ�Ҫ����ʼ��uartģ��
//����˵����uartNo:���ںţ�UART_1��UART_2��UART_3
//          baud:�����ʣ�300��600��1200��2400��4800��9600��19200��115200...
//�������أ���
//======================================================================
void uart_init(uint8_t uartNo, uint32_t baud_rate)
{
	uint16_t usartdiv; //BRR�Ĵ���Ӧ����ֵ
    //�жϴ��봮�ںŲ����Ƿ�����,����ֱ���˳�
	if(!uart_is_uartNo(uartNo))
	{
		return;
	}

	//����UARTģ���GPIOģ�����Χʱ�ӣ���ʹ�����ŵ�UART����
	switch(uartNo)
	{
	case UART_1:  //��Ϊ����1
#ifdef UART1_GROUP
		//����ѡ��ʹ�ܶ�Ӧʱ�ӣ������ö�Ӧ����ΪUART_1
		switch(UART1_GROUP)
		{
		case 0:
			//ʹ��USART1��GPIOAʱ��
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			//ʹ��PTA9,PTA10ΪUSART(Tx,Rx)����
			GPIOA->MODER &= ~(GPIO_MODER_MODE9|GPIO_MODER_MODE10);
			GPIOA->MODER |= (GPIO_MODER_MODE9_1|GPIO_MODER_MODE10_1);
			GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9|GPIO_AFRH_AFSEL10);
			GPIOA->AFR[1] |= ((GPIO_AFRH_AFSEL9_0 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_2)
					|(GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2));
			break;
		case 1:
			//ʹ��USART1��GPIOBʱ��
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			//ʹ��PTB6,PTB7ΪUSART(Tx,Rx)����
			GPIOB->MODER &= ~(GPIO_MODER_MODE6|GPIO_MODER_MODE7);
			GPIOB->MODER |= (GPIO_MODER_MODE6_1|GPIO_MODER_MODE7_1);
			GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6|GPIO_AFRL_AFSEL7);
			GPIOB->AFR[0] |= ((GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_1 | GPIO_AFRL_AFSEL6_2)
					|(GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_1 | GPIO_AFRL_AFSEL7_2));
			break;
		default:
			break;
		}
#endif
		break;

	case UART_2:  //��Ϊ����2
#ifdef UART2_GROUP
		//����ѡ��ʹ�ܶ�Ӧʱ�ӣ������ö�Ӧ����ΪUART_2
		switch(UART2_GROUP)
		{
		case 0:
			//ʹ��USART2��GPIOAʱ��
			RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			//ʹ��PTA2,PTA3ΪUSART(Tx,Rx)����
			GPIOA->MODER &= ~(GPIO_MODER_MODE2|GPIO_MODER_MODE3);
			GPIOA->MODER |= (GPIO_MODER_MODE2_1|GPIO_MODER_MODE3_1);
			GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2|GPIO_AFRL_AFSEL3);
			GPIOA->AFR[0] |= ((GPIO_AFRL_AFSEL2_0 | GPIO_AFRL_AFSEL2_1 | GPIO_AFRL_AFSEL2_2)
					|(GPIO_AFRL_AFSEL3_0 | GPIO_AFRL_AFSEL3_1 | GPIO_AFRL_AFSEL3_2));
			break;
		default:
			break;
		}
#endif
		break;

	case UART_3:  //��Ϊ����3
#ifdef UART3_GROUP
		//����ѡ��ʹ�ܶ�Ӧʱ�ӣ������ö�Ӧ����ΪUART_3
		switch(UART3_GROUP)
		{
		case 0:
			//ʹ��USART3��GPIOBʱ��
			RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			//ʹ��PTB10,PTB11ΪUSART(Tx,Rx)����
			GPIOB->MODER &= ~(GPIO_MODER_MODE10|GPIO_MODER_MODE11);
			GPIOB->MODER |= (GPIO_MODER_MODE10_1|GPIO_MODER_MODE11_1);
			GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL10|GPIO_AFRH_AFSEL11);
			GPIOB->AFR[1] |= ((GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2)
					|(GPIO_AFRH_AFSEL11_0 | GPIO_AFRH_AFSEL11_1 | GPIO_AFRH_AFSEL11_2));
			break;
		case 1:
			//ʹ��USART3��GPIOCʱ��
			RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
			//ʹ��PTC10,PTC11ΪUSART(Tx,Rx)����
			GPIOC->MODER &= ~(GPIO_MODER_MODE10|GPIO_MODER_MODE11);
			GPIOC->MODER |= (GPIO_MODER_MODE10_1|GPIO_MODER_MODE11_1);
			GPIOC->AFR[1] &= ~(GPIO_AFRH_AFSEL10|GPIO_AFRH_AFSEL11);
			GPIOC->AFR[1] |= ((GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2)
					|(GPIO_AFRH_AFSEL11_0 | GPIO_AFRH_AFSEL11_1 | GPIO_AFRH_AFSEL11_2));
			break;
		default:
			break;
		}
#endif
		break;
	}
	//��ʱ����UART����
	USART_ARR[uartNo-1]->CR1 &= ~USART_CR1_UE;
	//��ʱ�رմ��ڷ�������չ���
	USART_ARR[uartNo-1]->CR1 &= ~(USART_CR1_TE_Msk|USART_CR1_RE_Msk);
	//���ô��ڲ�����
	if((USART_ARR[uartNo-1]->CR1 & USART_CR1_OVER8_Msk) == USART_CR1_OVER8_Msk)
	    usartdiv = (uint16_t)((SystemCoreClock/baud_rate)*2);
	else
	    usartdiv = (uint16_t)(SystemCoreClock/baud_rate);
	USART_ARR[uartNo-1]->BRR = usartdiv;
	//��ʼ�����ƼĴ������ж�״̬�Ĵ��������־λ
	USART_ARR[uartNo-1]->ISR = 0;
	USART_ARR[uartNo-1]->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
	USART_ARR[uartNo-1]->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
	//�������ڷ�������չ���
	USART_ARR[uartNo-1]->CR1 |= (USART_CR1_TE|USART_CR1_RE);
	//����UART����
	USART_ARR[uartNo-1]->CR1 |= USART_CR1_UE;
}

//======================================================================
//�������ƣ�uart_send1
//����˵����uartNo: ���ں�:UART_1��UART_2��UART_3
//          ch:Ҫ���͵��ֽ�
//�������أ�����ִ��״̬��1=���ͳɹ���0=����ʧ�ܡ�
//���ܸ�Ҫ�����з���1���ֽ�
//======================================================================
uint8_t uart_send1(uint8_t uartNo, uint8_t ch)
{
	uint32_t t;

	//�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
	if(!uart_is_uartNo(uartNo))
	{
		return 0;
	}

	for (t = 0; t < 0xFBBB; t++)//��ѯָ������
	{
		//���ͻ�����Ϊ����������
		if ( USART_ARR[uartNo-1]->ISR & USART_ISR_TXE_Msk )
		{
			USART_ARR[uartNo-1]->TDR = ch;
			break;
		}
	}//end for
	if (t >= 0xFBBB)
		return 0; //���ͳ�ʱ������ʧ��
	else
		return 1; //�ɹ�����
}

//======================================================================
//�������ƣ�uart_sendN
//����˵����uartNo: ���ں�:UART_1��UART_2��UART_3
//         buff: ���ͻ�����
//         len:���ͳ���
//�������أ� ����ִ��״̬��1=���ͳɹ���0=����ʧ��
//���ܸ�Ҫ������ ����n���ֽ�
//======================================================================
uint8_t uart_sendN(uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
    uint16_t i;

    //�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
    if(!uart_is_uartNo(uartNo))
    {
        return 0;
    }

    for (i = 0; i < len; i++)
    {
        if (!uart_send1(uartNo, buff[i])) //����һ���ֽ����ݣ�ʧ��������ѭ��
        {
            break;
        }
    }
    if(i<len)
        return 0;    //���ͳ���
    else
        return 1;    //���ͳ���
}

//======================================================================
//�������ƣ�uart_send_string
//����˵����uartNo:UARTģ���:UART_1��UART_2��UART_3
//          buff:Ҫ���͵��ַ������׵�ַ
//�������أ� ����ִ��״̬��1=���ͳɹ���0=����ʧ��
//���ܸ�Ҫ����ָ��UART�˿ڷ���һ����'\0'�������ַ���
//======================================================================
uint8_t uart_send_string(uint8_t uartNo, uint8_t* buff)
{
    uint16_t i = 0;
    uint8_t *buff_ptr = (uint8_t *)buff;     //����ָ��ָ��Ҫ�����ַ����׵�ַ

    //�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
    if(!uart_is_uartNo(uartNo))
    {
        return 0;
    }

    for(i = 0; buff_ptr[i] != '\0'; i++)   //�����ַ�������ַ�
    {
        if (!uart_send1(uartNo,buff_ptr[i]))//����ָ���Ӧ���ַ�
            return 0;  //����ʧ��,����
    }
    return 1;          //���ͳɹ�
}

//======================================================================
//�������ƣ�uart_re1
//����˵����uartNo: ���ں�:UART_1��UART_2��UART_3
//        *fp:���ճɹ���־��ָ��:*fp=1:���ճɹ���*fp=0:����ʧ��
//�������أ����շ����ֽ�
//���ܸ�Ҫ�����н���1���ֽ�
//======================================================================
uint8_t uart_re1(uint8_t uartNo,uint8_t *fp)
{
    uint32_t t;
    uint8_t  dat;

	//�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
	if(!uart_is_uartNo(uartNo))
	{
		*fp=0;
		return 0;
	}

	for (t = 0; t < 0xFBBB; t++)//��ѯָ������
	{
		//�жϽ��ջ������Ƿ���
		if (USART_ARR[uartNo-1]->ISR & USART_ISR_RXNE_Msk)
		{
			dat=USART_ARR[uartNo-1]->RDR;    //��ȡ����,������ж�λ
			*fp = 1;  //���ճɹ�
			break;
		}
	}//end for
	if(t >= 0xFBBB)
	{
		dat = 0xFF;
		*fp = 0;    //δ�յ�����
	}
	return dat;    //���ؽ��յ�������
}

//======================================================================
//�������ƣ�uart_reN
//����˵����uartNo: ���ں�:UART_1��UART_2��UART_3
//          buff: ���ջ�����
//          len:���ճ���
//�������أ�����ִ��״̬ 1=���ճɹ�;0=����ʧ��
//���ܸ�Ҫ������ ����n���ֽ�,����buff��
//======================================================================
uint8_t uart_reN(uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
	uint16_t i;
	uint8_t flag = 0;

	//�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
	if(!uart_is_uartNo(uartNo))
	{
		return 0;
	}

	//�ж��Ƿ��ܽ�������
	for (i = 0; i < len && flag==1; i++)
	{
		buff[i] = uart_re1(uartNo, &flag); //��������
	}
	if (i < len)
		return 0; //����ʧ��
	else
		return 1; //���ճɹ�
}

//======================================================================
//�������ƣ�uart_enable_re_int
//����˵����uartNo: ���ں�:UART_1��UART_2��UART_3
//�������أ���
//���ܸ�Ҫ�������ڽ����ж�
//======================================================================
void uart_enable_re_int(uint8_t uartNo)
{
	//�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
	if(!uart_is_uartNo(uartNo))
	{
		return;
	}

	USART_ARR[uartNo-1]->CR1 |= USART_CR1_RXNEIE_Msk;    //����UART�����ж�
	NVIC_EnableIRQ(table_irq_uart[uartNo-1]);    //���жϿ�����IRQ�ж�
}

//======================================================================
//�������ƣ�uart_disable_re_int
//����˵����uartNo: ���ں� :UART_1��UART_2��UART_3
//�������أ���
//���ܸ�Ҫ���ش��ڽ����ж�
//======================================================================
void uart_disable_re_int(uint8_t uartNo)
{
	//�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
	if(!uart_is_uartNo(uartNo))
	{
		return;
	}

	USART_ARR[uartNo-1]->CR1 &= ~USART_CR1_RXNEIE_Msk;    //��ֹUART�����ж�
	NVIC_DisableIRQ(table_irq_uart[uartNo-1]);    //��ֹ�жϿ�����IRQ�ж�
}

//======================================================================
//�������ƣ�uart_get_re_int
//����˵����uartNo: ���ں� :UART_1��UART_2��UART_3
//�������أ������жϱ�־ 1=�н����ж�;0=�޽����ж�
//���ܸ�Ҫ����ȡ���ڽ����жϱ�־,ͬʱ���÷����ж�
//======================================================================
uint8_t uart_get_re_int(uint8_t uartNo)
{
	//�жϴ��봮�ںŲ����Ƿ���������ֱ���˳�
	if(!uart_is_uartNo(uartNo))
	{
		return 0;
	}

	//��ȡ�����жϱ�־����ͬʱ�ж�RXNE��RXNEIE
	if(((USART_ARR[uartNo-1]->ISR & USART_ISR_RXNE_Msk) == USART_ISR_RXNE_Msk)
			&& ((USART_ARR[uartNo-1]->CR1 & USART_CR1_RXNEIE_Msk) == USART_CR1_RXNEIE_Msk))
		return 1;
	else
		return 0;
}


//======================================================================
//�������ƣ�uart_deinit
//����˵����uartNo: ���ں� :UART_1��UART_2��UART_3
//�������أ���
//���ܸ�Ҫ��uart����ʼ�����رմ���ʱ��
//======================================================================
void uart_deinit(uint8_t uartNo)
{
	//�жϴ��봮�ںŲ����Ƿ�����,����ֱ���˳�
	if(!uart_is_uartNo(uartNo))
	{
		return;
	}

	//����UARTģ���GPIOģ�����Χʱ�ӣ���ʹ�����ŵ�UART����
	switch(uartNo)
	{
	case UART_1:  //��Ϊ����1
#ifdef UART1_GROUP
		//����ѡ��رն�Ӧʱ�ӣ�����ֹ��Ӧ����ΪUART_1
		switch(UART1_GROUP)
		{
		case 0:
			//�ر�USART1��GPIOAʱ��
			RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOAEN;
			//��ֹPTA9,PTA10ΪUSART(Tx,Rx)����
			GPIOA->MODER &= ~(GPIO_MODER_MODE9|GPIO_MODER_MODE10);
			GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9|GPIO_AFRH_AFSEL10);
			break;
		case 1:
			//�ر�USART1��GPIOBʱ��
			RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOBEN;
			//��ֹPTB6,PTB7ΪUSART(Tx,Rx)����
			GPIOB->MODER &= ~(GPIO_MODER_MODE6|GPIO_MODER_MODE7);
			GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6|GPIO_AFRL_AFSEL7);
			break;
		default:
			break;
		}
#endif
		break;

	case UART_2:  //��Ϊ����2
#ifdef UART2_GROUP
		//����ѡ��رն�Ӧʱ�ӣ�����ֹ��Ӧ����ΪUART_2
		switch(UART2_GROUP)
		{
		case 0:
			//�ر�USART2��GPIOAʱ��
			RCC->APB1ENR1 &= ~RCC_APB1ENR1_USART2EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOAEN;
			//��ֹPTA2,PTA3ΪUSART(Tx,Rx)����
			GPIOA->MODER &= ~(GPIO_MODER_MODE2|GPIO_MODER_MODE3);
			GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2|GPIO_AFRL_AFSEL3);
			break;
		default:
			break;
		}
#endif
		break;

	case UART_3:  //��Ϊ����3
#ifdef UART3_GROUP
		//����ѡ��رն�Ӧʱ�ӣ�����ֹ��Ӧ����ΪUART_3
		switch(UART3_GROUP)
		{
		case 0:
			//�ر�USART3��GPIOBʱ��
			RCC->APB1ENR1 &= ~RCC_APB1ENR1_USART3EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOBEN;
			//��ֹPTB10,PTB11ΪUSART(Tx,Rx)����
			GPIOB->MODER &= ~(GPIO_MODER_MODE10|GPIO_MODER_MODE11);
			GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL10|GPIO_AFRH_AFSEL11);
			break;
		case 1:
			//�ر�USART3��GPIOCʱ��
			RCC->APB1ENR1 &= ~RCC_APB1ENR1_USART3EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOCEN;
			//��ֹPTC10,PTC11ΪUSART(Tx,Rx)����
			GPIOC->MODER &= ~(GPIO_MODER_MODE10|GPIO_MODER_MODE11);
			GPIOC->AFR[1] &= ~(GPIO_AFRH_AFSEL10|GPIO_AFRH_AFSEL11);
			break;
		default:
			break;
		}
#endif
		break;
	}
}

//----------------------����Ϊ�ڲ�������Ŵ�--------------------------------------
//=====================================================================
//�������ƣ�uart_is_uartNo
//�������أ�1:���ں��ں���Χ�ڣ�0�����ںŲ�����
//����˵�������ں�uartNo  :UART_1��UART_2��UART_3
//���ܸ�Ҫ��Ϊ����׳�Զ��ж�uartNo�Ƿ��ڴ������ַ�Χ��
//=====================================================================
uint8_t uart_is_uartNo(uint8_t uartNo)
{
    if(uartNo < UART_1 || uartNo > UART_3)
        return 0;
    else
        return 1;
}

#endif
