/*******************************************************************************
*  描述:                                                                       *
*      12864标准字库液晶演示 数据p0,控制p2                                     *
********************************************************************************/
#include <reg51.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
/************* 12864LCD引脚定义 *************/
#define LCD_data  P0       //数据口
sbit LCD_RS  =  P2^6;      //寄存器选择输入 
sbit LCD_RW  =  P2^5;      //液晶读/写控制
sbit LCD_EN  =  P2^7;      //液晶使能控制
sbit LCD_PSB =  P3^2;      //串/并方式控制
//sbit LCD_RST =  P3^7;      //液晶复位端口


#define NOP(); {_nop_();_nop_();_nop_();_nop_();};
/*********************************************************/
uchar code  DIS1[] = {"    普中科技    "};
uchar code  DIS2[] = {"进入单片机世界"};
uchar code  DIS3[] = {"www.prechin.com "};
uchar code  DIS4[] = {"TEL:755-29325187"};
/*********************************************************/


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
    NOP();
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
    NOP();
    LCD_EN = 1;
    NOP();
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
    NOP();
    LCD_EN = 1;
    NOP();
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
 //   delay(3);                   
//    LCD_RST = 1;      
//    delay(3);
    
    lcd_wcmd(0x34);      //扩充指令操作
    delay(5);
    lcd_wcmd(0x30);      //基本指令操作
    delay(5);
    lcd_wcmd(0x0C);      //显示开，关光标
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

/*********************************************************
*                                                        *
* 主函数                                                 *
*                                                        *
*********************************************************/
void main()
{
   uchar i;
   delay(100);                 //上电，等待稳定
   lcd_init();                 //初始化LCD
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
     clr_screen(); //清屏函数，为下次刷新准备 
   }
}
/*********************************************************/




