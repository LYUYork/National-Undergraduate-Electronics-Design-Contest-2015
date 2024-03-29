#include<reg51.h>
#include<intrins.h>

#include"ds1302.h"

#include"12864.h"
#include"I2C.h"
#include"pcf8591.h"
#include"8DigitalTubeDisplay.h"
#include"main.h"
#include"18B20.h"
//#include"74HC165.h"
#define  NOP()   _nop_() 
//--定义全局变量


void main()
{
/*	while(1)
	{
		Lcd111DisplayTemp0(Ds18b20ReadTemp());
		for(i=0;i<5;i++)
		{
	   DisplayOneCharOnAddr(Data0[i],i);
		}
	}
*/
//  Time0[7]=0x20;
	TMOD=0x01;
	EA=1;ET0=1;
	TL0=0xc3;TH0=0xb7;
	TR0=0;
//	Relay=0;
	lcd_init(); 
/*	lcd_wcmd(0x80);	     lcd_wdat(0x30);
	lcd_wcmd(0x0d);      //显示开，关光标
    delay12(5);
	lcd_wcmd(0x90); lcd_wdat(0x30);

	while(1);*/
	//readtime();
//	ClockPlay();
  while(1)
	{
		LcdDisplayTemp0(DS18B20_ReadTemperature()
	}
}
/*		switch(keyboardscan(4))
		{
			case 0x7e: 
				{//n=0;
					n++;
					if(n==3) n=1;
					clr_screen();
					break;
				}
			case  0xbe: {n=4;clr_screen();break;}
		}
		switch(n)
		{
			case 1:{	readtime();Clock(); ClockPlay();break;}
			case 2:{LcdDisplayTemp0(DS18B20_ReadTemperature());ADDisplay();break;}
			case 4:{timesetting();clr_screen();break;}
     }
		
		//sec(1);// min(1);//hour(1);//day(1);//month(1);//year(1);
		//P1=hc74_165();
		//lcd_wcmd(0x80); lcd_wdat(T[3]);
   // LcdDisplayTemp0(Ds18b20ReadTemp());ADDisplay();
		//
		//	  readtime();
		//ClockPlay();
  	//
	 }  
}
*/
void LcdDisplayTemp0(int temp) 	 //lcd显示
{
	unsigned char i; unsigned char T[5];
   	float tp;  
	if(temp< 0)				//当温度值为负数
  	{
		DisplayData[0] = 0x40; 
		//因为读取的温度是实际温度的补码，所以减1，再取反求出原码
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算由�0.5，还是在小数点后面。
 
  	}
 	else
  	{			
		DisplayData[0] = 0x00;
		tp=temp;//因为数据处理有小数点所以将温度赋给一个浮点型变量
		//如果温度是正的那么，那么正数的原码就是补码它本身
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。
	}
	//P3=tp;

	Data0[0] = temp / 10000;
	Data0[1] = temp % 10000 / 1000;
	Data0[2] = temp % 1000 / 100 ;
	Data0[3] = temp % 100 / 10;
	Data0[4] = temp % 10;
  
	for(i=0;i<=4;i++)
	{
		switch(Data0[i])
		{
			case 0:
			{T[i]=0x30;break;}
			case 1:
			{T[i]=0x31;break;}
			case 2:
			{T[i]=0x32;break;}
			case 3:
			{T[i]=0x33;break;}
			case 4:
			{T[i]=0x34;break;}
			case 5:
			{	T[i]=0x35;break;}
			case 6:
			{	T[i]=0x36;break;}
			case 7:
			{T[i]=0x37;break;}
			case 8:
			{T[i]=0x38;break;}
			case 9:
			{T[i]=0x39;break;}			
		}
	}
	     lcd_pos(1,0);             //??????????
     for(i=0;i<5;i++)
     {
       lcd_wdat(DIS3[i]);
     }
		 lcd_wcmd(0x93);
		 lcd_wdat(T[0]);
	lcd_wdat(T[1]);
	lcd_wdat(T[2]);
	lcd_wdat(0x2e);
	lcd_wdat(T[3]);
	lcd_wdat(T[4]);//lcd_pos(3,0);
	lcd_wdat(0xa1);
	lcd_wdat(0xe3);
	lcd_wdat(0x63);
	/* for(i=1;i<5;i++)
     {
       lcd_wdat(T[i]);
       delay0(3);
     }
		  lcd_wdat(0x65);
*/
		 DisplayOneCharOnAddr((temp / 10000),0);
		 DisplayOneCharOnAddr((temp % 10000 / 1000),1);
		 DisplayOneCharOnAddr((temp % 1000 / 100),2);
		 DisplayOneCharOnAddr((temp % 10),3);
}
void delay_main(int ms)
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

void readtime()
{
	   Time0[0]= (DS1302_ReadOneByteAtAddr(ADDR_SEC_R));
     Time0[1]= (DS1302_ReadOneByteAtAddr(ADDR_MIN_R));
     Time0[2]= (DS1302_ReadOneByteAtAddr(ADDR_HOUR_R));
     Time0[3]= (DS1302_ReadOneByteAtAddr(ADDR_DAY_R));
     Time0[4]= (DS1302_ReadOneByteAtAddr(ADDR_MONTH_R));
     Time0[5]= (DS1302_ReadOneByteAtAddr(ADDR_WEEK_R));
 	   Time0[6]= (DS1302_ReadOneByteAtAddr(ADDR_YEAR_R));
}
void ClockPlay()
{   uchar i;
	
    	if((Time0[7]&0x0a)==0x0a)    
			{		
			  	Time0[7]=(Time0[7]&0xf0);
		  		Time0[7]+=0x10;
		  }
			if((Time0[7]&0x0f)==0x0f)
			{		
					Time0[7]=(Time0[7]&0xf0);
					Time0[7]+=0x09;
			}

     lcd_pos(1,0);             //设置显示位置为第一行
     for(i=0;i<5;i++)
     {
       lcd_wdat(DIS1[i]);
       delay_main(5);
     }
		 lcd_wcmd(0x91); 
		 lcd_wdat(0x30+Time0[7]/16);
     lcd_wdat(0x30+Time0[7]%16);
		 lcd_wdat(0x30+Time0[6]/16);
     lcd_wdat(0x30+Time0[6]%16);
		 lcd_wdat(0xc4);
		 lcd_wdat(0xea);
		 lcd_wdat(0x30+Time0[4]/16);
     lcd_wdat(0x30+Time0[4]%16);
		 lcd_wdat(0xd4);
		 lcd_wdat(0xc2);
		 lcd_wdat(0x30+Time0[3]/16);
     lcd_wdat(0x30+Time0[3]%16);
		 lcd_wdat(0xc8);
		 lcd_wdat(0xd5);
		 lcd_pos(3,0);           
     for(i=0;i<5;i++)
     {
       lcd_wdat(DIS2[i]);
       delay_main(5);
     }
		 //lcd_pos(4,0); 
		 lcd_wcmd(0x9B); 
		 lcd_wdat(0x30+Time0[2]/16);
     lcd_wdat(0x30+Time0[2]%16);

     lcd_wdat(':');
		 		 lcd_wcmd(0x9D); 
		 lcd_wdat(0x30+Time0[1]/16);
     lcd_wdat(0x30+Time0[1]%16);
		 lcd_wdat(':');
		 		 lcd_wcmd(0x9F); 
		 lcd_wdat(0x30+Time0[0]/16);
     lcd_wdat(0x30+Time0[0]%16);
}
void ADDisplay()
{int i;
	ISendByte(PCF8591,0x41);
  D[0]=IRcvByte(PCF8591)*2;  //ADC0 模数转换1  放大2倍显示
	LedOut[0]=Disp_Tab[D[0]%10000/1000];
     LedOut[1]=Disp_Tab[D[0]%1000/100];
     LedOut[2]=Disp_Tab[D[0]%100/10];
     LedOut[3]=Disp_Tab[D[0]%10];
	    lcd_pos(3,0);             //设置显示位置为第一行
     for(i=0;i<5;i++)
     {
       lcd_wdat(DIS4[i]);
       delay_main(5);
     }
		 lcd_wcmd(0x9C); 
		//lcd_wdat(LedOut[0]);
		 lcd_wdat(LedOut[1]);
		// 		 lcd_wdat(DIS6[0]);
		 //lcd_wdat(DIS6[1]);
		      lcd_wdat(0x2e);//.
		 lcd_wdat(LedOut[2]);

		 lcd_wdat(LedOut[3]);
		 lcd_wdat(0x56);//V

}
void delay0(unsigned int n)
{
	unsigned int k;
	for(k=2;k>0;k--)
	{
	  while(n--){NOP();}
	}
}

void delay10(unsigned int n)
{
	  while(n--);
}
void timesetting()
{
	while(1)
	{
		ClockPlay();
		lcd_wcmd(0x84); 
		for(a=0;a<7;a++)
		 {lcd_wdat(DIS5[a]);}
	switch(keyboardscan(4))
	{
			case 0x77:     //按下按键1，进入调试年
			{
				 while (1)
				 {
					 lcd_wcmd(0x92); lcd_wcmd(0x0d);  
						switch(keyboardscan(8))
					  {
							case 0x7d://按下K9，进入加1
						   { year(0);break;}
							case 0xbd:
					    	{year(1);break;}
					  }
				   if(keyboardscan(4)==0xed)
			     {lcd_wcmd(0x0c);break;}
				 }break;
			}
			case 0xb7://按下K2 进入调试月
			{
					while (1)
					{lcd_wcmd(0x94); lcd_wcmd(0x0d);  
						switch(keyboardscan(8))
					  {
						  case 0x7d://按下K9，进入加1
						      {   month(0);break;	}
						  case 0xbd:
                 {month(1);break;}
					  }
				   if(keyboardscan(4)==0xed)
			     {lcd_wcmd(0x0c);break;}
				 }break;
			}
			case 0xd7://按下K3 进入调试day
			{
					while (1)
					{lcd_wcmd(0x96); lcd_wcmd(0x0d);  
						switch(keyboardscan(8))
					  {
						   case 0x7d://按下K9，进入加1
						      {  day(0);break;	}
						   case 0xbd://K13
						      {day(1);break;}
					  }
				   if(keyboardscan(4)==0xed)
			     {lcd_wcmd(0x0c);break;}
				 }break;
			}
			case 0xe7://按下K4 进入调试hour
			{
					while (1)
					{lcd_wcmd(0x9B); lcd_wcmd(0x0d);  
						switch(keyboardscan(8))
					  {
						    case 0x7d://按下K9，进入加1
						        {  hour(0);break;}
						    case 0xbd:
						       {hour(1);break;}
					  }
				   if(keyboardscan(4)==0xed)
			     {lcd_wcmd(0x0c);break;}
				 }break;
			}
			case 0x7b://按下K5 进入调试min
			{
				while(1)
					{lcd_wcmd(0x9D); lcd_wcmd(0x0d);  
						switch(keyboardscan(8))
					  {
						    case 0x7d://按下K9，进入加1
						       {  min(0);break;	}
						    case 0xbd:
						       {min(1);break;}
					  }
				   if(keyboardscan(4)==0xed)
			     {lcd_wcmd(0x0c);break;}
				 }break;
			}
			case 0xbb://按下K6 进入调sec
			{
					while (1)
					{
						lcd_wcmd(0x9F); lcd_wcmd(0x0d);  
						switch(keyboardscan(8))
					  {
						     case 0x7d://按下K9，进入加1
						       { sec(0);break;	}
						     case 0xbd:
						       {sec(1);break;}
					  }
				   if(keyboardscan(4)==0xed)
			     {lcd_wcmd(0x0c);break;}
				 }break;
			}
   }
		if(keyboardscan(4)==0xee)
		{
				n=1; lcd_wcmd(0x0c);
				DS1302_WriteOneByteAtAddr(0x8e,0x00);								
				DS1302_SetInit(Time0);                 //对时钟进行设置
  			DS1302_WriteOneByteAtAddr(0x8e,0x80);
				break;
		}  //lcd_wcmd(0x0c);
 }
}
void year(unsigned char k)
{
	if(k==0)                //加一
	{	
		Time0[6]+=0x01;
		if(Time0[6]==0x9a)
		{
				Time0[6]=0x00;
				Time0[7]+=0x01;
				if((Time0[7]&0x0a)==0x0a)
				{		
						Time0[7]=(Time0[7]&0xf0);
						Time0[7]+=0x10;
			  }
		}
	  if((Time0[6]&0x0a)==0x0a)
		{		
				Time0[6]=(Time0[6]&0xf0);
				Time0[6]+=0x10;
     }	
	}
	if(k==1)                 //减一
	{
		 Time0[6]-=0x01;
		 if((Time0[6]&0x0f)==0x0f)
			{		
					Time0[6]=(Time0[6]&0xf0);
					Time0[6]+=0x09;
			}
			if(Time0[6]==0x00)
			{		
					Time0[6]=0x99;
					Time0[7]-=0x01;
				  if((Time0[7]&0x0f)==0x0f)
					{		
							 Time0[7]=(Time0[7]&0xf0);
							 Time0[7]+=0x09;
					}
			}	
	}
	lcd_wcmd(0x0d);      //显示开，关光标
  ClockPlay();
}

void month(unsigned char k)
{
	if(k==0)
	{
		Time0[4]+=0x01;
		if(Time0[4]==0x13)
		{
				Time0[4]=0x01;
		}
    if((Time0[4]&0x0a)==0x0a)
	  {		
			Time0[4]=(Time0[4]&0xf0);
			Time0[4]+=0x10;
	  }
   }
  if(k==1)
  {
	  Time0[4]-=0x01;
		if(Time0[4]==0x00)
		{		
				Time0[4]=0x12;
		}	
   if((Time0[4]&0x0f)==0x0f)
		{		
				Time0[4]=(Time0[4]&0xf0);
				Time0[4]+=0x09;
		}
  }
  ClockPlay();
}

void day(unsigned char k)
{
	 if(k==0)
	 {				
		 if(Time0[3]==checkday())
		 {		
			  Time0[3]=0x00;
		 }	
		Time0[3]+=0x01;
		if((Time0[3]&0x0a)==0x0a)
		{		
				Time0[3]=(Time0[3]&0xf0);
				Time0[3]+=0x10;
		}
	}
	if(k==1)
  {
		 if(Time0[3]==0x01)
			{		
					Time0[3]=checkday()+0x01;
			}	
      Time0[3]-=0x01;
			if((Time0[3]&0x0f)==0x0f)
			{		
			  	Time0[3]=(Time0[3]&0xf0);
					Time0[3]+=0x09;
			}
	}
  ClockPlay();
}
void hour(unsigned char k)
{
	 if(k==0)
	 {
		 Time0[2]+=0x01;
		 if(Time0[2]==0x24)
		 {
				Time0[2]=0x00;
		 }
		if((Time0[2]&0x0a)==0x0a)
		{		
				Time0[2]=(Time0[2]&0xf0);
				Time0[2]+=0x10;
		 }
	 }
	 if(k==1)	
		{
			if(Time0[2]==0x00)
			{		
					Time0[2]=0x24;
			}	
 			Time0[2]-=0x01;
			if((Time0[2]&0x0f)==0x0f)
			{		
					Time0[2]=(Time0[2]&0xf0);
					Time0[2]+=0x09;
			}	
		}
  ClockPlay();		
}

void min(unsigned char k)
{
	if(k==0)
	{
		Time0[1]+=0x01;
		if((Time0[1]&0x0a)==0x0a)
		{		
			 Time0[1]=(Time0[1]&0xf0);
			 Time0[1]+=0x10;
		}
		if(Time0[1]==0x60)
		{
				Time0[1]=0x00;
		}
	}
	if(k==1)
	{
		if(Time0[1]==0x00)
		{		
				Time0[1]=0x60;
		}
    Time0[1]-=0x01;
    if((Time0[1]&0x0f)==0x0f)
		{		
				Time0[1]=(Time0[1]&0xf0);
				Time0[1]+=0x09;
		}	
	}
  ClockPlay();
}
void sec(unsigned char k)
{
	if(k==0)
	{
		Time0[0]+=0x01;
		if((Time0[0]&0x0a)==0x0a)
		{		
			 Time0[0]=(Time0[0]&0xf0);
			Time0[0]+=0x10;
    }
		if(Time0[0]==0x60)
		{
					Time0[0]=0x00;
		}
	}
	if(k==1)
  {
		if(Time0[0]==0x00)
		{		
				Time0[0]=0x60;
		}	
    Time0[0]-=0x01;
		if((Time0[0]&0x0f)==0x0f)
		{		
					Time0[0]=(Time0[0]&0xf0);
					Time0[0]+=0x09;
		}	
	}
  ClockPlay();
}

void relaywork(unsigned char k)
{
	switch(k)
	{
	   case 0:
		 {	Relay=1;break;}
     case 1:
		 {  Relay=0;break;}
	 }
}

void Clock()
{
		if(Time0[1]==clock1[0])
			{
					if(Time0[2]==clock1[1])
					{
							if(Time0[0]==0x00)
							{relaywork(0);TR0=1;clock_num=0;}
					}
			}
			if (Time0[1]==clock2[0])
			{
					if(Time0[2]==clock2[1])
					{
							if(Time0[0]==0x00)
							{relaywork(0);TR0=1;clock_num=0;}
					}
			}
			if (Time0[1]==clock3[0])
			{
					if(Time0[2]==clock3[1])
					{
							if(Time0[0]==0x00)
							{relaywork(0);TR0=1;clock_num=0;}
					}
			}
			if (Time0[1]==clock4[0])
			{
					if(Time0[2]==clock4[1])
					{
							if(Time0[0]==0x00)
							{relaywork(0);TR0=1;clock_num=0;}
					}
			}
			if (Time0[1]==clock5[0])
			{
					if(Time0[2]==clock5[1])
					{
							if(Time0[0]==0x00)
							{relaywork(0);TR0=1;clock_num=0;}
					}
			}
			if (Time0[1]==clock6[0])
			{
					if(Time0[2]==clock6[1])
					{
							if(Time0[0]==0x00)
							{relaywork(0);TR0=1;clock_num=0;}
					}
			}
			if (Time0[1]==clock7[0])
			{
					if(Time0[2]==clock7[1])
					{
							if(Time0[0]==0x00)
							{relaywork(0);TR0=1;clock_num=0;}
					}
			}
			if (Time0[1]==clock8[0])
			{
					if(Time0[2]==clock8[1])
					{
							if(Time0[0]==0x00)
							{relaywork(0);TR0=1;clock_num=0;}
					}
			}
}

void time_interrupt()   interrupt 1
{
	clock_num++;
	TL0=0xc3;TH0=0xb7;
	if(clock_num==1000)
	{
		relaywork(1);
	}
}
void Lcd111DisplayTemp0(int temp) 	 //lcd显示
{
	unsigned char i; 
	unsigned char code  p2[]= "TEMP:";
   	float tp;  
	if(temp< 0)				//当温度值为负数
  	{
		DisplayData[0] = 0x40; 
		//因为读取的温度是实际温度的补码，所以减1，再取反求出原码
		temp=temp-1;
		temp=~temp;
		tp=temp;
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算由�0.5，还是在小数点后面。
 
  	}
 	else
  	{			
		DisplayData[0] = 0x00;
		tp=temp;//因为数据处理有小数点所以将温度赋给一个浮点型变量
		//如果温度是正的那么，那么正数的原码就是补码它本身
		temp=tp*0.0625*100+0.5;	
		//留两个小数点就*100，+0.5是四舍五入，因为C语言浮点数转换为整型的时候把小数点
		//后面的数自动去掉，不管是否大于0.5，而+0.5之后大于0.5的就是进1了，小于0.5的就
		//算加上0.5，还是在小数点后面。
	}
	//P3=tp;

	Data0[0] = temp / 10000;
	Data0[1] = temp % 10000 / 1000;
	Data0[2] = temp % 1000 / 100 ;
	Data0[3] = temp % 100 / 10;
	Data0[4] = temp % 10;
  
	
}