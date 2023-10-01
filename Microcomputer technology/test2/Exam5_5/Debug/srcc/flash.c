//����ͷ�ļ�
#include "flash.h"
#include "string.h"
#if(USE_BIOS_FLASH==0)//1�������̳���BIOS��0����ʹ���Դ�����
//=================�ڲ����ú�������=====================================
//======================================================================
//�������ƣ�flash_write_DoubleWord
//�������أ�0-�ɹ� 1-ʧ��
//����˵����addr��Ŀ���ַ��Ҫ��Ϊ4�ı����Ҵ���Flash�׵�ַ
//              �����磺0x08000004��Flash�׵�ַΪ0x08000000��
//       data��д���˫��
//���ܸ�Ҫ��Flash˫��д�����
//======================================================================
uint8_t flash_write_DoubleWord(uint32_t addr,uint32_t data_l,uint32_t data_h);
//======================================================================
//�������ƣ�flash_Best
//�������أ�0-�ɹ� 1-ʧ��
//����˵����sect:��д��������
//			offset:��д������λ�õ�ƫ�Ƶ�ַ
//			N����д�������ֽ���
//			buf:��д�����ݵ��׵�ַ
//���ܸ�Ҫ����λ��ַ�����������µ�����д��
//======================================================================
uint8_t flash_Best(uint16_t sect,uint16_t offset,uint16_t N,uint8_t *buf);
//======================================================================
//======================================================================

//=================�ⲿ�ӿں���=========================================
//======================================================================
//�������ƣ�flash_init
//�������أ���
//����˵������
//���ܸ�Ҫ����ʼ��flashģ��
//======================================================================
void flash_init(void)
{
    //���֮ǰ�ı�̵��µ����д����־λ
	FLASH->SR &= 0xFFFFFFUL;
    //����Flash���ƼĴ���(CR)
    if((FLASH->CR & FLASH_CR_LOCK) != 0U)
    {
        FLASH->KEYR = (uint32_t)FLASH_KEY1;
        FLASH->KEYR = (uint32_t)FLASH_KEY2;
    }
    
    //�ȴ�֮ǰ���һ��flash�������
    while( (FLASH->SR & FLASH_SR_BSY) != 0U);
    
    //�����ݻ�����
    FLASH->ACR &= ~FLASH_ACR_DCEN_Msk;
    //�����漴ʱ���λ
    FLASH->CR &= ~FLASH_CR_PG_Msk;
}
//======================================================================
//�������ƣ�flash_erase
//�������أ�����ִ��ִ��״̬��0=������1=�쳣��
//����˵����sect��Ŀ�������ţ���Χȡ����ʵ��оƬ������ STM32L433:0~127,ÿ����2KB;
//���ܸ�Ҫ������flash�洢����sect����
//======================================================================
uint8_t flash_erase(uint16_t sect)
{
	
    //�ȴ�֮ǰ���һ��flash�������
    while( (FLASH->SR & FLASH_SR_BSY) != 0U);
    //���֮ǰ�ı�̵��µ����д����־λ
	FLASH->SR &= 0xFFFFFFUL;
    //�����漴ʱ���λ
    FLASH->CR &= ~FLASH_CR_PG;
    
    //ʹ����������
    FLASH->CR |= FLASH_CR_PER;
    //���ò���������
    FLASH->CR &= ~FLASH_CR_PNB;
    FLASH->CR |= (uint32_t)(sect << 3u);
    //��ʼ��������
    FLASH->CR |= FLASH_CR_STRT;
    //�ȴ������������
    while( (FLASH->SR & FLASH_SR_BSY) != 0U);
    //��ֹ��������
    FLASH->CR &= ~FLASH_CR_PER;
    
    return 0;  //�ɹ�����
}
//======================================================================
//�������ƣ�flash_write
//�������أ�����ִ��״̬��0=������1=�쳣��
//����˵����sect�������ţ���Χȡ����ʵ��оƬ������ STM32L433:0~127,ÿ����2KB��
//        offset:д�������ڲ�ƫ�Ƶ�ַ��0~2044��Ҫ��Ϊ0,4,8,12��......��
//        N��д���ֽ���Ŀ��4~2048,Ҫ��Ϊ4,8,12,......��
//        buf��Դ���ݻ������׵�ַ
//���ܸ�Ҫ����buf��ʼ��N�ֽ�д�뵽flash�洢����sect������ offset��
//=======================================================================
uint8_t flash_write(uint16_t sect,uint16_t offset,uint16_t N,uint8_t *buf)
{
    uint16_t i;
	
    //���֮ǰ�ı�̵��µ����д����־λ
	FLASH->SR &= 0xFFFFFFUL;
	
    //д���ֽ�����������
    if(offset+N>MCU_SECTORSIZE)
    {
        //��д���һ������
        flash_write(sect,offset,MCU_SECTORSIZE-offset,buf);
        //��д��ڶ�������
        flash_write(sect+1,0,N-(MCU_SECTORSIZE-offset),buf+(MCU_SECTORSIZE-offset));
    }
    //д���ֽ������������
    else
    {
//        //���ǰ���ַ����˫�ֶ��룬ֱ��д��
//        if(offset%8==0&&N%8==0)
//        {
//            flash_Best(sect,offset,N,buf);
//        }
//        //ǰ���ַֻҪ��һ��������
//        else
//        {	
            uint8_t data[MCU_SECTORSIZE]; //�洢��ǰ������ȫ��ֵ
            flash_read_logic(data,sect,0,MCU_SECTORSIZE); //����ǰ������ȫ��ֵ����������
            //��Ҫд����������ն�Ӧλ��д��������
            for(i = 0;i<N;i++)
            {
                data[offset+i] = buf[i];
            }
            //��������
            flash_erase(sect);
            //������д������
            flash_Best(sect,0,MCU_SECTORSIZE,data);
//        }
    }
    
	//�ȴ�д��������
	while( (FLASH->SR & FLASH_SR_BSY) != 0U);
	return 0;  //�ɹ�ִ��
}

//==========================================================================
//�������ƣ�flash_write_physical
//�������أ�����ִ��״̬��0=��������0=�쳣��
//����˵���� addr��Ŀ���ַ��Ҫ��Ϊ4�ı����Ҵ���Flash�׵�ַ
//              �����磺0x08000004��Flash�׵�ַΪ0x08000000��
//       cnt��д���ֽ���Ŀ��8~512��
//       buf��Դ���ݻ������׵�ַ
//���ܸ�Ҫ��flashд�����
//==========================================================================
uint8_t flash_write_physical(uint32_t addr,uint16_t N,uint8_t buf[])
{
    uint16_t sect;   //������
    uint16_t offset;	// ƫ�Ƶ�ַ
    sect = (addr-MCU_FLASH_ADDR_START)/MCU_SECTORSIZE;
    offset = addr-(sect*MCU_SECTORSIZE)-MCU_FLASH_ADDR_START;
    flash_write(sect,offset,N,buf);
    
	//�ȴ�д��������
	while( (FLASH->SR & FLASH_SR_BSY) != 0U);
	return 0;  //�ɹ�ִ��
}

//======================================================================
//�������ƣ�flash_read_logic
//�������أ���
//����˵����dest���������ݴ�Ŵ�������ַ��Ŀ���Ǵ����������ݣ�RAM����
//       sect�������ţ���Χȡ����ʵ��оƬ������ STM32L433:0~127,ÿ����2KB��
//       offset:�����ڲ�ƫ�Ƶ�ַ��0~2024��Ҫ��Ϊ0,4,8,12��......��
//       N�����ֽ���Ŀ��4~2048,Ҫ��Ϊ4,8,12,......��//
//���ܸ�Ҫ����ȡflash�洢����sect������ offset����ʼ��N�ֽڣ���RAM��dest��
//=======================================================================
void flash_read_logic(uint8_t *dest,uint16_t sect,uint16_t offset,uint16_t N)
{
    uint8_t *src;
    src=(uint8_t *)(FLASH_BASE+sect*FLASH_PAGE_SIZE+offset);
    memcpy(dest,src,N);
}

//======================================================================
//�������ƣ�flash_read_physical
//�������أ���
//����˵����dest���������ݴ�Ŵ�������ַ��Ŀ���Ǵ����������ݣ�RAM����
//       addr��Ŀ���ַ��Ҫ��Ϊ4�ı��������磺0x00000004��
//       N�����ֽ���Ŀ��0~1020,Ҫ��Ϊ4��8,12,......��
//���ܸ�Ҫ����ȡflashָ����ַ������
//======================================================================
void flash_read_physical(uint8_t *dest,uint32_t addr,uint16_t N)
{
    uint8_t *src;
    src=(uint8_t *)addr;
    memcpy(dest,src,N);
}

//======================================================================
//�������ƣ�flash_protect
//�������أ���
//����˵����M����������������
//���ܸ�Ҫ��flash��������
//======================================================================
void flash_protect(uint8_t M)
{
    uint32_t temp;
    temp = M|((M+1)<<16);
    if((FLASH->CR & FLASH_CR_OPTLOCK) != 0U)
    {
        FLASH->OPTKEYR = (uint32_t)FLASH_OPTKEY1;
        FLASH->OPTKEYR = (uint32_t)FLASH_OPTKEY2;
    }
    while( (FLASH->SR & FLASH_SR_BSY) != 0U);
    //������ؼĴ���
    FLASH->WRP1AR &= 0x0;
    FLASH->WRP1AR |= temp;
    FLASH->CR |= FLASH_CR_OPTSTRT;
    while( (FLASH->SR & FLASH_SR_BSY) != 0U);
    FLASH->CR &= ~FLASH_CR_OPTSTRT;

}


//======================================================================
//�������ƣ�flash_unprotect
//�������أ���
//����˵����M�����Ᵽ����������
//���ܸ�Ҫ��flash�Ᵽ������
//˵        ����
//======================================================================
void flash_unprotect(uint8_t M)
{
    uint32_t temp;
    
    temp = 0xff00ffff;
    
    if((FLASH->CR & FLASH_CR_OPTLOCK) != 0U)
    {
        FLASH->OPTKEYR = (uint32_t)FLASH_OPTKEY1;
        FLASH->OPTKEYR = (uint32_t)FLASH_OPTKEY2;
    }
    while( (FLASH->SR & FLASH_SR_BSY) != 0U);
    //������ؼĴ���
    FLASH->WRP1AR &= 0x0;
    FLASH->WRP1AR |= temp;
    FLASH->CR |= FLASH_CR_OPTSTRT;
    while( (FLASH->SR & FLASH_SR_BSY) != 0U);
    FLASH->CR &= ~FLASH_CR_OPTSTRT;
}

//======================================================================
//�������ƣ�flash_isempty
//�������أ�1=Ŀ������Ϊ�գ�0=Ŀ������ǿա�
//����˵������Ҫ̽���flash�����ʼ��ַ
//���ܸ�Ҫ��flash�пղ���
//======================================================================

uint8_t flash_isempty(uint16_t sect,uint16_t N)
{
    uint16_t i,flag;
    uint8_t dest[N];
    uint8_t *src;
    flag = 1;
    src=(uint8_t *)(FLASH_BASE+sect*FLASH_PAGE_SIZE);
    memcpy(dest,src,N);
    for(i = 0; i<N; i++)   //�����������ֽ�
    {
        if(dest[i]!=0xff)   //�ǿ�
        {
            flag=0;
            break;
        }
    }
    return flag;
}
//========================================================================
//�������ƣ�flashCtl_isSectorProtected
//�������أ�1=������������0=����δ������
//����˵������Ҫ��������
//���ܸ�Ҫ���ж�flash�����Ƿ񱻱���
//=========================================================================
uint8_t flash_isSectorProtected(uint16_t sect)
{
    uint8_t STRT,END;
    uint32_t temp;
    temp = FLASH->WRP1AR;
    STRT = temp;
    END = temp>>16;
    if(sect>=STRT && sect<END)
    return 1;
    
    temp = FLASH->WRP1BR;
    STRT = temp;
    END = temp>>16;
    if(sect>=STRT && sect<END)
    return 1;
    
    return 0;
}

//----------------------����Ϊ�ڲ�������Ŵ�----------------------------
//======================================================================
//�������ƣ�flash_write_DoubleWord
//�������أ�0-�ɹ� 1-ʧ��
//����˵����addr��Ŀ���ַ��Ҫ��Ϊ4�ı����Ҵ���Flash�׵�ַ
//              �����磺0x08000004��Flash�׵�ַΪ0x08000000��
//       data��д���˫��
//���ܸ�Ҫ��Flash˫��д�������STM32L433ÿ��ֻ��ʵ��˫��д�룬��д��λ�֣���д��λ�֣�
//======================================================================
uint8_t flash_write_DoubleWord(uint32_t addr,uint32_t data_l,uint32_t data_h)
{
    //�����ݻ�����
    if((FLASH->ACR & FLASH_ACR_DCEN) != 0U)
    {
        FLASH->ACR &= ~FLASH_ACR_DCEN;
    }
    
    //ʹ��Flash��ʱ���
    FLASH->CR |= FLASH_CR_PG;
    
    //��д���λ��
    *(__IO uint32_t*)addr = data_l;
    
    //��д���λ��
    *(__IO uint32_t*)(addr+4U) = data_h;
    
    //��ֹFlash��ʱ���
    FLASH->CR &= ~FLASH_CR_PG;
    
    return 0;    //���سɹ�
}
#endif


//======================================================================
//�������ƣ�flash_Best
//�������أ�0-�ɹ� 1-ʧ��
//����˵����sect:��д��������
//			offset:��д������λ�õ�ƫ�Ƶ�ַ
//			N����д�������ֽ���
//			buf:��д�����ݵ��׵�ַ
//���ܸ�Ҫ����λ��ַ�����������µ�����д��
//======================================================================
uint8_t flash_Best(uint16_t sect,uint16_t offset,uint16_t N,uint8_t *buf)
{
    uint32_t temp_l,temp_h;
    uint32_t addr;
    uint16_t i;
    while( (FLASH->SR & FLASH_SR_BSY) != 0U);
    //����˫��д����Ե�ַ
    addr = (uint32_t)(FLASH_BASE+sect*FLASH_PAGE_SIZE+offset);
    //ѭ��д��˫�֣�ÿ8����дһ��
    for(i = 0; i < N; i+=8)
    {
        //��λ�ָ�ֵ
        temp_l = (uint32_t)((buf[i])|(buf[i+1]<<8)|(buf[i+2]<<16)|(buf[i+3]<<24));
        //��λ�ָ�ֵ
        temp_h = (uint32_t)((buf[i+4])|(buf[i+5]<<8)|(buf[i+6]<<16)|(buf[i+7]<<24));
        //�ھ��Ե�ַ(addr+i)��ʵ��˫��д��
        flash_write_DoubleWord((addr+i),temp_l,temp_h);
    }
    while( (FLASH->SR & FLASH_SR_BSY) != 0U);
    return 0;
}






