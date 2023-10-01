/*
 * valueType.c
 *
 *  Created on: 2018��5��9��
 *      Author: 13341
 */
#include "valueType.h"

//=====================================================================
//�������ƣ�IntConvertToStr
//�������أ���
//����˵����num����ת��Ϊ�ַ��������֣�str���ַ���ת����ɺ�洢��λ�ã�
//���ܸ�Ҫ����ָ�����Ƶ�������תΪ�ַ���
//=====================================================================
uint8_t *IntConvertToStr(int num,uint8_t *buf)
{
	uint8_t *str;
	int temp;
	int sign = 0;                          //���num�ķ���
    uint8_t *p;
     str = buf;
     p = str;
	  /*�����Ļ�ȡ����ֵ���ı���*/
	  if (num < 0)
	  {
			 num = 0 - num;
			 sign = 1;
	  }
	  /*�����ӵ�λ�Ž��ַ���*/
	  do
	  {
			 temp = num % 10;    //ȡnum�����һλ
			 *p = temp + '0';
			 p++;
	  }while ((num /= 10) != 0);
	  /*�Ǹ�����ʱ����ӡ�-��*/
	  if (sign == 1)
	  {
			*(p++) = '-';
	  }
	   /*���ַ�����ĩβ��� ''/0*/
	  *p = '\0';
	  p--;
	  /*�ַ�������*/
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
//�������ƣ�DoubleConvertToStr
//�������أ���
//����˵����num����ת��Ϊ�ַ��������֣�n:����С��λ����str���ַ���ת����ɺ�洢��λ�ã�
//���ܸ�Ҫ����ָ�����Ƶĸ���������תΪ�ַ���
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
//�������ƣ�FloatConvertToStr
//�������أ�ת����ɺ����õ����ַ����׵�ַ����'\0'��β
//����˵����x����ת����˫���ȸ�������
//          m��ת������С����λ����
//          buf���ַ���ת����ɺ�洢��λ�ã�
//���ܸ�Ҫ����������תΪ�ַ���
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
