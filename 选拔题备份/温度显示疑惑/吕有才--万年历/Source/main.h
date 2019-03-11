#include<reg51.h>
//#include"12864.h"
//#include"pcf8591.h"

/*********************************************************/
#define uchar unsigned char
#define uint  unsigned int
uchar Time0[9],T[5],Data0[5];
uchar code  DIS1[] = {"DATE:"};
uchar code  DIS2[] = {"TIME:"};
uchar code  DIS3[] = {"TEMP:"};
uchar code  DIS4[] = {"AD1:"};
uchar DIS5[]={"°c"};
uchar DIS6[]={"."};
/*#define  PCF8591 0x90    //PCF8591 地址
unsigned char code Disp_Tab[] = {0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39}; 

unsigned char AD_CHANNEL;
unsigned long xdata  LedOut[8];
unsigned int  D[32];
sbit     SCL=P2^3;       //I2C  时钟 
sbit     SDA=P2^4;       //I2C  数据 
bit ack;  
/*******************************************************************
ADC????[??]????               
*******************************************************************/
/*bit ISendByte(unsigned char sla,unsigned char c)
{
   Start_I2c();              //????
   SendByte(sla);            //??????
   if(ack==0)return(0);
   SendByte(c);              //????
   if(ack==0)return(0);
   Stop_I2c();               //????
   return(1);
}
*******************************************************************/
/*bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val)
{
   Start_I2c();              //启动总线
   SendByte(sla);            //发送器件地址
   if(ack==0)return(0);
   SendByte(c);              //发送控制字节
   if(ack==0)return(0);
   SendByte(Val);            //发送DAC的数值  
   if(ack==0)return(0);
   Stop_I2c();               //结束总线
   return(1);
}

/*******************************************************************
ADC发送字节[命令]数据函数               
*******************************************************************/
/*bit ISendByte(unsigned char sla,unsigned char c)
{
   Start_I2c();              //启动总线
   SendByte(sla);            //发送器件地址
   if(ack==0)return(0);
   SendByte(c);              //发送数据
   if(ack==0)return(0);
   Stop_I2c();               //结束总线
   return(1);
}
unsigned char IRcvByte(unsigned char sla);
*/
unsigned char code Seg_Data[]={	 //the information is showed in the digital tube,shows 0-F//共阳数码管的编码，并将数据定义在CODE区 
					        0xc0,/*0*/
					        0xF9,/*1*/
					        0xA4,/*2*/
					        0xB0,/*3*/
					        0x99,/*4*/
					        0x92,/*5*/
					        0x82,/*6*/
					        0xF8,/*7*/
					        0x80,/*8*/
					        0x90,/*9*/				  
							};
unsigned char checkday()                  //自动检查是否是闰年，并为对应的月份设置天数
{
	unsigned char day;
	unsigned int year;
	year=Time0[7]/16*1000+Time0[7]%16*100+Time0[6]/16*10+Time0[6]%16;
	
  if(((year%4==0)&&(year%100==0))||(year%400==0))//判断是否是闰年
 {
	  switch(Time0[4])
	{
		case 0x01: day=0x31;break;
		case 0x02: day=0x29;break;
		case 0x03: day=0x31;break;
		case 0x04: day=0x30;break;
		case 0x05: day=0x31;break;
		case 0x06: day=0x30;break;
		case 0x07: day=0x31;break;
		case 0x08: day=0x31;break;
		case 0x09: day=0x30;break;
		case 0x10: day=0x31;break;
		case 0x11: day=0x30;break;
		case 0x12: day=0x31;break;
	}
 }
 else
 {
 switch(Time0[4])
	{
		case 0x01: day=0x31;break;
		case 0x02: day=0x28;break;
		case 0x03: day=0x31;break;
		case 0x04: day=0x30;break;
		case 0x05: day=0x31;break;
		case 0x06: day=0x30;break;
		case 0x07: day=0x31;break;
		case 0x08: day=0x31;break;
		case 0x09: day=0x30;break;
		case 0x10: day=0x31;break;
		case 0x11: day=0x30;break;
		case 0x12: day=0x31;break;
	}
	}
 
 return(day);
}



unsigned char Time0[9],week[3],week0,DisplayData[8], Data0[5];
void readtime();
void Lcd12864Display();
void ClockPlay();
void timesetting();
void year(unsigned char k);//年加减
void month(unsigned char k);//月加减
void day(unsigned char k);
void hour(unsigned char k);
void min(unsigned char k);
void sec(unsigned char k);
void delay0(unsigned int n);

void LcdDisplayTemp0(int temp);
void delay2(unsigned int n)
{
	while(n--);
}
unsigned char keyboardscan()
{
	unsigned char board_h, board_l;
	P1=0x0f;
	board_h=P1&0x0f;
	if(board_h!=0x0f)
	{
		delay2(5000);
		board_h=P1&0x0f;
		if(board_h!=0x0f)
		{
			P1=board_h|0xf0;
			board_l=P1&0xf0;
			return(board_h+board_l);
		}
	}
	return(0xff);
}

/*********************************************************/
uchar code Photo1[] ={
      0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x01,0x3F,0xC0,
      0x80,0x42,0x04,0x20,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x8A,0x1F,
      0xFC,0x42,0x04,0xF8,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0x80,
      0x01,0xFF,0xDE,0x88,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x01,0x2A,0x87,
      0xF0,0xA2,0x0A,0xF8,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0x84,
      0x10,0xA2,0x0A,0x88,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x1F,
      0xFC,0xA2,0x0A,0xF8,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x9F,0x90,
      0x05,0x2F,0xCA,0xA4,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x03,
      0xE1,0xA8,0x4A,0xA8,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0xBF,0xC2,
      0x24,0x48,0x44,0x90,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x92,0x84,
      0x24,0xA8,0x4A,0xA8,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0xA6,0x58,
      0x3D,0x0F,0xD0,0xC4,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x1C,0xFF,0xC0,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x23,0x08,0x37,0x80,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x40,0x10,0x08,0x40,0x00,0xFF,0x90,
      0x10,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x81,0x86,0x10,0x40,0x00,0x08,0x08,
      0x10,0xFF,0x86,0x00,0x00,0x00,0x00,0x00,
      0x01,0x02,0x49,0x40,0x40,0x00,0x7F,0x0B,
      0xFC,0x08,0x0F,0x00,0x00,0x00,0x00,0x00,
      0x01,0x08,0x00,0x40,0x20,0x00,0x10,0x00,
      0x10,0x49,0x0F,0x00,0x00,0x00,0x00,0x00,
      0x02,0x08,0x00,0x20,0x20,0x01,0xFF,0xDD,
      0x10,0x2A,0x0F,0x00,0x00,0x00,0x00,0x00,
      0x04,0x31,0x83,0x20,0x20,0x00,0x20,0x04,
      0x91,0xFF,0xC6,0x00,0x00,0x00,0x00,0x00,
      0x04,0x52,0x44,0x90,0x20,0x00,0x7F,0x04,
      0x90,0x1C,0x06,0x00,0x00,0x00,0x00,0x00,
      0x09,0xA4,0x28,0x4C,0x10,0x00,0xA1,0x04,
      0x10,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,
      0x0E,0x44,0xE9,0xC3,0x90,0x01,0x3F,0x04,
      0x70,0x49,0x06,0x00,0x00,0x00,0x00,0x00,
      0x00,0x82,0xC5,0x81,0x70,0x00,0x21,0x0A,
      0x01,0x88,0xC6,0x00,0x00,0x00,0x00,0x00,
      0x01,0x01,0x83,0x00,0x80,0x00,0x3F,0x11,
      0xFC,0x08,0x00,0x00,0x00,0x00,0x00,0x00,
      0x01,0x0C,0x70,0x00,0x80,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x02,0x13,0x87,0x10,0x40,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x02,0x20,0x78,0xA0,0x40,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x02,0x20,0x00,0x60,0x40,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x02,0x21,0x80,0x60,0x40,0x00,0x00,0x71,
      0xEE,0x3C,0x00,0x00,0x00,0x00,0x00,0x00,
      0x01,0x11,0x98,0x90,0x80,0x00,0x00,0x8E,
      0x31,0xC6,0x00,0x00,0x00,0x00,0x00,0x00,
      0x01,0x08,0x18,0x80,0x80,0x00,0x01,0x24,
      0x24,0x83,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x96,0x01,0x01,0x00,0x00,0x01,0x40,
      0x28,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x49,0x86,0x03,0x00,0x00,0x01,0x40,
      0x28,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x34,0x78,0x8C,0x00,0x00,0x01,0x00,
      0x20,0x03,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x0E,0x01,0x30,0x00,0x00,0x00,0x80,
      0x30,0x06,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x71,0x87,0xCE,0x00,0x00,0x00,0x40,
      0x68,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0xE0,0x78,0x07,0x00,0x00,0x00,0x20,
      0xC4,0x18,0x00,0x00,0x00,0x00,0x00,0x00,
      0x01,0xAF,0xFF,0xC5,0x80,0x00,0x00,0x11,
      0x82,0x30,0x00,0x00,0x00,0x00,0x00,0x00,
      0x03,0xA9,0xB6,0x45,0xC0,0x00,0x00,0x0B,
      0x01,0x60,0x00,0x00,0x00,0x00,0x00,0x00,
      0x07,0x2F,0x03,0xC4,0xE0,0x00,0x00,0x06,
      0x00,0xC0,0x00,0x00,0x00,0x00,0x00,0x00,
      0x0E,0x16,0x01,0x88,0x70,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x0F,0x08,0x00,0x10,0xF0,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x0F,0x84,0x00,0x21,0xF0,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
      0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};
/******************************************************************************/
uchar code Photo2[] ={
/*--  调入了一幅图像：C:\Users\Administrator\Desktop\资料\自动化.bmp  --*/
/*--  宽度x高度=128x64  --*/
0x01,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,
0x07,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,
0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,
0x3F,0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,0xFC,
0x7F,0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0xFE,
0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0xFF,
0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7F,
0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,
0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0xF0,0x00,0x00,0x00,0x01,0x80,0x00,0x10,0x38,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0xE0,0x00,0x00,0x00,0x03,0x80,0x00,0x3C,0x30,0x00,0x00,0x07,
0xE0,0x00,0x00,0x01,0xC0,0x00,0x00,0x00,0x03,0x00,0x00,0x70,0x30,0x00,0x00,0x07,
0xE0,0x00,0x00,0x01,0x80,0x00,0x03,0xFF,0x03,0x00,0x00,0x60,0x70,0x00,0x00,0x07,
0xE0,0x00,0x00,0xFF,0xFF,0xF0,0x07,0xFF,0x07,0x00,0x00,0xE0,0x60,0x60,0x00,0x07,
0xE0,0x00,0x00,0xFF,0xFF,0xF0,0x00,0x00,0x06,0x00,0x01,0xC0,0x60,0xF0,0x00,0x07,
0xE0,0x00,0x00,0xC0,0x00,0x60,0x00,0x00,0xFF,0xF8,0x03,0x80,0xE1,0xE0,0x00,0x07,
0xE0,0x00,0x01,0xC0,0x00,0x60,0x00,0x01,0xFF,0xF8,0x07,0x80,0xC3,0x80,0x00,0x07,
0xE0,0x00,0x01,0x80,0x00,0xE0,0x00,0x00,0x0C,0x30,0x0F,0x80,0xC7,0x00,0x00,0x07,
0xE0,0x00,0x01,0x80,0x00,0xC0,0x3F,0xFE,0x0C,0x30,0x1F,0x01,0xDE,0x00,0x00,0x07,
0xE0,0x00,0x03,0xFF,0xFF,0xC0,0x3F,0xFE,0x18,0x70,0x3F,0x01,0xF8,0x00,0x00,0x07,
0xE0,0x00,0x03,0x00,0x01,0xC0,0x03,0x80,0x18,0x60,0xF7,0x01,0xF0,0x00,0x00,0x07,
0xE0,0x00,0x03,0x00,0x01,0x80,0x03,0x00,0x38,0x60,0x66,0x03,0xC0,0x00,0x00,0x07,
0xE0,0x00,0x07,0x00,0x01,0x80,0x06,0x00,0x30,0xE0,0x06,0x07,0x80,0x00,0x00,0x07,
0xE0,0x00,0x06,0x00,0x03,0x80,0x0E,0x20,0x70,0xC0,0x0E,0x1F,0x00,0x00,0x00,0x07,
0xE0,0x00,0x07,0xFF,0xFF,0x00,0x1C,0x70,0x61,0xC0,0x0C,0x7F,0x00,0x00,0x00,0x07,
0xE0,0x00,0x0F,0xFF,0xFF,0x00,0x18,0x70,0xE1,0x80,0x0D,0xF6,0x00,0x00,0x00,0x07,
0xE0,0x00,0x0C,0x00,0x07,0x00,0x30,0x70,0xC1,0x80,0x1D,0xC6,0x00,0x00,0x00,0x07,
0xE0,0x00,0x0C,0x00,0x06,0x00,0x60,0xF1,0x83,0x80,0x19,0x0E,0x00,0x00,0x00,0x07,
0xE0,0x00,0x1C,0x00,0x06,0x01,0xFF,0xF3,0x83,0x00,0x18,0x0C,0x00,0x00,0x00,0x07,
0xE0,0x00,0x18,0x00,0x0E,0x01,0xFE,0x3F,0x03,0x00,0x38,0x0C,0x07,0x00,0x00,0x07,
0xE0,0x00,0x1F,0xFF,0xFC,0x01,0x80,0x2E,0x06,0x00,0x30,0x1C,0x07,0x00,0x00,0x07,
0xE0,0x00,0x3F,0xFF,0xFC,0x00,0x00,0x1C,0x0E,0x00,0x30,0x1C,0x0E,0x00,0x00,0x07,
0xE0,0x00,0x30,0x00,0x1C,0x00,0x00,0x38,0xFC,0x00,0x70,0x1F,0xFC,0x00,0x00,0x07,
0xE0,0x00,0x70,0x00,0x18,0x00,0x00,0xF0,0x78,0x00,0x60,0x1F,0xF8,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xE0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,
0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0F,
0xF0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,
0xFC,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,
0xFE,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFF,
0xFF,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0xFE,
0x7F,0xF8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x1F,0xFC,
0x1F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,
0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xE0,
0x03,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xC0,
0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x00

};