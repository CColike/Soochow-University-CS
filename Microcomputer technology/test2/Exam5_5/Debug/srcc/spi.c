//=====================================================================
//�ļ����ƣ�spi.c
//���ܸ�Ҫ��spi�ײ���������Դ�ļ�
//������λ�����ݴ�ѧǶ��ʽϵͳ���������о���(sumcu.suda.edu.cn)
//��    ����  2019-05-09  V2.0
//����оƬ��STM32
//=====================================================================


#include "spi.h"

SPI_TypeDef *SPI_ARR[] = {(SPI_TypeDef*)SPI1_BASE, (SPI_TypeDef*)SPI2_BASE, (SPI_TypeDef*)SPI3_BASE};
IRQn_Type table_irq_spi[3] = {SPI1_IRQn, SPI2_IRQn, SPI3_IRQn};
//=====================================================================
//�������ƣ�spi_init��
//����˵����SPI��ʼ��
//����������No��ģ��ţ����ò����ɲμ�gec.h�ļ�
//       MSTR��SPI���ӻ�ѡ��0ѡ��Ϊ�ӻ�,1ѡ��Ϊ������
//       BaudRate�������ʣ���ȡ20000��10000��5000��2500��1250��625����λ��bps
//       CPOL��CPOL=0������ЧSPIʱ�ӣ�����Ч����CPOL=1������ЧSPIʱ�ӣ�����Ч��
//       CPHA��CPHA=0��λΪ0�� CPHA=1��λΪ1��
//�������أ���
//=====================================================================
void spi_init(uint8_t No,uint8_t MSTR,uint16_t BaudRate,\
uint8_t CPOL,uint8_t CPHA)
{
    uint32_t temp = 0x00;    //
    uint16_t Freq_div;
    uint8_t BaudRate_Mode;
    if(No<SPI_1||No>SPI_3)   No=SPI_1;    //���SPI�Ų���������ǿ��ѡ�� SPI1
    //��1��ʹ��SPI�Ͷ�ӦGPIOʱ��
    switch(No)
    {
        case SPI_1:
        RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
        //ʹ��PTA5,PTA6,PTA7,PTA15ΪSPI(SCK,MISO,MOSI,NSS)����
        GPIOA->MODER &= ~(GPIO_MODER_MODE5|GPIO_MODER_MODE6|GPIO_MODER_MODE7|GPIO_MODER_MODE15);
        GPIOA->MODER |= (GPIO_MODER_MODE5_1|GPIO_MODER_MODE6_1|GPIO_MODER_MODE7_1|GPIO_MODER_MODE15_1);
        GPIOA->AFR[0] &= ~(GPIO_AFRL_AFSEL5|GPIO_AFRL_AFSEL6|GPIO_AFRL_AFSEL7);
        GPIOA->AFR[0] |= ((GPIO_AFRL_AFSEL5_0 | GPIO_AFRL_AFSEL5_2) | (GPIO_AFRL_AFSEL6_0 | GPIO_AFRL_AFSEL6_2) | (GPIO_AFRL_AFSEL7_0 | GPIO_AFRL_AFSEL7_2));
        GPIOA->AFR[1] &= ~GPIO_AFRH_AFSEL15;
        GPIOA->AFR[1] |= (GPIO_AFRH_AFSEL15_0 | GPIO_AFRH_AFSEL15_2);
        //������������
        GPIOA->OSPEEDR |= 0xc000fc00;
        break;
        case SPI_2:
        //ʹ��SPI2��GPIOBʱ��
        RCC->APB1ENR1 |= RCC_APB1ENR1_SPI2EN;
        RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
        //ʹ��PTB13,PTB14,PTB15,PTB12ΪSPI(SCK,MISO,MOSI,NSS)����
        GPIOB->MODER &= ~(GPIO_MODER_MODE12|GPIO_MODER_MODE13|GPIO_MODER_MODE14|GPIO_MODER_MODE15);
        GPIOB->MODER |= (GPIO_MODER_MODE12_1|GPIO_MODER_MODE13_1|GPIO_MODER_MODE14_1|GPIO_MODER_MODE15_1);
        GPIOB->AFR[1] &= ~(GPIO_AFRH_AFSEL12|GPIO_AFRH_AFSEL13|GPIO_AFRH_AFSEL14|GPIO_AFRH_AFSEL15);
        GPIOB->AFR[1] |= (GPIO_AFRH_AFSEL12_0 | GPIO_AFRH_AFSEL12_2)|(GPIO_AFRH_AFSEL13_0 | GPIO_AFRH_AFSEL13_2)|(GPIO_AFRH_AFSEL14_0 | GPIO_AFRH_AFSEL14_2)|(GPIO_AFRH_AFSEL15_0 | GPIO_AFRH_AFSEL15_2);
        //������������
        GPIOB->OSPEEDR |= 0xff000000;
        break;
        case SPI_3:
        break;
        default:
        break;
    }

    //��2������CR1�Ĵ���
    //��2.1����ʱ����SPI����
    SPI_ARR[No]->CR1 &= ~SPI_CR1_SPE;
    //��2.2������SPI���ӻ�ģʽ
    if(MSTR == 1)    //����ģʽ
    {
        temp |= SPI_CR1_MSTR;
        //����NSS����������ƣ���λΪ1
        temp |= SPI_CR1_SSI|SPI_CR1_SSM;
    }
    else    //�ӻ�ģʽ
    {
        temp &= ~SPI_CR1_MSTR;
        //����NSS����������ƣ���λΪ0
        temp |= SPI_CR1_SSM;
        temp &= ~SPI_CR1_SSI;
    }

    //��2.3������SPI��λ�ͼ���
    if(CPOL == 1)
    temp |= SPI_CR1_CPOL;
    else
    temp &= ~SPI_CR1_CPOL;

    if(CPHA == 1)
    temp |= SPI_CR1_CPHA;
    else
    temp &= ~SPI_CR1_CPHA;

    //��2.4������SPI������
    Freq_div = SystemCoreClock/1000/BaudRate;
    BaudRate_Mode = 0;
    while(Freq_div/2 >= 2)
    {
        BaudRate_Mode++;
        Freq_div = Freq_div/2;
    }
    temp |= (BaudRate_Mode<<3);

    //��2.5��ͳһ����CR1�Ĵ���
    SPI_ARR[No]->CR1 |= temp;
    //��3������CR2�Ĵ���
    temp = 0x00;
    //��3.1����������Ϊ16bit
    //	temp |= SPI_CR2_DS;
    temp |= (SPI_CR2_DS_0|SPI_CR2_DS_1|SPI_CR2_DS_2);
    temp |= SPI_CR2_FRXTH;
    SPI_ARR[No]->CR2 |= temp;
    //��4��ʹ��SPI����
    SPI_ARR[No]->CR1 |= SPI_CR1_SPE;
}

//=====================================================================
//�������ƣ�spi_send1.
//����˵����SPI����һ�ֽ����ݡ�
//����������No��ģ��ţ����ò����ɲμ�gec.h�ļ�
//       data��     ��Ҫ���͵�һ�ֽ����ݡ�
//�������أ�0������ʧ�ܣ�1�����ͳɹ���
//=====================================================================
uint8_t spi_send1(uint8_t No,uint8_t data)
{
    volatile uint32_t i;

    i = 0;

    if(No<SPI_1||No>SPI_3)   return 0;  //���SPI�Ų�����������ʧ��

    //��SPIδʹ�ܣ���ʹ��
    if ((SPI_ARR[No]->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        SPI_ARR[No]->CR1 |= SPI_CR1_SPE;
    }
    //�жϷ��ͻ������Ƿ�Ϊ�ա���Ϊ�գ���������
    while((SPI_ARR[No]->SR & SPI_SR_TXE) !=  SPI_SR_TXE)
    {
        i++;
        if(i>0xfffe) return 0;
    }
    *((__IO uint8_t *)&SPI_ARR[No]->DR) = data;
    i = 0;

    //���ջط����ݣ���ֹ���ͻ��������
    while((SPI_ARR[No]->SR & SPI_SR_RXNE) !=  SPI_SR_RXNE)
    {
        i++;
        if(i>0xfffe) return 0;
    }
    //��һ��DR,SR����ֹDR,SR�������
    i = SPI_ARR[No]->DR;
    i = SPI_ARR[No]->SR;
    return 1;
}

//=====================================================================
//�������ƣ�spi_sendN
//����˵����SPI�������ݡ�
//����������No��ģ��ţ����ò����ɲμ�gec.h�ļ�
//       n:     Ҫ���͵��ֽڸ�������ΧΪ(1~255)
//       data[]:����������׵�ַ��
//�������أ��ޡ�
//=====================================================================
uint8_t spi_sendN(uint8_t No,uint8_t n,uint8_t data[])
{
    uint32_t i;

    if(No<SPI_1||No>SPI_3)   return 0;     //���SPI�Ų�����������ʧ��

    for (i = 0; i < n; i++)
    {
        if (!spi_send1(No, data[i])) //����һ���ֽ����ݣ�ʧ��������ѭ��
        {
            break;
        }
    }
    if(i<n)
        return 0;    //���ͳ���
    else
        return 1;    //���ͳɹ�
}

//=====================================================================
//�������ƣ�spi_receive1.
//����˵����SPI����һ���ֽڵ�����
//����������No��ģ��ţ����ò����ɲμ�gec.h�ļ�
//�������أ����յ������ݡ�
//=====================================================================
uint8_t spi_receive1(uint8_t No)
{
    if(No<SPI_1||No>SPI_3)   return 0xff;     //���SPI�Ų�����������ʧ��
    uint32_t i = 0;
    //��SPIδʹ�ܣ���ʹ��
    if ((SPI_ARR[No]->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        SPI_ARR[No]->CR1 |= SPI_CR1_SPE;
    }

    //�жϽ��ջ������Ƿ�Ϊ�ա�����Ϊ�գ����������
    while((SPI_ARR[No]->SR & SPI_SR_RXNE) !=  SPI_SR_RXNE)
    {
        i++;
        if(i>0xfffe) return 0xff;
    }

    return SPI_ARR[No]->DR;
}

//=====================================================================
//�������ƣ�spi_receiveN.
//����˵����SPI�������ݡ���n=1ʱ�����ǽ���һ���ֽڵ����ݡ���
//����������No��ģ��ţ����ò����ɲμ�gec.h�ļ�
//        n:    Ҫ���͵��ֽڸ�������ΧΪ(1~255),
//       data[]:���յ������ݴ�ŵ��׵�ַ��
//�������أ�1�����ճɹ�,���������ʧ�ܡ�
//=====================================================================
uint8_t spi_receiveN(uint8_t No,uint8_t n,uint8_t data[])
{
    if(No<SPI_1||No>SPI_3)   return 0;   //���SPI�Ų�����������ʧ��
    uint32_t i;
    for (i = 0; i < n; i++)
    {
        data[i] = spi_receive1(No);
        if (!data[i]) //����һ���ֽ����ݣ�ʧ��������ѭ��
        {
            break;
        }
    }
    if(i<n)
        return 0;    //���ճ���
    else
        return 1;    //���ճɹ�
}

//=====================================================================
//�������ƣ�spi_enable_re_int
//����˵������SPI�����жϡ�
//����������No��ģ��ţ����ò����ɲμ�gec.h�ļ�
//�������أ��ޡ�
//=====================================================================
void spi_enable_re_int(uint8_t No)
{
    if(No<SPI_1||No>SPI_3)   return;    //���SPI�Ų�����������ʧ��
    SPI_ARR[No]->CR2 |= SPI_CR2_RXNEIE;     //����SPI�����ж�
    NVIC_EnableIRQ(table_irq_spi[No]);     //���жϿ�����IRQ�ж�
}

//=====================================================================
//�������ƣ�spi_disable_re_int
//����˵�����ر�SPI�����жϡ�
//����������No��ģ��ţ����ò����ɲμ�gec.h�ļ�
//�������أ��ޡ�
//=====================================================================
void spi_disable_re_int(uint8_t No)
{
    if(No<SPI_1||No>SPI_3)   return;   //���SPI�Ų�����������ʧ��
    SPI_ARR[No]->CR2 &= ~SPI_CR2_RXNEIE;    //����SPI�����ж�
    NVIC_DisableIRQ(table_irq_spi[No]);    //��ֹ�жϿ�����IRQ�ж�
}

