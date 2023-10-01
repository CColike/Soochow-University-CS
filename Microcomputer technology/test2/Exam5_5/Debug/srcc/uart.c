//======================================================================
//文件名称：uart.c
//功能概要：uart底层驱动构件源文件
//版权所有：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//更新记录：2019-05-20 V1.0 GXY
//======================================================================
#include "uart.h"

#if(USE_BIOS_UART==0)//1代表函数继承自BIOS，0代表使用自带函数

USART_TypeDef *USART_ARR[] = {(USART_TypeDef*)USART1_BASE, (USART_TypeDef*)USART2_BASE, (USART_TypeDef*)USART3_BASE};

//====定义串口IRQ号对应表====
IRQn_Type table_irq_uart[3] = {USART1_IRQn, USART2_IRQn, USART3_IRQn};
//内部函数声明
uint8_t uart_is_uartNo(uint8_t uartNo);

//======================================================================
//函数名称：uart_init
//功能概要：初始化uart模块
//参数说明：uartNo:串口号：UART_1、UART_2、UART_3
//          baud:波特率：300、600、1200、2400、4800、9600、19200、115200...
//函数返回：无
//======================================================================
void uart_init(uint8_t uartNo, uint32_t baud_rate)
{
	uint16_t usartdiv; //BRR寄存器应赋的值
    //判断传入串口号参数是否有误,有误直接退出
	if(!uart_is_uartNo(uartNo))
	{
		return;
	}

	//开启UART模块和GPIO模块的外围时钟，并使能引脚的UART功能
	switch(uartNo)
	{
	case UART_1:  //若为串口1
#ifdef UART1_GROUP
		//依据选择使能对应时钟，并配置对应引脚为UART_1
		switch(UART1_GROUP)
		{
		case 0:
			//使能USART1和GPIOA时钟
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			//使能PTA9,PTA10为USART(Tx,Rx)功能
			GPIOA->MODER &= ~(GPIO_MODER_MODE9|GPIO_MODER_MODE10);
			GPIOA->MODER |= (GPIO_MODER_MODE9_1|GPIO_MODER_MODE10_1);
			GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9|GPIO_AFRH_AFSEL10);
			GPIOA->AFR[1] |= ((GPIO_AFRH_AFSEL9_0 | GPIO_AFRH_AFSEL9_1 | GPIO_AFRH_AFSEL9_2)
					|(GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2));
			break;
		case 1:
			//使能USART1和GPIOB时钟
			RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			//使能PTB6,PTB7为USART(Tx,Rx)功能
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

	case UART_2:  //若为串口2
#ifdef UART2_GROUP
		//依据选择使能对应时钟，并配置对应引脚为UART_2
		switch(UART2_GROUP)
		{
		case 0:
			//使能USART2和GPIOA时钟
			RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
			//使能PTA2,PTA3为USART(Tx,Rx)功能
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

	case UART_3:  //若为串口3
#ifdef UART3_GROUP
		//依据选择使能对应时钟，并配置对应引脚为UART_3
		switch(UART3_GROUP)
		{
		case 0:
			//使能USART3和GPIOB时钟
			RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
			//使能PTB10,PTB11为USART(Tx,Rx)功能
			GPIOB->MODER &= ~(GPIO_MODER_MODE10|GPIO_MODER_MODE11);
			GPIOB->MODER |= (GPIO_MODER_MODE10_1|GPIO_MODER_MODE11_1);
			GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL10|GPIO_AFRH_AFSEL11);
			GPIOB->AFR[1] |= ((GPIO_AFRH_AFSEL10_0 | GPIO_AFRH_AFSEL10_1 | GPIO_AFRH_AFSEL10_2)
					|(GPIO_AFRH_AFSEL11_0 | GPIO_AFRH_AFSEL11_1 | GPIO_AFRH_AFSEL11_2));
			break;
		case 1:
			//使能USART3和GPIOC时钟
			RCC->APB1ENR1 |= RCC_APB1ENR1_USART3EN;
			RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
			//使能PTC10,PTC11为USART(Tx,Rx)功能
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
	//暂时禁用UART功能
	USART_ARR[uartNo-1]->CR1 &= ~USART_CR1_UE;
	//暂时关闭串口发送与接收功能
	USART_ARR[uartNo-1]->CR1 &= ~(USART_CR1_TE_Msk|USART_CR1_RE_Msk);
	//配置串口波特率
	if((USART_ARR[uartNo-1]->CR1 & USART_CR1_OVER8_Msk) == USART_CR1_OVER8_Msk)
	    usartdiv = (uint16_t)((SystemCoreClock/baud_rate)*2);
	else
	    usartdiv = (uint16_t)(SystemCoreClock/baud_rate);
	USART_ARR[uartNo-1]->BRR = usartdiv;
	//初始化控制寄存器和中断状态寄存器、清标志位
	USART_ARR[uartNo-1]->ISR = 0;
	USART_ARR[uartNo-1]->CR2 &= ~(USART_CR2_LINEN | USART_CR2_CLKEN);
	USART_ARR[uartNo-1]->CR3 &= ~(USART_CR3_SCEN | USART_CR3_HDSEL | USART_CR3_IREN);
	//启动串口发送与接收功能
	USART_ARR[uartNo-1]->CR1 |= (USART_CR1_TE|USART_CR1_RE);
	//开启UART功能
	USART_ARR[uartNo-1]->CR1 |= USART_CR1_UE;
}

//======================================================================
//函数名称：uart_send1
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//          ch:要发送的字节
//函数返回：函数执行状态：1=发送成功；0=发送失败。
//功能概要：串行发送1个字节
//======================================================================
uint8_t uart_send1(uint8_t uartNo, uint8_t ch)
{
	uint32_t t;

	//判断传入串口号参数是否有误，有误直接退出
	if(!uart_is_uartNo(uartNo))
	{
		return 0;
	}

	for (t = 0; t < 0xFBBB; t++)//查询指定次数
	{
		//发送缓冲区为空则发送数据
		if ( USART_ARR[uartNo-1]->ISR & USART_ISR_TXE_Msk )
		{
			USART_ARR[uartNo-1]->TDR = ch;
			break;
		}
	}//end for
	if (t >= 0xFBBB)
		return 0; //发送超时，发送失败
	else
		return 1; //成功发送
}

//======================================================================
//函数名称：uart_sendN
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//         buff: 发送缓冲区
//         len:发送长度
//函数返回： 函数执行状态：1=发送成功；0=发送失败
//功能概要：串行 接收n个字节
//======================================================================
uint8_t uart_sendN(uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
    uint16_t i;

    //判断传入串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return 0;
    }

    for (i = 0; i < len; i++)
    {
        if (!uart_send1(uartNo, buff[i])) //发送一个字节数据，失败则跳出循环
        {
            break;
        }
    }
    if(i<len)
        return 0;    //发送出错
    else
        return 1;    //发送出错
}

//======================================================================
//函数名称：uart_send_string
//参数说明：uartNo:UART模块号:UART_1、UART_2、UART_3
//          buff:要发送的字符串的首地址
//函数返回： 函数执行状态：1=发送成功；0=发送失败
//功能概要：从指定UART端口发送一个以'\0'结束的字符串
//======================================================================
uint8_t uart_send_string(uint8_t uartNo, uint8_t* buff)
{
    uint16_t i = 0;
    uint8_t *buff_ptr = (uint8_t *)buff;     //定义指针指向要发送字符串首地址

    //判断传入串口号参数是否有误，有误直接退出
    if(!uart_is_uartNo(uartNo))
    {
        return 0;
    }

    for(i = 0; buff_ptr[i] != '\0'; i++)   //遍历字符串里的字符
    {
        if (!uart_send1(uartNo,buff_ptr[i]))//发送指针对应的字符
            return 0;  //发送失败,返回
    }
    return 1;          //发送成功
}

//======================================================================
//函数名称：uart_re1
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//        *fp:接收成功标志的指针:*fp=1:接收成功；*fp=0:接收失败
//函数返回：接收返回字节
//功能概要：串行接收1个字节
//======================================================================
uint8_t uart_re1(uint8_t uartNo,uint8_t *fp)
{
    uint32_t t;
    uint8_t  dat;

	//判断传入串口号参数是否有误，有误直接退出
	if(!uart_is_uartNo(uartNo))
	{
		*fp=0;
		return 0;
	}

	for (t = 0; t < 0xFBBB; t++)//查询指定次数
	{
		//判断接收缓冲区是否满
		if (USART_ARR[uartNo-1]->ISR & USART_ISR_RXNE_Msk)
		{
			dat=USART_ARR[uartNo-1]->RDR;    //获取数据,清接收中断位
			*fp = 1;  //接收成功
			break;
		}
	}//end for
	if(t >= 0xFBBB)
	{
		dat = 0xFF;
		*fp = 0;    //未收到数据
	}
	return dat;    //返回接收到的数据
}

//======================================================================
//函数名称：uart_reN
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//          buff: 接收缓冲区
//          len:接收长度
//函数返回：函数执行状态 1=接收成功;0=接收失败
//功能概要：串行 接收n个字节,放入buff中
//======================================================================
uint8_t uart_reN(uint8_t uartNo ,uint16_t len ,uint8_t* buff)
{
	uint16_t i;
	uint8_t flag = 0;

	//判断传入串口号参数是否有误，有误直接退出
	if(!uart_is_uartNo(uartNo))
	{
		return 0;
	}

	//判断是否能接受数据
	for (i = 0; i < len && flag==1; i++)
	{
		buff[i] = uart_re1(uartNo, &flag); //接受数据
	}
	if (i < len)
		return 0; //接收失败
	else
		return 1; //接收成功
}

//======================================================================
//函数名称：uart_enable_re_int
//参数说明：uartNo: 串口号:UART_1、UART_2、UART_3
//函数返回：无
//功能概要：开串口接收中断
//======================================================================
void uart_enable_re_int(uint8_t uartNo)
{
	//判断传入串口号参数是否有误，有误直接退出
	if(!uart_is_uartNo(uartNo))
	{
		return;
	}

	USART_ARR[uartNo-1]->CR1 |= USART_CR1_RXNEIE_Msk;    //开放UART接收中断
	NVIC_EnableIRQ(table_irq_uart[uartNo-1]);    //开中断控制器IRQ中断
}

//======================================================================
//函数名称：uart_disable_re_int
//参数说明：uartNo: 串口号 :UART_1、UART_2、UART_3
//函数返回：无
//功能概要：关串口接收中断
//======================================================================
void uart_disable_re_int(uint8_t uartNo)
{
	//判断传入串口号参数是否有误，有误直接退出
	if(!uart_is_uartNo(uartNo))
	{
		return;
	}

	USART_ARR[uartNo-1]->CR1 &= ~USART_CR1_RXNEIE_Msk;    //禁止UART接收中断
	NVIC_DisableIRQ(table_irq_uart[uartNo-1]);    //禁止中断控制器IRQ中断
}

//======================================================================
//函数名称：uart_get_re_int
//参数说明：uartNo: 串口号 :UART_1、UART_2、UART_3
//函数返回：接收中断标志 1=有接收中断;0=无接收中断
//功能概要：获取串口接收中断标志,同时禁用发送中断
//======================================================================
uint8_t uart_get_re_int(uint8_t uartNo)
{
	//判断传入串口号参数是否有误，有误直接退出
	if(!uart_is_uartNo(uartNo))
	{
		return 0;
	}

	//获取接收中断标志，需同时判断RXNE和RXNEIE
	if(((USART_ARR[uartNo-1]->ISR & USART_ISR_RXNE_Msk) == USART_ISR_RXNE_Msk)
			&& ((USART_ARR[uartNo-1]->CR1 & USART_CR1_RXNEIE_Msk) == USART_CR1_RXNEIE_Msk))
		return 1;
	else
		return 0;
}


//======================================================================
//函数名称：uart_deinit
//参数说明：uartNo: 串口号 :UART_1、UART_2、UART_3
//函数返回：无
//功能概要：uart反初始化，关闭串口时钟
//======================================================================
void uart_deinit(uint8_t uartNo)
{
	//判断传入串口号参数是否有误,有误直接退出
	if(!uart_is_uartNo(uartNo))
	{
		return;
	}

	//开启UART模块和GPIO模块的外围时钟，并使能引脚的UART功能
	switch(uartNo)
	{
	case UART_1:  //若为串口1
#ifdef UART1_GROUP
		//依据选择关闭对应时钟，并禁止对应引脚为UART_1
		switch(UART1_GROUP)
		{
		case 0:
			//关闭USART1和GPIOA时钟
			RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOAEN;
			//禁止PTA9,PTA10为USART(Tx,Rx)功能
			GPIOA->MODER &= ~(GPIO_MODER_MODE9|GPIO_MODER_MODE10);
			GPIOA->AFR[1] &= ~(GPIO_AFRH_AFSEL9|GPIO_AFRH_AFSEL10);
			break;
		case 1:
			//关闭USART1和GPIOB时钟
			RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOBEN;
			//禁止PTB6,PTB7为USART(Tx,Rx)功能
			GPIOB->MODER &= ~(GPIO_MODER_MODE6|GPIO_MODER_MODE7);
			GPIOB->AFR[0] &= ~(GPIO_AFRL_AFSEL6|GPIO_AFRL_AFSEL7);
			break;
		default:
			break;
		}
#endif
		break;

	case UART_2:  //若为串口2
#ifdef UART2_GROUP
		//依据选择关闭对应时钟，并禁止对应引脚为UART_2
		switch(UART2_GROUP)
		{
		case 0:
			//关闭USART2和GPIOA时钟
			RCC->APB1ENR1 &= ~RCC_APB1ENR1_USART2EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOAEN;
			//禁止PTA2,PTA3为USART(Tx,Rx)功能
			GPIOA->MODER &= ~(GPIO_MODER_MODE2|GPIO_MODER_MODE3);
			GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL2|GPIO_AFRL_AFSEL3);
			break;
		default:
			break;
		}
#endif
		break;

	case UART_3:  //若为串口3
#ifdef UART3_GROUP
		//依据选择关闭对应时钟，并禁止对应引脚为UART_3
		switch(UART3_GROUP)
		{
		case 0:
			//关闭USART3和GPIOB时钟
			RCC->APB1ENR1 &= ~RCC_APB1ENR1_USART3EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOBEN;
			//禁止PTB10,PTB11为USART(Tx,Rx)功能
			GPIOB->MODER &= ~(GPIO_MODER_MODE10|GPIO_MODER_MODE11);
			GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL10|GPIO_AFRH_AFSEL11);
			break;
		case 1:
			//关闭USART3和GPIOC时钟
			RCC->APB1ENR1 &= ~RCC_APB1ENR1_USART3EN;
			RCC->AHB2ENR &= ~RCC_AHB2ENR_GPIOCEN;
			//禁止PTC10,PTC11为USART(Tx,Rx)功能
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

//----------------------以下为内部函数存放处--------------------------------------
//=====================================================================
//函数名称：uart_is_uartNo
//函数返回：1:串口号在合理范围内，0：串口号不合理
//参数说明：串口号uartNo  :UART_1、UART_2、UART_3
//功能概要：为程序健壮性而判断uartNo是否在串口数字范围内
//=====================================================================
uint8_t uart_is_uartNo(uint8_t uartNo)
{
    if(uartNo < UART_1 || uartNo > UART_3)
        return 0;
    else
        return 1;
}

#endif
