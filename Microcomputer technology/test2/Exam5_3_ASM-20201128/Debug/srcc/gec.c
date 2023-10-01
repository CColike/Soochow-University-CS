//=====================================================================
//�ļ����ƣ�gec.c�ļ�
//������λ��SD-Arm(sumcu.suda.edu.cn)
//���¼�¼��20181201-20200627
//��ֲ���򣺡��̶���
//=====================================================================
#include "gec.h"
//======================================================================
//�������ƣ�Vectors_Init
//�������أ���
//����˵������
//���ܸ�Ҫ��User��BIOS�ж�������Ĳ��ּ̳�,�����⺯��ָ���ʼ��
//�޸���Ϣ��WYH��20200805���淶
//======================================================================
void  Vectors_Init()
{
    //���û����򣬱��뱾�δ���
    #if (GEC_USER_SECTOR_START!=0)   
    //��1����Flash����1������ǰ24�ֽ�Ϊ�գ���д���豸���кż�����汾�ų�ֵ
    if(flash_isempty(MCU_SECTOR_NUM-1,24))
    {
        flash_write_physical((MCU_SECTOR_NUM-1)*MCU_SECTORSIZE+
        MCU_FLASH_ADDR_START,24,(uint8_t *)"0123456789ABCDEF20200716");
    }
    //��2���̳�BIOS�Ĵ����ж�
    void ** bios=(void *)MCU_FLASH_ADDR_START;   //��������ʼ��ַ
    uint32_t user[MCU_SECTORSIZE/4];     //�������������
    //��ȡUSER�ж���������жϴ�������ַ����user����
    flash_read_physical((uint8_t *)user,GEC_USER_SECTOR_START*
    MCU_SECTORSIZE+MCU_FLASH_ADDR_START,MCU_SECTORSIZE);
    //�ж�USER�д��ڸ����ж��Ƿ�ΪBIOS��Ӧ�жϵ�ַ�����ǣ����������������޸�
    //ΪBIOS��Ӧ�жϵ�ַ
    if(user[BIOS_UART_UPDATE_IRQn] != (uint32_t)bios[BIOS_UART_UPDATE_IRQn])
    {
        //�ı�User�ж���������BIOS_UART�ж�����
        flash_erase(GEC_USER_SECTOR_START);
        //��USER�ж��������BIOS����д�봮�ڵ��жϴ�������ַ
        user[BIOS_UART_UPDATE_IRQn]=(uint32_t)bios[BIOS_UART_UPDATE_IRQn];
        user[BIOS_SVC_IRQn]=(uint32_t)bios[BIOS_SVC_IRQn];
		user[BIOS_PendSV_Handler]=(uint32_t)bios[BIOS_PendSV_Handler];
		user[BIOS_SysTick_Handler]=(uint32_t)bios[BIOS_SysTick_Handler];
        flash_write_physical(GEC_USER_SECTOR_START*MCU_SECTORSIZE+
        MCU_FLASH_ADDR_START,MCU_SECTORSIZE,(uint8_t *)user);
    }
    
    //��3���ж�������ָ���ض���USER������ж�������
    SCB->VTOR = (uint32_t)(GEC_USER_SECTOR_START*MCU_SECTORSIZE+
    MCU_FLASH_ADDR_START);  
    //��4����component_fun��ֵ��SYSTEM_FUNCTION������
    component_fun=(void **)(MCU_FLASH_ADDR_START+
    GEC_COMPONENT_LST_START*MCU_SECTORSIZE); 
    //��5��printf��ʾ
    printf("  ��User��ʾ����������User��main()ִ��...\r\n");
    
    #endif
}


//
//void SYSTEM_FUNCTION(uint8_t * data)
//{
//    uint8_t info[MCU_SECTORSIZE];
//    uint8_t i;
//    switch(data[0])
//    {
//        //�û�������£���λͣ����BIOS����bios�ӹ��ж��������ӹ��û������ж�
//        case 0:
//        if(strncmp((char *)(data+1),(char *)((MCU_SECTOR_NUM-1)*
//           MCU_SECTORSIZE+MCU_FLASH_ADDR_START+16),8) == 0)
//        {
//            emuart_sendN(4,(uint8_t *)"same");
//            break;
//        }
//        memcpy(component_fun[25],"user\0",5);   
//        NVIC_SystemReset();
//        break;
//        
//        //��Ϣ����
//        case 1:  
//        switch(data[1])
//        {
//            case 'r':
//            flash_read_physical((uint8_t *)info,(MCU_SECTOR_NUM-1)*
//                      MCU_SECTORSIZE+MCU_FLASH_ADDR_START,MCU_SECTORSIZE);
//            emuart_sendN(MCU_SECTORSIZE,(uint8_t *)(info));
//            break;
//            case 'w':
//            flash_erase(MCU_SECTOR_NUM-1);
//            flash_write_physical((MCU_SECTOR_NUM-1)*MCU_SECTORSIZE+
//                      MCU_FLASH_ADDR_START,MCU_SECTORSIZE,(uint8_t *)(data+2));
//            emuart_sendN(3,(uint8_t *)"get");
//            break;
//            default:
//            break;
//        }
//        break;
//        case 9:
//        emuart_sendN(19,(uint8_t *)MCU_TYPE);
//        break;
//        case 20:             //��̬����д��
//        i=0;
//        if(gcRecvLen==24)    //1֡ͷ+4�ֽ�CRC32У��+2����
//        {
//            gcRecvDCLen=gcRecvBuf[5+17]*256+gcRecvBuf[6+17];
//            if(gcRecvDCLen>((GEC_DYNAMIC_END-GEC_DYNAMIC_START+1)*
//            MCU_SECTORSIZE))    //������������
//            {
//                gcRecvDCLen=0xFFFF;
//                emuart_sendN(2,(uint8_t *)"no");
//                break;
//            }
//            else
//            {
//                emuart_sendN(3,(uint8_t *)"new");
//                for(i=GEC_DYNAMIC_START;i<=GEC_DYNAMIC_END;i++)
//                {
//                    flash_erase(i);
//                }
//                gcRecvDCLen=0;
//                break;
//            }
//            break;
//        }
//        else
//        {
//            if(gcRecvDCLen==(gcRecvBuf[5+17]*256+gcRecvBuf[6+17]+24-gcRecvLen))
//            {
//                emuart_sendN(2,(uint8_t *)"ok");
//            }
//            else
//            {
//                emuart_sendN(3,(uint8_t *)"get");
//            }
//            flash_write_physical((GEC_DYNAMIC_START+(gcRecvDCLen/MCU_SECTORSIZE))*
//                MCU_SECTORSIZE+gcRecvDCLen-(gcRecvDCLen/MCU_SECTORSIZE)*MCU_SECTORSIZE,
//                gcRecvLen-17-7,(uint8_t *)(gcRecvBuf+7+17));
//            gcRecvDCLen+=(gcRecvLen-7-17);
//            break;
//        }
//        break;
//    }
//    return;
//}
