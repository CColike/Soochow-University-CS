
#include "lcd.h"

uint32_t mypow(uint8_t m,uint8_t n);
void LCD_WR_DATA8(uint8_t da); //��������-8λ����
void LCD_WR_DATA(uint16_t da);
void LCD_WR_REG(uint8_t da);
void LCD_WR_REG_DATA(uint8_t reg,uint16_t da);
void Address_set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2);
extern void gpio_set(uint16_t port_pin, uint8_t state);
extern void gpio_init(uint16_t port_pin, uint8_t dir, uint8_t state);

//=====================================================================
//�������ƣ�Lcd_Init��
//�������أ���
//����˵������
//���ܸ�Ҫ��LCD��ʼ��
//�޸ļ�¼�����˻���2018��7��23�գ����ó������飬��LCD_Init���
//=====================================================================
const uint8_t cmdA[15]={0x0F,0x20,0x1E,0x09,0x12,0x0B,0x50,0XBA,
0x44,0x09,0x14,0x05,0x23,0x21,0x00};
const uint8_t cmdB[15]={0x00,0x19,0x19,0x00,0x12,0x07,0x2D,0x28,
0x3F,0x02,0x0A,0x08,0x25,0x2D,0x0F};
const uint8_t cmdC[4]={0x64,0x03,0X12,0X81};
int32_t k;		//���ڼ�¼�Ǽ�λ���������һ��������д���λ�ã���������16x16��Ӣ���ֺ�������8x16

void LCD_Init(void)     //LCD��ʼ��
{
    int i;
    for (i=0;i<=60000;i++) __asm("nop");
    gpio_init(LCD_RS,1,0);
    gpio_init(LCD_DC,1,0);
    gpio_init(LCD_CS,1,1);
    spi_init(LCD_SPI,1,2000,0,0);
    for (i=0;i<=60000;i++) __asm("nop");

    LCD_WR_REG_DATA(0,0);
    gpio_set(LCD_RS,0);
    for (i=0;i<=3000;i++) __asm("nop");
    gpio_set(LCD_RS,1);
    for (i=0;i<=3000;i++) __asm("nop");

    LCD_WR_REG(0x36);    //�洢�����ʿ��ƣ���ʾ��������ʾд0x00/0x08,��ʾ��������ʾд0xD0/0xD8
    LCD_WR_DATA8(0x00);  //0x00��ST7789V����LCD��������ILI9341V�����ߵ�
    //0x08��ILI9341V����LCD��������ST7789V������ɫ�ߵ�
    LCD_WR_REG(0xB6);    //��ʾ���ܿ���
    LCD_WR_DATA8(0x0A);
    LCD_WR_DATA8(0xA2);

    LCD_WR_REG(0x3a);  //����RGBͼ�����ݸ�ʽ
    LCD_WR_DATA8(0x05);//16λ/����

    LCD_WR_REG(0x11);     //�˳�˯��ģʽ
    for (i=0;i<=20000;i++) __asm("nop");  //��ʱ
    LCD_Clear(GRAY);
    LCD_WR_REG(0x29);
}

//=====================================================================
//�������ƣ�LCD_Clear
//�������أ���
//����˵����background:������ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ��LCD����
//=====================================================================
void LCD_Clear(uint16_t background)  //LCD����
{
    uint16_t i,j;
    Address_set(0,0,LCD_W-1,LCD_H-1);
    for(i=0;i<LCD_W;i++)
    {
        for (j=0;j<LCD_H;j++) LCD_WR_DATA(background);
        wdog_feed();
    }
}


//=====================================================================
//�������ƣ�LCD_DrawPoint
//�������أ���
//����˵����x,y:������(240*320),
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ��λ�û�һ����
//=====================================================================
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)    //����
{
    Address_set(x,y,x,y);//���ù��λ��
    LCD_WR_DATA(color);
}


//=====================================================================
//�������ƣ�LCD_DrawPoint_big
//�������أ���
//����˵����x,y:������(240*320)
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ��λ�û�һ�����,���ķ�Χʵ����һ����x-1,y-1Ϊ���Ͻ⣬x+1,y+1Ϊ���½ǵ�С����
//       ����9���㣨3*3���Ĵ�㡣
//=====================================================================
void LCD_DrawPoint_big(uint16_t x,uint16_t y,uint16_t color) //��һ�����
{
    LCD_DrawSurface(x-1,y-1,x+1,y+1,color);
}

//=====================================================================
//�������ƣ�Draw_Circle
//�������أ���
//����˵����x,y:���ĵ�����(240*320),
//       r:Բ�İ뾶,
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ��λ�û�һ��ָ����С��Բ
//=====================================================================
void LCD_DrawCircle(uint16_t x,uint16_t y,uint8_t r,uint16_t color)    //��Բ
{
    int a,b;
    int di;
    a=0;b=r;
    di=3-(r<<1);             //�ж��¸���λ�õı�־
    while(a<=b)
    {
        LCD_DrawPoint(x-b,y-a,color);             //3
        LCD_DrawPoint(x+b,y-a,color);             //0
        LCD_DrawPoint(x-a,y+b,color);             //1
        LCD_DrawPoint(x-b,y-a,color);             //7
        LCD_DrawPoint(x-a,y-b,color);             //2
        LCD_DrawPoint(x+b,y+a,color);             //4
        LCD_DrawPoint(x+a,y-b,color);             //5
        LCD_DrawPoint(x+a,y+b,color);             //6
        LCD_DrawPoint(x-b,y+a,color);
        a++;
        //ʹ��Bresenham�㷨��Բ
        if(di<0)di +=4*a+6;
        else
        {
            di+=10+4*(a-b);
            b--;
        }
        LCD_DrawPoint(x+a,y+b,color);
    }
}


//=====================================================================
//�������ƣ�LCD_DrawRectangle
//�������أ���
//����˵����x1,y1:���Ͻǵ�����(240*320),x2,y2:���½ǵ�����(240*320),
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ�����Ͻ������½ǻ�һ��ָ��������ɫ�ľ���
//=====================================================================
void LCD_DrawRectangle(uint16_t x1, uint16_t y1,
uint16_t x2, uint16_t y2,uint16_t color)    //������
{
    LCD_DrawLine(x1,y1,x2,y1,color);
    LCD_DrawLine(x1,y1,x1,y2,color);
    LCD_DrawLine(x1,y2,x2,y2,color);
    LCD_DrawLine(x2,y1,x2,y2,color);
}


//=====================================================================
//�������ƣ�LCD_ShowCharactor
//�������أ���
//����˵����x,y:�������(240*320),index���������ֿ��е�����,fontcolor:������ɫ,
//       groundbackcolor:������ɫ��p:�ֿ���ʼ��ַ
//���ܸ�Ҫ����ָ��λ����ʾһ������(16*16��С),������Ҫ���д��ֿ���ȡ
//=====================================================================
void LCD_ShowCharactor(uint16_t  x,uint16_t y,uint16_t fontcolor,
uint16_t groundbackcolor,const char *p)    //��ʾ16*16����
{
    uint8_t i,j;
    const char *temp=p;
    Address_set(x,y,x+15,y+15); //��������
    for(j=0;j<32;j++)
    {
        for(i=0;i<8;i++)
        {
            if((*temp&(1<<i))!=0)
            LCD_WR_DATA(fontcolor);
            else

            LCD_WR_DATA(groundbackcolor);
        }
        temp++;
    }
}
//=====================================================================
//�������ƣ�LCD_showTitle
//�������أ���
//����˵����p:�ֿ���ʼ��ַ
//���ܸ�Ҫ����LCD��Ļ����ʾͷ�����ַ�����Ϣ
//=====================================================================
void LCD_showTitle(char *p)
{
    //��1������LCD��Ļ��ʾ��һ��
    LCD_aotu(2,2,238,318,1);               //LCDָ������͹��
    LCD_ShowString(4,15,RED,GRAY,p);       //����
    //��2������LCD��Ļ��ʾ�ڶ���
    LCD_aotu(2,43,238,318,0);             //LCDָ��������
}
//=====================================================================
//�������ƣ�LCD_showScreen_string
//�������أ���
//����˵����x,y:�������(240*320),p:�ֿ���ʼ��ַ
//���ܸ�Ҫ����ָ��λ����ʾ�ַ�������,������Ҫ���д��ֿ���ȡ
//=====================================================================
void LCD_showScreen_string(uint16_t  x,uint16_t y,const char *p)
{
    LCD_ShowString(x,y,BLACK,GRAY,p); //����Ļ��Ҫ��ʾ������
    k=6;							  //��Ҫ���µ�һ����ʾ����ʱ��x�����ʼֵ��Ҫˢ��
}


//=====================================================================
//�������ƣ�LCD_ShowString
//�������أ���
//����˵����x,y:�������(240*320),p:�ַ�����ʼ��ַ�����԰������ģ���Ӧ�����ں�����ģ�У�
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ��λ����ʾ�ַ�������ָ����ʾ������ɫ�ͱ�����ɫ��
//        ���Ĵ�СΪ��16*16��,Ӣ�Ĵ�СΪ��8*16��
//=====================================================================
void LCD_ShowString(uint16_t  x,uint16_t y,uint16_t fontcolor,
uint16_t groundbackcolor,const char *p)
{
    uint8_t i,j,k;
    const char *temp;
    k = 0;
    while(*p != 0)
    {
        wdog_feed();
        //DISABLE_INTERRUPTS;
        if(*p>=0x20 && *p<=0x7e)
        {
            temp=nAsciiDot;
            Address_set(x+8*k,y,x+7+8*k,y+15); //��������
            temp+=(*p-0x20)*16;
            for(j=0;j<16;j++)
            {
                for(i=0;i<8;i++)
                {
                    if((*temp&(1<<i))!=0)
                    {
                        LCD_WR_DATA(fontcolor);
                    }
                    else
                    {
                        LCD_WR_DATA(groundbackcolor);
                    }
                }
                temp++;
            }
            k++;
        }
        else if(*p > 0x7e)
        {
            wdog_feed();
            for(i=0;i<ChineseCharacterLength;i++)
            {
                uint8_t a = *p;
                uint8_t b = *(p+1);
                uint8_t c = GB_16[i].Index[0];
                uint8_t d = GB_16[i].Index[1];
                if( (a == c) && (b == d))
                {
                    LCD_ShowCharactor(x+8*k,y,fontcolor,groundbackcolor,GB_16[i].Msk);
                    break;
                }
            }
            k++;
        }
        p++;
        if (k>=30) break;
        //ENABLE_INTERRUPTS;
    }
}

//=====================================================================
//�������ƣ�LCD_aotu
//�������أ���
//����˵����x,y:��������(240*320),x1,y1:���½�����(240*320)
//���ܸ�Ҫ����ָ��λ����ʾһ����͹��ť
//=====================================================================
void LCD_aotu(uint16_t x,uint16_t y,uint16_t x1,uint16_t y1,uint8_t s) //��͹��ť
{
    uint8_t i,n;
    uint16_t color;
    color = GRAY;
    LCD_DrawSurface(x,y,x1,y1,color);
    n=2;
    color = BLACK;
    LCD_DrawLine(x,y,x1,y,color);
    LCD_DrawLine(x,y,x,y1,color);
    color = BLACK;
    LCD_DrawLine(x1,y,x1,y1,color);
    LCD_DrawLine(x,y1,x1,y1,color);

    for(i=1;i<n;i++)
    {

        color=(s==0?BLACK:WHITE);  //

        LCD_DrawLine(x+i,y+i,x1-i,y+i,color);
        LCD_DrawLine(x+i,y+i,x+i,y1-i,color);

        color=(s==0?WHITE:BLACK);

        LCD_DrawLine(x1-i,y+i,x1-i,y1-i,color);
        LCD_DrawLine(x+i,y1-i,x1-i,y1-i,color);
    };
};

//=====================================================================
//�������ƣ�LCD_DrawLine
//�������أ���
//����˵����x1,y1:�������(240*320),x2,y2:�յ�����(240*320),
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ����ָ������仭һ��ָ����ɫ��ֱ��
//=====================================================================
void LCD_DrawLine(uint16_t x1,uint16_t y1,
uint16_t x2, uint16_t y2,uint16_t color)    //����
{
    uint16_t t;
    int xerr=0,yerr=0,delta_x,delta_y,distance;
    int incx,incy,uRow,uCol;

    delta_x=x2-x1; //������������
    delta_y=y2-y1;
    uRow=x1;
    uCol=y1;
    if(delta_x>0)incx=1; //���õ�������
    else if(delta_x==0)incx=0;//��ֱ��
    else {incx=-1;delta_x=-delta_x;}
    if(delta_y>0)incy=1;
    else if(delta_y==0)incy=0;//ˮƽ��
    else{incy=-1;delta_y=-delta_y;}
    if( delta_x>delta_y)distance=delta_x; //ѡȡ��������������
    else distance=delta_y;
    for(t=0;t<=distance+1;t++ )//�������
    {
        LCD_DrawPoint(uRow,uCol,color);//����
        xerr+=delta_x ;
        yerr+=delta_y ;
        if(xerr>distance)
        {
            xerr-=distance;
            uRow+=incx;
        }
        if(yerr>distance)
        {
            yerr-=distance;
            uCol+=incy;
        }
    }
}

//=====================================================================
//�������ƣ�LCD_DrawSurface
//�������أ���
//����˵����x1,y1:�������(240*320),x2,y2:�յ�����(240*320),
//       color:��ɫ��ʹ�ñ��ļ��󻭱���ɫ�궨�壩
//���ܸ�Ҫ��ָ����ɫ����������Ҫȷ��x2>x1,y2>y1�������������ִ��
//=====================================================================
void LCD_DrawSurface(uint16_t x1,uint16_t y1,
uint16_t x2,uint16_t y2,uint16_t color)    //����������
{
    uint16_t i,j;
    Address_set(x1,y1,x2,y2);      //���ù��λ��
    for(i=y1;i<=y2;i++)
    {
        for(j=x1;j<=x2;j++)LCD_WR_DATA(color);//����
    }
}

//=====================================================================
//�������ƣ�LCD_ShowScreen_digital
//�������أ���
//����˵����y:���y����(240*320),num:�������������
//���ܸ�Ҫ����ָ��λ����ʾ���������е�����
//=====================================================================
void LCD_showScreen_digital(uint16_t y,const int num)
{
	uint8_t a[10]={0};
	if(num<10)
	{
	  	IntConvertToStr(num,a);
	  	LCD_ShowString(k,y,BLACK,GRAY,(char *)a);
	  	k=k+18;		//x���꣺8+10
	}
	if(num>9&&num<100)
	{
	  	IntConvertToStr(num,a);
	  	LCD_ShowString(k,y,BLACK,GRAY,(char *)a);
	  	k=k+26;		//x���꣺8+10+8
	}
	if(num>99&&num<1000)
	{
	  	IntConvertToStr(num,a);
	  	LCD_ShowString(k,y,BLACK,GRAY,(char *)a);
	  	k=k+34;		//x���꣺8+10+8+8
	}
}




//=====================================================================
//�ڲ�����
//=====================================================================

//=====================================================================
//�������ƣ�mypow
//�������أ�m^n
//����˵����m����,nָ��
//���ܸ�Ҫ������m^n
//=====================================================================
uint32_t mypow(uint8_t m,uint8_t n)
{
    uint32_t result;
    result=1;
    while(n--) result*=m;
    return result;
}
void LCD_WR_DATA8(uint8_t da) //��������-8λ����
{
    gpio_set(LCD_DC,1);
    gpio_set(LCD_CS,0);
    //	gpio_init(LCD_CS,1,0);
    spi_send1(LCD_SPI,da);
    gpio_set(LCD_CS,1);
    //	gpio_init(LCD_CS,1,1);
}
void LCD_WR_DATA(uint16_t da)
{
    gpio_set(LCD_DC,1);
    gpio_set(LCD_CS,0);
    //	gpio_init(LCD_CS,1,0);
    spi_send1(LCD_SPI,da>>8);
    spi_send1(LCD_SPI,da);
    gpio_set(LCD_CS,1);
    //    gpio_init(LCD_CS,1,1);
}
void LCD_WR_REG(uint8_t da)
{
    gpio_set(LCD_DC,0);
    gpio_set(LCD_CS,0);
    //	gpio_init(LCD_CS,1,0);
    spi_send1(LCD_SPI,da);
    //	gpio_init(LCD_CS,1,1);
    gpio_set(LCD_CS,1);
}
//void LCD_WR_REG_DATA(uint16_t reg,uint16_t da)
void LCD_WR_REG_DATA(uint8_t reg,uint16_t da)
{
    DISABLE_INTERRUPTS;
    LCD_WR_REG(reg);
    LCD_WR_DATA(da);
    ENABLE_INTERRUPTS;
}
void Address_set(uint16_t x1,uint16_t y1,uint16_t x2,uint16_t y2)
{
    LCD_WR_REG(0x2a);      //д�е�ַ����
    LCD_WR_DATA8(x1>>8);   //д��ʼ�е�ַ
    LCD_WR_DATA8(x1);
    LCD_WR_DATA8(x2>>8);   //д�����е�ַ
    LCD_WR_DATA8(x2);

    LCD_WR_REG(0x2b);     //д�е�ַ����
    LCD_WR_DATA8(y1>>8);  //д����ʼ��ַ
    LCD_WR_DATA8(y1);
    LCD_WR_DATA8(y2>>8);  //д�����е�ַ
    LCD_WR_DATA8(y2);

    LCD_WR_REG(0x2C);     //д�洢������
}








