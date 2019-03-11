/*******************************************************************************
*  描述:                                                                       *
*      12864标准字库液晶演示 数据p0,控制p2  
*
*     LCD_PIN4(RS)     P2.6
*	  LCD_PIN5(RW)     P2.5
*     LCD_PIN6(E)      P2.7                                     
*
*	  LCD_PIN15(PSB)   P3.2
*	  LCD_PIN16(NC)	   P3.3
*	  LCD_PIN17(RST)   P3.4
********************************************************************************/
#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
/************* 12864LCD引脚定义 *************/
#define LCD_data  P0       //数据口
sbit LCD_RS  =  P3^4;      //寄存器选择输入 
sbit LCD_RW  =  P3^5;      //液晶读/写控制
sbit LCD_EN  =  P3^6;      //液晶使能控制
sbit LCD_PSB =  P3^7;      //串/并方式控制
//sbit LCD_RST =  P3^7;      //液晶复位端口


#define delayNOP(); {_nop_();_nop_();_nop_();_nop_();};
/*********************************************************/
uchar code  DIS1[] = {"    普中科技    "};
uchar code  DIS2[] = {"进入单片机世界  "};
uchar code  DIS3[] = {"www.prechin.com "};
uchar code  DIS4[] = {"TEL:755-29325187"};
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
/*******************************************************************/
/*                                                                 */
/*  延时函数                                                       */
/*                                                                 */
/*******************************************************************/
void delay(int ms)
{
    while(ms--)
	{
      uchar i;
	  for(i=0;i<150;i++)  
	   {
	    _nop_();			   
		_nop_();
		_nop_();
		_nop_();
	   }
	}
}	
/*******************************************************************/
/*                                                                 */
/*  延时函数                                                       */
/*                                                                 */
/*******************************************************************/
void delay1(int ms)
{
    while(ms--)
	{
      uchar y;
	  for(y=0;y<100;y++) ; 
	}
}			
/*******************************************************************/
/*                                                                 */
/*检查LCD忙状态                                                    */
/*lcd_busy为1时，忙，等待。lcd-busy为0时,闲，可写指令与数据。      */
/*                                                                 */
/*******************************************************************/
bit lcd_busy()
 {                          
    bit result;
    LCD_RS = 0;
    LCD_RW = 1;
    LCD_EN = 1;
    delayNOP();
    result = (bit)(P0&0x80);
    LCD_EN = 0;
    return(result); 
 }
/*******************************************************************/
/*                                                                 */
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
/*                                                                 */
/*******************************************************************/
void lcd_wcmd(uchar cmd)
{                          
   while(lcd_busy());
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    _nop_();
    _nop_(); 
    P0 = cmd;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*                                                                 */
/*******************************************************************/
void lcd_wdat(uchar dat)
{                          
   while(lcd_busy());
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
    delayNOP();
    LCD_EN = 1;
    delayNOP();
    LCD_EN = 0; 
}
/*******************************************************************/
/*                                                                 */
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 
    LCD_PSB = 1;         //并口方式
    
//	LCD_RST = 0;		 //液晶复位
//    delay(3);                   
//   LCD_RST = 1;      
//    delay(3);
    
    lcd_wcmd(0x34);      //扩充指令操作
    delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay(5);
    lcd_wcmd(0x0c);      //显示开，关光标
    delay(5);
    lcd_wcmd(0x01);      //清除LCD的显示内容
    delay(5);
}
/*********************************************************/
/*                                                       */
/* 设定显示位置                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==1)
     {X=0x80;}
   else if (X==2)
     {X=0x90;}
   else if (X==3)
     {X=0x88;}
   else if (X==4)
     {X=0x98;}
   pos = X+Y ; 
 
   lcd_wcmd(pos);     //显示地址
}
/*********************************************************
*                                                        *
* 闪烁函数                                               *
*                                                        *
*********************************************************/
void lcdflag() 
{
   lcd_wcmd(0x08);   
   delay(400);
   lcd_wcmd(0x0c);   
   delay(400);
   lcd_wcmd(0x08);   
   delay(400);
   lcd_wcmd(0x0c);   
   delay(400);
   lcd_wcmd(0x08);   
   delay(200); 
   lcd_wcmd(0x0c);   
   delay(5);
   lcd_wcmd(0x01);   
   delay(5);
}
/*********************************************************
*                                                        *
* 图形显示                                               *
*                                                        *
*********************************************************/
void photodisplay(uchar *bmp)	
{ 
  uchar i,j;

  lcd_wcmd(0x36);        //写数据时,关闭图形显示

  for(i=0;i<32;i++)
  {
    lcd_wcmd(0x80+i);    //先写入水平坐标值
    lcd_wcmd(0x80);      //写入垂直坐标值
    for(j=0;j<16;j++)   //再写入两个8位元的数据    
    lcd_wdat(*bmp++);     
    delay1(1000);
  }

  for(i=0;i<32;i++)
  { 
    lcd_wcmd(0x80+i);
    lcd_wcmd(0x88);
    for(j=0;j<16;j++)         
	lcd_wdat(*bmp++);    
	delay1(1000);
  }
  lcd_wcmd(0x36);       //写完数据,开图形显示 
}
/*********************************************************
*                                                        *
* 清屏函数                                               *
*                                                        *
*********************************************************/
void  clr_screen()
{
   lcd_wcmd(0x34);      //扩充指令操作
   delay(5);    
   lcd_wcmd(0x30);      //基本指令操作
   delay(5); 
   lcd_wcmd(0x01);      //清屏 
   delay(5);     
}
/**********************************************************
; 显示字符表代码
**********************************************************/
void  bytecode()
{
   uchar  s;
   clr_screen();          //清屏    
   lcd_wcmd(0x80);        //设置显示位置为第一行  
   for(s=0;s<16;s++)
   {
     lcd_wdat(0x30+s); 
   }
   lcd_wcmd(0x90);        //设置显示位置为第二行 
   for(s=0;s<16;s++)
   {
     lcd_wdat(0x40+s); 
   }
   lcd_wcmd(0x88);        //设置显示位置为第三行  
   for(s=0;s<16;s++)
   {
     lcd_wdat(0x50+s); 
   }
   lcd_wcmd(0x98);       //设置显示位置为第四行   
   for(s=0;s<16;s++)
   {
     lcd_wdat(0x60+s); 
   }
}
/*********************************************************
*                                                        *
* 主函数                                                 *
*                                                        *
*********************************************************/
void main()
{
   unsigned char code  hz[]={"中国"};
   uchar i;
   delay(100);                 //上电，等待稳定
   lcd_init();                 //初始化LCD
/*
   lcd_wcmd(0x81);       //设置显示位置为第四行
   lcd_wdat(hz[0]);   
   lcd_wdat(hz[1]);

   lcd_wcmd(0x92);       //设置显示位置为第四行
     
   lcd_wdat(hz[2]);   
   lcd_wdat(hz[3]);   
 
   while(1);
*/
   while(1)
   {

     lcd_pos(1,0);             //设置显示位置为第一行
     for(i=0;i<16;i++)
     {
       lcd_wdat(DIS1[i]);
       delay(30);
     }

     lcd_pos(2,0);             //设置显示位置为第二行
     for(i=0;i<16;i++)
     {
       lcd_wdat(DIS2[i]);
       delay(30);
     }
     lcd_pos(3,0);             //设置显示位置为第三行
     for(i=0;i<16;i++)
     {
       lcd_wdat(DIS3[i]);
       delay(30);
     }
     lcd_pos(4,0);             //设置显示位置为第四行
     for(i=0;i<16;i++)
     {
       lcd_wdat(DIS4[i]);
       delay(30);
     }
/*
	 while(1);
*/
     delay(1000);
     lcdflag();
     clr_screen();             //清屏        
     photodisplay(Photo1);     //显示图片1
     delay(2000);    
     clr_screen();             //清屏
     photodisplay(Photo2);     //显示图片2
     delay(2000);
     bytecode();               //显示字符表代码
     delay(2000);
     clr_screen();  
   }
}
/*********************************************************/




