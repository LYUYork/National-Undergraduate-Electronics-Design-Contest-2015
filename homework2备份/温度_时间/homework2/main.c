#include<reg52.h> 
#include"hc164.h"
#include"LCD1602.h"
#include"ds1302.h"
#include"74HC165.h"
#include"18B20.h"
unsigned char code ucInitTime[7]={0x55,0x46,0x17,0x21,0x01,0x01,0x13};
/* CLK=P2^0;    //串行时钟
 INPUT=P2^1;  //串行数据，接B或者A，这里我们接B
  sbit A=P2^2;  //悬空的令一端(A或B),这里是A，接P22
*/
void LcdDisplayTemp(int temp);
void readtime();
void LcdDisplay();
unsigned char Time0[9],week[3],week0,DisplayData[8], Data0[10],Time1[6];
//unsigned char Data0[10]={0x11,0x12,0x13,0x14,0X23,0X26,0X40};
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

void main()
{
	 //Timep[
	LCD1602_Init();
	//DS1302_SetInit(ucInitTime);
	Time0[7]=0X20;
	while(1)
	{
		readtime();
		LcdDisplay();
		LcdDisplayTemp(Ds18b20ReadTemp());
		switch(hc74_165())
		{
			case 0x7f:
			{LCD1602_DisplayOneCharOnAddr(1,9,'1');break;	}
			case 0xfe:
			{LCD1602_DisplayOneCharOnAddr(1,10,'2');break;	}
		}
	}
}

void readtime()
{    //DS1302_SetInit();
	   Time0[0]= (DS1302_ReadOneByteAtAddr(ADDR_SEC_R));
     Time0[1]= (DS1302_ReadOneByteAtAddr(ADDR_MIN_R));
     Time0[2]= (DS1302_ReadOneByteAtAddr(ADDR_HOUR_R));
     Time0[3]= (DS1302_ReadOneByteAtAddr(ADDR_DAY_R));
     Time0[4]= (DS1302_ReadOneByteAtAddr(ADDR_MONTH_R));
     Time0[5]= (DS1302_ReadOneByteAtAddr(ADDR_WEEK_R));
 	   Time0[6]= (DS1302_ReadOneByteAtAddr(ADDR_YEAR_R));
}

void LcdDisplay()
{  
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
						//显示 星期
			week0=('0'+Time0[5]%16);
			switch(week0)
			{
				case 0x31:
					{week[0]=0x4d;week[1]=0x4f;week[2]=0x4e;break;}//"MON";
				case 0x32:
					{week[0]=0x54;  week[1]=0x55; week[2]=0x45;break;}  //"TUE"
				case 0x33:
					{week[0]=0x57; week[1]=0x45; week[2]=0x44;break;}   //"WED"
				case 0x34:
					{week[0]=0x54;week[1]=0x48;week[2]=0x55;break;}   //"THU"
				case 0x35:
					{week[0]=0x46;week[1]=0x52;week[2]=0x49;break;}  //"FRI"
				case 0x36:
					{week[0]=0x53;week[1]=0x41;week[2]=0x54; break;}  //"SAT"
				case 0x37:  
					{week[0]=0x53;week[1]=0x55;week[2]=0x4e;break;} //"SUN"
			}
			LCD1602_DisplayOneCharOnAddr(0,13,week[0]);	//星期		
		  LCD1602_DisplayOneCharOnAddr(0,14,week[1]);	
		  LCD1602_DisplayOneCharOnAddr(0,15,week[2]);	 
			
	  	LCD1602_DisplayOneCharOnAddr(0,0,'0'+Time0[7]/16);
	    LCD1602_DisplayOneCharOnAddr(0,1,'0'+Time0[7]%16);
      LCD1602_DisplayOneCharOnAddr(0,2,('0'+Time0[6]/16));			//年
	   	LCD1602_DisplayOneCharOnAddr(0,3,('0'+Time0[6]%16));
	    LCD1602_DisplayOneCharOnAddr(0,4,(0x00));
			LCD1602_DisplayOneCharOnAddr(0,5,('0'+Time0[4]/16));			//月
			LCD1602_DisplayOneCharOnAddr(0,6,('0'+Time0[4]%16));
			LCD1602_DisplayOneCharOnAddr(0,7,(0x01));
			LCD1602_DisplayOneCharOnAddr(0,8,('0'+Time0[3]/16));			//日
			LCD1602_DisplayOneCharOnAddr(0,9,('0'+Time0[3]%16));	
			LCD1602_DisplayOneCharOnAddr(0,10,0x02);
			LCD1602_DisplayOneCharOnAddr(1,0,('0'+Time0[2]/16));				//时
			LCD1602_DisplayOneCharOnAddr(1,1,('0'+Time0[2]%16));				 
			LCD1602_DisplayOneCharOnAddr(1,2,(':'));
			LCD1602_DisplayOneCharOnAddr(1,3,('0'+Time0[1]/16));				//分
			LCD1602_DisplayOneCharOnAddr(1,4,('0'+Time0[1]%16));	
			LCD1602_DisplayOneCharOnAddr(1,5,(':'));
			LCD1602_DisplayOneCharOnAddr(1,6,('0'+Time0[0]/16));				//秒
			LCD1602_DisplayOneCharOnAddr(1,7,('0'+Time0[0]%16));

}

void LcdDisplayTemp(int temp) 	 //lcd显示
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
		switch(Seg_Data[Data0[i]])
		{
			case 0xc0:
			{T[i]=0x30;break;}
			case 0xF9:
			{T[i]=0x31;break;}
			case 0xA4:
			{T[i]=0x32;break;}
			case 0xB0:
			{T[i]=0x33;break;}
			case 0x99:
			{T[i]=0x34;break;}
			case 0x92:
			{	T[i]=0x35;break;}
			case 0x82:
			{	T[i]=0x36;break;}
			case 0xF8:
			{T[i]=0x37;break;}
			case 0x80:
			{T[i]=0x38;break;}
			case 0x90:
			{T[i]=0x39;break;}			
		}
	}
	/*lcd_wcmd(0x80); 
	 for(i=0;i<5;i++)
     {
       lcd_wdat(T[i]);
       delay0(30);
     }*/
			 LCD1602_DisplayOneCharOnAddr(1,11,T[1]);
	  	LCD1602_DisplayOneCharOnAddr(1,12,T[2]);
	  	LCD1602_DisplayOneCharOnAddr(1,13,0x2e);//.
	  	LCD1602_DisplayOneCharOnAddr(1,14,T[3]);
       LCD1602_DisplayOneCharOnAddr(1,15,0x06);	//°c
}


