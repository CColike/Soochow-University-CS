//=====================================================================
//文件名称：spi.c
//功能概要：spi底层驱动构件源文件
//制作单位：苏州大学嵌入式系统与物联网研究所(sumcu.suda.edu.cn)
//版    本：  2019-05-09  V2.0
//适用芯片：STM32
//=====================================================================


#include "spi.h"

SPI_TypeDef *SPI_ARR[] = {(SPI_TypeDef*)SPI1_BASE, (SPI_TypeDef*)SPI2_BASE, (SPI_TypeDef*)SPI3_BASE};
IRQn_Type table_irq_spi[3] = {SPI1_IRQn, SPI2_IRQn, SPI3_IRQn};
//=====================================================================
//函数名称：spi_init。
//功能说明：SPI初始化
//函数参数：No：模块号，可用参数可参见gec.h文件
//       MSTR：SPI主从机选择，0选择为从机,1选择为主机。
//       BaudRate：波特率，可取20000、10000、5000、2500、1250、625，单位：bps
//       CPOL：CPOL=0：高有效SPI时钟（低无效）；CPOL=1：低有效SPI时钟（高无效）
//       CPHA：CPHA=0相位为0； CPHA=1相位为1；
//函数返回：无
//=====================================================================
void spi_init(uint8_t No,uint8_t MSTR,uint16_t BaudRate,\
uint8_t CPOL,uint8_t CPHA)
{
    uint32_t temp = 0x00;    //
    uint16_t Freq_div;
    uint8_t BaudRate_Mode;
    if(No<SPI_1||No>SPI_3)   No=SPI_1;    //如果SPI号参数错误则强制选择 SPI1
    //（1）使能SPI和对应GPIO时钟
    switch(No)
    {
        case SPI_1:
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
        //使能PTA5,PTA6,PTA7,PTA15为SPI(SCK,MISO,MOSI,NSS)功能
        GPIOA->MODER &= ~(GPIO_MODER_MODE5|GPIO_MODER_MODE6|GPIO_MODER_MODE7|GPIO_MODER_MODE15);
        GPIOA->MODER |= (GPIO_MODER_MODE5_1|GPIO_MODER_MODE6_1|GPIO_MODER_MODE7_1|GPIO_MODER_MODE15_1);
        GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL5|GPIO_AFRL_AFSEL6|GPIO_AFRL_AFSEL7);
        GPIOA->AFR[0] |= ((GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL5_2) | (GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_2) | (GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_2));
        GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL15;
        GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL15_0 | GPIO_AFRH_AFSEL15_2);
        //配置引脚速率
        GPIOA->OSPEEDR |= 0xc000fc00;
        break;
        case SPI_2:
        //使能SPI2和GPIOB时钟
        RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
        //使能PTB13,PTB14,PTB15,PTB12为SPI(SCK,MISO,MOSI,NSS)功能
        GPIOB->MODER &= ~(GPIO_MODER_MODE12|GPIO_MODER_MODE13|GPIO_MODER_MODE14|GPIO_MODER_MODE15);
        GPIOB->MODER |= (GPIO_MODER_MODE12_1|GPIO_MODER_MODE13_1|GPIO_MODER_MODE14_1|GPIO_MODER_MODE15_1);
        GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL12|GPIO_AFRH_AFSEL13|GPIO_AFRH_AFSEL14|GPIO_AFRH_AFSEL15);
        GPIOB->AFR[1] |= (GPIO_AFRH_AFSEL12_0 | GPIO_AFRH_AFSEL12_2)|(GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL13_2)|(GPIO_AFRH_AFSEL14_0 | GPIO_AFRH_AFSEL14_2)|(GPIO_AFRH_AFSEL15_0 | GPIO_AFRH_AFSEL15_2);
        //配置引脚速率
        GPIOB->OSPEEDR |= 0xff000000;
        break;
        case SPI_3:
        break;
        default:
        break;
    }

    //（2）配置CR1寄存器
    //（2.1）暂时禁用SPI功能
    SPI_ARR[No]->CR1 &= ~SPI_CR1_SPE;
    //（2.2）配置SPI主从机模式
    if(MSTR == 1)    //主机模式
    {
        temp |= SPI_CR1_MSTR;
        //配置NSS脚由软件控制，置位为1
        temp |= SPI_CR1_SSI|SPI_CR1_SSM;
    }
    else    //从机模式
    {
        temp &= ~SPI_CR1_MSTR;
        //配置NSS脚由软件控制，置位为0
        temp |= SPI_CR1_SSM;
        temp &= ~SPI_CR1_SSI;
    }

    //（2.3）配置SPI相位和极性
    if(CPOL == 1)
    temp |= SPI_CR1_CPOL;
    else
    temp &= ~SPI_CR1_CPOL;

    if(CPHA == 1)
    temp |= SPI_CR1_CPHA;
    else
    temp &= ~SPI_CR1_CPHA;

    //（2.4）配置SPI波特率
    Freq_div = SystemCoreClock/1000/BaudRate;
    BaudRate_Mode = 0;
    while(Freq_div/2 >= 2)
    {
        BaudRate_Mode++;
        Freq_div = Freq_div/2;
    }
    temp |= (BaudRate_Mode<<3);

    //（2.5）统一配置CR1寄存器
    SPI_ARR[No]->CR1 |= temp;
    //（3）配置CR2寄存器
    temp = 0x00;
    //（3.1）配置数据为16bit
    //	temp |= SPI_CR2_DS;
    temp |= (SPI_CR2_DS_0|SPI_CR2_DS_1|SPI_CR2_DS_2);
    temp |= SPI_CR2_FRXTH;
    SPI_ARR[No]->CR2 |= temp;
    //（4）使能SPI功能
    SPI_ARR[No]->CR1 |= SPI_CR1_SPE;
}

//=====================================================================
//函数名称：spi_send1.
//功能说明：SPI发送一字节数据。
//函数参数：No：模块号，可用参数可参见gec.h文件
//       data：     需要发送的一字节数据。
//函数返回：0：发送失败；1：发送成功。
//=====================================================================
uint8_t spi_send1(uint8_t No,uint8_t data)
{
    volatile uint32_t i;

    i = 0;

    if(No<SPI_1||No>SPI_3)   return 0;  //如果SPI号参数错误则发送失败

    //若SPI未使能，则使能
    if ((SPI_ARR[No]->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        SPI_ARR[No]->CR1 |= SPI_CR1_SPE;
    }
    //判断发送缓冲区是否为空。若为空，则发送数据
    while((SPI_ARR[No]->SR & SPI_SR_TXE) !=  SPI_SR_TXE)
    {
        i++;
        if(i>0xfffe) return 0;
    }
    *((__IO uint8_t *)&SPI_ARR[No]->DR) = data;
    i = 0;

    //接收回发数据，防止发送缓冲区溢出
    while((SPI_ARR[No]->SR & SPI_SR_RXNE) !=  SPI_SR_RXNE)
    {
        i++;
        if(i>0xfffe) return 0;
    }
    //读一次DR,SR，防止DR,SR不被清空
    i = SPI_ARR[No]->DR;
    i = SPI_ARR[No]->SR;
    return 1;
}

//=====================================================================
//函数名称：spi_sendN
//功能说明：SPI发送数据。
//函数参数：No：模块号，可用参数可参见gec.h文件
//       n:     要发送的字节个数。范围为(1~255)
//       data[]:所发数组的首地址。
//函数返回：无。
//=====================================================================
uint8_t spi_sendN(uint8_t No,uint8_t n,uint8_t data[])
{
    uint32_t i;

    if(No<SPI_1||No>SPI_3)   return 0;     //如果SPI号参数错误则发送失败

    for (i = 0; i < n; i++)
    {
        if (!spi_send1(No, data[i])) //发送一个字节数据，失败则跳出循环
        {
            break;
        }
    }
    if(i<n)
        return 0;    //发送出错
    else
        return 1;    //发送成功
}

//=====================================================================
//函数名称：spi_receive1.
//功能说明：SPI接收一个字节的数据
//函数参数：No：模块号，可用参数可参见gec.h文件
//函数返回：接收到的数据。
//=====================================================================
uint8_t spi_receive1(uint8_t No)
{
    if(No<SPI_1||No>SPI_3)   return 0xff;     //如果SPI号参数错误则发送失败
    uint32_t i = 0;
    //若SPI未使能，则使能
    if ((SPI_ARR[No]->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        SPI_ARR[No]->CR1 |= SPI_CR1_SPE;
    }

    //判断接收缓冲区是否不为空。若不为空，则接收数据
    while((SPI_ARR[No]->SR & SPI_SR_RXNE) !=  SPI_SR_RXNE)
    {
        i++;
        if(i>0xfffe) return 0xff;
    }

    return SPI_ARR[No]->DR;
}

//=====================================================================
//函数名称：spi_receiveN.
//功能说明：SPI接收数据。当n=1时，就是接受一个字节的数据……
//函数参数：No：模块号，可用参数可参见gec.h文件
//        n:    要发送的字节个数。范围为(1~255),
//       data[]:接收到的数据存放的首地址。
//函数返回：1：接收成功,其他情况：失败。
//=====================================================================
uint8_t spi_receiveN(uint8_t No,uint8_t n,uint8_t data[])
{
    if(No<SPI_1||No>SPI_3)   return 0;   //如果SPI号参数错误则发送失败
    uint32_t i;
    for (i = 0; i < n; i++)
    {
        data[i] = spi_receive1(No);
        if (!data[i]) //发送一个字节数据，失败则跳出循环
        {
            break;
        }
    }
    if(i<n)
        return 0;    //接收出错
    else
        return 1;    //接收成功
}

//=====================================================================
//函数名称：spi_enable_re_int
//功能说明：打开SPI接收中断。
//函数参数：No：模块号，可用参数可参见gec.h文件
//函数返回：无。
//=====================================================================
void spi_enable_re_int(uint8_t No)
{
    if(No<SPI_1||No>SPI_3)   return;    //如果SPI号参数错误则发送失败
    SPI_ARR[No]->CR2 |= SPI_CR2_RXNEIE;     //开放SPI接收中断
    NVIC_EnableIRQ(table_irq_spi[No]);     //开中断控制器IRQ中断
}

//=====================================================================
//函数名称：spi_disable_re_int
//功能说明：关闭SPI接收中断。
//函数参数：No：模块号，可用参数可参见gec.h文件
//函数返回：无。
//=====================================================================
void spi_disable_re_int(uint8_t No)
{
    if(No<SPI_1||No>SPI_3)   return;   //如果SPI号参数错误则发送失败
    SPI_ARR[No]->CR2 &= ~SPI_CR2_RXNEIE;    //禁用SPI接收中断
    NVIC_DisableIRQ(table_irq_spi[No]);    //禁止中断控制器IRQ中断
}

