/*
 * valueType.c
 *
 *  Created on: 2018年5月9日
 *      Author: 13341
 */
#include "valueType.h"

//=====================================================================
//函数名称：IntConvertToStr
//函数返回：无
//参数说明：num：待转换为字符串的数字；str：字符串转换完成后存储的位置；
//功能概要：将指定进制的整型数转为字符串
//=====================================================================
uint8_t *IntConvertToStr(int num,uint8_t *buf)
{
	uint8_t *str;
	int temp;
	int sign = 0;                          //标记num的符号
    uint8_t *p;
     str = buf;
     p = str;
	  /*负数的话取绝对值并改变标记*/
	  if (num < 0)
	  {
			 num = 0 - num;
			 sign = 1;
	  }
	  /*把数从低位放进字符串*/
	  do
	  {
			 temp = num % 10;    //取num的最后一位
			 *p = temp + '0';
			 p++;
	  }while ((num /= 10) != 0);
	  /*是负数的时候添加‘-’*/
	  if (sign == 1)
	  {
			*(p++) = '-';
	  }
	   /*给字符串的末尾添加 ''/0*/
	  *p = '\0';
	  p--;
	  /*字符串逆置*/
	  while(str < p)
	  {
		   *str = *str + *p;
		   *p = *str - *p;
		   *str = *str - *p;
		   str++;
		   p--;
	  }
	  return buf;
}

//=====================================================================
//函数名称：DoubleConvertToStr
//函数返回：无
//参数说明：num：待转换为字符串的数字；n:保留小数位数；str：字符串转换完成后存储的位置；
//功能概要：将指定进制的浮点数型数转为字符串
//=====================================================================
uint8_t *DoubleConvertToStr(double num,int n,uint8_t *buf)
{
    int     sumI;
    float   sumF;
    int     sign = 0;
    int     temp;
    int     count = 0;
    uint8_t *p;
    uint8_t *pp;
    uint8_t * str;
    str = buf;
    p = str;
    if(num < 0)
    {
        sign = 1;
        num = 0 - num;
    }
    sumI = (int)num;    //sumI is the part of int
    sumF = num - sumI;  //sumF is the part of float
    do
    {
        temp = sumI % 10;
        *(str++) = temp + '0';
    }while((sumI = sumI /10) != 0);
    if(sign == 1)
    {
        *(str++) = '-';
    }
    pp = str;
    pp--;
    while(p < pp)
    {
        *p = *p + *pp;
        *pp = *p - *pp;
        *p = *p -*pp;
        p++;
        pp--;
    }
    *(str++) = '.';     //point
    do
    {
        temp = (int)(sumF*10);
        *(str++) = temp + '0';

        if((++count) == n)
            break;

        sumF = sumF*10 - temp;

    }while(!(sumF > -0.000001 && sumF < 0.000001));
    *str = '\0';
    return buf;
}



//================================================================
//函数名称：FloatConvertToStr
//函数返回：转换完成后所得到的字符串首地址，以'\0'结尾
//参数说明：x：待转换的双精度浮点数；
//          m：转换后保留小数的位数；
//          buf：字符串转换完成后存储的位置；
//功能概要：将浮点数转为字符串
//=================================================================
char *FloatConvertToStr(float x,int num,char *buf)
{
    int     sumI,sign,temp,count;
    float   sumF;
    char *p;
    char *pp;
    char *str;
    //
    str = buf;
    p = str;
    //
    sign = 0;
    count = 0;
    //
    if(x < 0)
    {
        sign = 1;
        x = 0 - x;
    }
    sumI = (int)x;    //sumI is the part of int
    sumF = x - sumI;  //sumF is the part of float
    do
    {
        temp = sumI % 10;
        *(str++) = temp + '0';
    }while((sumI = sumI /10) != 0);
    if(sign == 1)
    {
        *(str++) = '-';
    }
    pp = str;
    pp--;
    while(p < pp)
    {
        *p = *p + *pp;
        *pp = *p - *pp;
        *p = *p -*pp;
        p++;
        pp--;
    }
    *(str++) = '.';     //point
    do
    {
        temp = (int)(sumF*10);
        *(str++) = temp + '0';

        if((++count) == num)
            break;

        sumF = sumF*10 - temp;

    }while(!(sumF > -0.000001 && sumF < 0.000001));
    *str = '\0';
    return buf;
}
