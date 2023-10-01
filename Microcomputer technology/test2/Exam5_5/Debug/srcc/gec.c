//=====================================================================
//文件名称：gec.c文件
//制作单位：SD-Arm(sumcu.suda.edu.cn)
//更新记录：20181201-20200627
//移植规则：【固定】
//=====================================================================
#include "gec.h"
//======================================================================
//函数名称：Vectors_Init
//函数返回：无
//参数说明：无
//功能概要：User对BIOS中断向量表的部分继承,构件库函数指针初始化
//修改信息：WYH，20200805，规范
//======================================================================
void  Vectors_Init()
{
    //有用户程序，编译本段代码
    #if (GEC_USER_SECTOR_START!=0)   
    //（1）若Flash倒数1扇区的前24字节为空，则写入设备序列号及软件版本号初值
    if(flash_isempty(MCU_SECTOR_NUM-1,24))
    {
        flash_write_physical((MCU_SECTOR_NUM-1)*MCU_SECTORSIZE+
        MCU_FLASH_ADDR_START,24,(uint8_t *)"0123456789ABCDEF20200716");
    }
    //（2）继承BIOS的串口中断
    void ** bios=(void *)MCU_FLASH_ADDR_START;   //向量表起始地址
    uint32_t user[MCU_SECTORSIZE/4];     //向量表变量数组
    //读取USER中断向量表各中断处理程序地址赋给user数组
    flash_read_physical((uint8_t *)user,GEC_USER_SECTOR_START*
    MCU_SECTORSIZE+MCU_FLASH_ADDR_START,MCU_SECTORSIZE);
    //判断USER中串口更新中断是否为BIOS对应中断地址。若是，则不作操作；否则修改
    //为BIOS对应中断地址
    if(user[BIOS_UART_UPDATE_IRQn] != (uint32_t)bios[BIOS_UART_UPDATE_IRQn])
    {
        //改变User中断向量表中BIOS_UART中断向量
        flash_erase(GEC_USER_SECTOR_START);
        //改USER中断向量表的BIOS程序写入串口的中断处理程序地址
        user[BIOS_UART_UPDATE_IRQn]=(uint32_t)bios[BIOS_UART_UPDATE_IRQn];
        user[BIOS_SVC_IRQn]=(uint32_t)bios[BIOS_SVC_IRQn];
		user[BIOS_PendSV_Handler]=(uint32_t)bios[BIOS_PendSV_Handler];
		user[BIOS_SysTick_Handler]=(uint32_t)bios[BIOS_SysTick_Handler];
        flash_write_physical(GEC_USER_SECTOR_START*MCU_SECTORSIZE+
        MCU_FLASH_ADDR_START,MCU_SECTORSIZE,(uint8_t *)user);
    }
    
    //（3）中断向量表指针重定向到USER程序的中断向量表
    SCB->VTOR = (uint32_t)(GEC_USER_SECTOR_START*MCU_SECTORSIZE+
    MCU_FLASH_ADDR_START);  
    //（4）给component_fun赋值，SYSTEM_FUNCTION函数用
    component_fun=(void **)(MCU_FLASH_ADDR_START+
    GEC_COMPONENT_LST_START*MCU_SECTORSIZE); 
    //（5）printf提示
    printf("  【User提示】：将进入User的main()执行...\r\n");
    
    #endif
}


//
//void SYSTEM_FUNCTION(uint8_t * data)
//{
//    uint8_t info[MCU_SECTORSIZE];
//    uint8_t i;
//    switch(data[0])
//    {
//        //用户程序更新，复位停留至BIOS，由bios接管中断向量表、接管用户串口中断
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
//        //信息更新
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
//        case 20:             //动态命令写入
//        i=0;
//        if(gcRecvLen==24)    //1帧头+4字节CRC32校验+2长度
//        {
//            gcRecvDCLen=gcRecvBuf[5+17]*256+gcRecvBuf[6+17];
//            if(gcRecvDCLen>((GEC_DYNAMIC_END-GEC_DYNAMIC_START+1)*
//            MCU_SECTORSIZE))    //超过长度限制
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
