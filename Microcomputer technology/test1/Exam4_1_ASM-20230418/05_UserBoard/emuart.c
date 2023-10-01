///=====================================================================
//文件名称：emuart.c文件
//制作单位：SD-Arm(sumcu.suda.edu.cn)
//更新记录：20181201-20200627
//移植规则：【固定】
///=====================================================================
#include "emuart.h"

//帧头为0xa5,0x06；帧尾为0xb6,0x07
static uint8_t emuartTerminStr1[6] ="StOpU";  //uecom终结组帧字符串
static uint8_t emuartFrameHead[2] = {0xa5,0x06};  //帧头
static uint8_t emuartFrameTail[2] = {0xb6,0x07};  //帧尾
static uint8_t emuartTerminStr2[8] ="eMySeLf";  //uecom终结组帧字符串
//static uint8_t emuartTerminStr[13] ="StOpUeMySeLf";  //uecom终结组帧字符串
static uint8_t UART_NO;      //emuart使用的串口

//======================内部函数声明====================================
//在函数定义处有详细说明
void sendFrame(uint16_t length,uint8_t *data);
uint16_t crc16(uint8_t *ptr,uint16_t len);
//======================内部函数声明结束==================================

//=====================================================================
//函数名称：emuart_init
//函数返回： 无
//参数说明： uartNo：emuart使用的串口； baud：emuart的波特率。
//功能概要：初始化emuart
//更新记录：20180602，wb；
//=====================================================================
void emuart_init(uint8_t uartNo,uint32_t baud)
{
	uart_init(uartNo,baud);
	uart_enable_re_int(uartNo);
	UART_NO = uartNo;
}

//=====================================================================
//函数名称：emuart_send1
//函数返回： 无
//参数说明： a：待发送的一个字节数据
//功能概要：通过emuart发送一个字节数据
//更新记录：20180602，wb；
//=====================================================================
void emuart_send1(uint8_t a)
{
	sendFrame(1,&a);
}

//=====================================================================
//函数名称：emuart_sendN
//函数返回： 无
//参数说明： len：待发送数组的长度；buff：待发送数据缓冲区
//功能概要：通过emuart发送一个字节数组
//更新记录：20180602，wb；
//=====================================================================
void emuart_sendN(uint16_t len ,uint8_t* buff)
{
	sendFrame(len,buff);
}

//=====================================================================
//函数名称：emuart_send_string
//函数返回： 无
//参数说明： buff：待发送的字符串
//功能概要：通过emuart发送一个字符串
//更新记录：20180602，wb；
//=====================================================================
void emuart_send_string(uint8_t * buff)
{
	uint16_t len=0;
	while(buff[len])len++;
	sendFrame(len,buff);
}

//===========================================================================
//函数名称：emuart_frame
//功能概要：组帧，将待组帧的数据加入帧中。本函数应被放置于中断处理程序中。
//参数说明：ch：串口接收到一个字节数据；数组data：存放接收到的数据。
//函数返回：0：未组帧成功；非0：组帧成功，且返回值为接收到的数据长度
//备注：十六进制数据帧格式
//      帧头       + 数据长度         + 有效数据   +CRC校验码 +  帧尾
//      emuartFrameHead(2字节)
//      len(2字节)
//      有效数据(N字节 N=len[0]*256+len[1])
//      CRC校验(2字节)
//      emuartFrameTail(2字节)
//===========================================================================
uint16_t emuart_frame(uint8_t ch, uint8_t *data)
{
	static uint16_t index = 1;
	static uint16_t length = 1;
	static uint8_t markPos=1;
	uint16_t ret_val;
	uint16_t i;
	uint8_t CRC_check[2];
	uint16_t crc;

	//(0)逐字符比较，判断输入字符是否为终结组帧字符190226hzx（2/2）------------
	if(markPos<=6)
	{
		if(ch == emuartTerminStr1[(markPos-1)])
		{
			markPos++;  //字符位置+1
			//判断是否比对成功，如成功则终结组帧过程
			if((markPos-1)==12)
			{
				markPos=1;
				index = 1;
				length = 1;
				ret_val = 0;
				goto uecom_recv_exit;
			}
		}
		else
		{
			//比对失败，重新进行比对
			if(ch == emuartTerminStr1[0])
				markPos=2;
			else
				markPos=1;
		}
	}
	else
	{
		if(ch == emuartTerminStr2[(markPos-7)])
		{
			markPos++;  //字符位置+1
			//判断是否比对成功，如成功则终结组帧过程
			if((markPos-1)==13)
			{
				markPos=1;
				index = 1;
				length = 1;
				ret_val = 0;
				goto uecom_recv_exit;
			}
		}
		else
		{
			//比对失败，重新进行比对
			if(ch == emuartTerminStr1[0])
				markPos=2;
			else
				markPos=1;
	}
	}
	


	//（1）若未接收到数据或者未遇到帧头，则退出并返回0  帧头长度为两个字节
	if(((index-1) == 0 && ch != emuartFrameHead[0]) ||
			((index-1) == 1 && ch != emuartFrameHead[1]))
	{
		index = 1;
		length = 1;
		ret_val = 0;     //接收数据错误
		goto uecom_recv_exit;
	}
	//（2）正确接收到了帧头，继续执行，将数据存入data数组
	data[(index++)-1] = ch;
	//（3）当获取到第四个数据时，求出有效数据长度


	if((index-1) == 4)
	{
		length = ((uint16_t)(data[2]<<8)) + data[3]+1;
	}
	//（4）如果接收到的数据达到一帧长度（帧长度=有效数据长度+8），进行CRC校验，
	//     如果校验通过将进行数据的处理。
	if((length-1) != 0 && (index-1) >= length+7)
	{
		//（4.1）对有效数据进行CRC校验
		crc = crc16((data+4),(length-1));
		CRC_check[0] = (crc>>8)&0xff;
		CRC_check[1] = crc&0xff;
		//（4.2）当未获取到帧尾或CRC校验出错，则出错返回0
		if(data[index-3]!=emuartFrameTail[0] || data[index-2]!= emuartFrameTail[1]//δ?????β
			||	CRC_check[0] != data[index-5] || CRC_check[1] != data[index-4])//CRC???????
		{
			//出错返回
			index = 1;
			length = 1;
			ret_val = 0;
			goto uecom_recv_exit;
		}
		//（4.3）将前4个字节移出buf数组，令buf数组全为有效数据，并返回有效数据
		for(i=0;i<(length-1);i++)
		{

			data[i] = data[i+4];
		}
		index = 1;
		ret_val = (length-1); //返回有效数据长度
		data[(length-1)] = 0; //令数组长度为0
		//（4.4）收到的数据若为上位机搜寻emuart设备的字符串，则进行响应
		if((length-1) == 21 &&
			!strcmp((const char*)data,"[Are you an emuart??]"))
		{
			emuart_send_string((uint8_t*)"[Yes,I am an emuart!!]");
			ret_val = 0;
		}
		length = 1; //令有效数据长度为0
		goto uecom_recv_exit;
	}
	ret_val = 0;
uecom_recv_exit:
    return ret_val;
}

//===========================================================================
//函数名称：emuart_frame
//功能概要：组帧，将待组帧的数据加入帧中。本函数应被放置于中断处理程序中。
//参数说明：ch：串口接收到一个字节数据；数组data：存放接收到的数据。
//函数返回：0：未组帧成功；非0：组帧成功，且返回值为接收到的数据长度
//备注：十六进制数据帧格式
//      帧头       + 数据长度         + 有效数据   +CRC校验码 +  帧尾
//      emuartFrameHead(2字节)
//      len(2字节)
//      有效数据(N字节 N=len[0]*256+len[1])
//      CRC校验(2字节)
//      emuartFrameTail(2字节)
//===========================================================================
uint16_t useremuart_frame(uint8_t ch, uint8_t *data)
{
	static uint16_t index = 1;
	static uint16_t length = 1;
	static uint8_t markPos=1;
	uint16_t ret_val;
	uint16_t i;
	uint8_t CRC_check[2];
	uint16_t crc;
    uint8_t imei[16];
	//(0)逐字符比较，判断输入字符是否为终结组帧字符190226hzx（2/2）------------
	if(markPos<=6)
	{
		if(ch == emuartTerminStr1[(markPos-1)])
		{
			markPos++;  //字符位置+1
			//判断是否比对成功，如成功则终结组帧过程
			if((markPos-1)==12)
			{
				markPos=1;
				index = 1;
				length = 1;
				ret_val = 0;
				goto uecom_recv_exit;
			}
		}
		else
		{
			//比对失败，重新进行比对
			if(ch == emuartTerminStr1[0])
				markPos=2;
			else
				markPos=1;
		}
	}
	else
	{
		if(ch == emuartTerminStr2[(markPos-7)])
		{
			markPos++;  //字符位置+1
			//判断是否比对成功，如成功则终结组帧过程
			if((markPos-1)==13)
			{
				markPos=1;
				index = 1;
				length = 1;
				ret_val = 0;
				goto uecom_recv_exit;
			}
		}
		else
		{
			//比对失败，重新进行比对
			if(ch == emuartTerminStr1[0])
				markPos=2;
			else
				markPos=1;
	}
	}
	


	//（1）若未接收到数据或者未遇到帧头，则退出并返回0  帧头长度为两个字节
	if(((index-1) == 0 && ch != emuartFrameHead[0]) ||
			((index-1) == 1 && ch != emuartFrameHead[1]))
	{
		index = 1;
		length = 1;
		ret_val = 0;     //接收数据错误
		goto uecom_recv_exit;
	}
	//（2）正确接收到了帧头，继续执行，将数据存入data数组
	data[(index++)-1] = ch;
	//（3）当获取到第四个数据时，求出有效数据长度


	if((index-1) == 4)
	{
		length = ((uint16_t)(data[2]<<8)) + data[3]+1;
	}
	//（4）如果接收到的数据达到一帧长度（帧长度=有效数据长度+8），进行CRC校验，
	//     如果校验通过将进行数据的处理。
	if((length-1) != 0 && (index-1) >= length+7)
	{
		//（4.1）对有效数据进行CRC校验
		crc = crc16((data+4),(length-1));
		CRC_check[0] = (crc>>8)&0xff;
		CRC_check[1] = crc&0xff;
		//（4.2）当未获取到帧尾或CRC校验出错，则出错返回0
		if(data[index-3]!=emuartFrameTail[0] || data[index-2]!= emuartFrameTail[1]//δ?????β
			||	CRC_check[0] != data[index-5] || CRC_check[1] != data[index-4])//CRC???????
		{
			//出错返回
			index = 1;
			length = 1;
			ret_val = 0;
			goto uecom_recv_exit;
		}
		//（4.3）将前4个字节移出buf数组，令buf数组全为有效数据，并返回有效数据
		for(i=0;i<(length-1);i++)
		{

			data[i] = data[i+4];
		}
		index = 1;
		ret_val = (length-1); //返回有效数据长度
		data[(length-1)] = 0; //令数组长度为0
		//（4.4）收到的数据若为上位机搜寻emuart设备的字符串，则进行响应
		if((length-1) == 45)
		{
		    if(!strcmp((const char*)(data+24),"[Are you an emuart??]"))
		    {
		        flash_read_physical((uint8_t*)imei,(MCU_SECTOR_NUM-1)*MCU_SECTORSIZE+MCU_FLASH_ADDR_START,16);
                if(!strncmp((char*)imei,(char*)data,16))
                {
                    emuart_send_string((uint8_t*)"[Yes,I am an emuart!!]");
			        
                }
                ret_val = 0;
		    }
		}
		length = 1; //令有效数据长度为0
		goto uecom_recv_exit;
	}
	ret_val = 0;
uecom_recv_exit:
    return ret_val;
}


//======以下为内部函数====================================================
//=====================================================================
//函数名称：sendFrame
//函数返回： 无
//参数说明： length：待发送数据的长度；data：待发送数据缓冲区。
//功能概要：通过emuart发送指定长度的字节数组。
//更新记录：20180602，wb；
//=====================================================================
void sendFrame(uint16_t length,uint8_t *data)
{
	uint16_t crc;
	//计算得到CRC校验码
	crc = crc16(data,length);
	//发送帧头
	uart_send1(UART_NO,emuartFrameHead[0]);
	uart_send1(UART_NO,emuartFrameHead[1]);
	//发送帧长
	uart_send1(UART_NO,length>>8);
	uart_send1(UART_NO,length);
	//发送帧数据
	uart_sendN(UART_NO,length,data);
    //发送校验码
	uart_send1(UART_NO,crc>>8);
	uart_send1(UART_NO,crc);
	//发送帧尾
	uart_send1(UART_NO,emuartFrameTail[0]);
	uart_send1(UART_NO,emuartFrameTail[1]);
}
//=====================================================================
//函数名称：crc16
//功能概要：将数据进行16位的CRC校验，返回校验后的结果值
//参数说明：ptr:需要校验的数据缓存区
//      len:需要检验的数据长度
//函数返回：计算得到的校验值?
//=====================================================================
uint16_t crc16(uint8_t *ptr,uint16_t len)
{
	uint16_t i,j,tmp,crc16;

	crc16 = 0xffff;
	for(i = (uint16_t)0;i < len;i++)
	{
		crc16 = (uint16_t)ptr[i]^crc16;
		for(j = 0;j< 8;j++)
		{
			tmp = crc16 & 0x0001;
			crc16 = crc16>>1;
			if(tmp)
				crc16 = crc16^0xa001;
		}
	}
	return crc16;
}
