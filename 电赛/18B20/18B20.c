#include<reg52.h>
#include"18B20.h"
#include"lcd.h"
/*******************************************************************************
* 函 数 名         : Delay1ms
* 函数功能		   : 延时函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/

void Delay1ms(uint y)
{
	uint x;
	for( ; y>0; y--)
	{
		for(x=110; x>0; x--);
	}
}
/*******************************************************************************
* 函 数 名         : Ds18b20Init
* 函数功能		   : 初始化
* 输    入         : 无
* 输    出         : 初始化成功返回1，失败返回0
*******************************************************************************/

uchar Ds18b20Init()
{
	uchar i;
	DSPORT = 0;			 //将总线拉低480us~960us
	i = 70;	
	while(i--);//延时642us
	DSPORT = 1;			//然后拉高总线，如果DS18B20做出反应会将在15us~60us后总线拉低
	i = 0;
	while(DSPORT)	//等待DS18B20拉低总线
	{
		Delay1ms(1);
		i++;
		if(i>5)//等待>5MS
		{
			return 0;//初始化失败
		}
	
	}
	return 1;//初始化成功
}

/*******************************************************************************
* 函 数 名         : Ds18b20WriteByte
* 函数功能		   : 向18B20写入一个字节
* 输    入         : com
* 输    出         : 无
*******************************************************************************/

void Ds18b20WriteByte(uchar dat)
{
	uint i, j;

	for(j=0; j<8; j++)
	{
		DSPORT = 0;	     	  //每写入一位数据之前先把总线拉低1us
		i++;
		DSPORT = dat & 0x01;  //然后写入一个数据，从最低位开始
		i=6;
		while(i--); //延时68us，持续时间最少60us
		DSPORT = 1;	//然后释放总线，至少1us给总线恢复时间才能接着写入第二个数值
		dat >>= 1;
	}
}
/*******************************************************************************
* 函 数 名         : Ds18b20ReadByte
* 函数功能		   : 读取一个字节
* 输    入         : com
* 输    出         : 无
*******************************************************************************/


uchar Ds18b20ReadByte()
{
	uchar byte, bi;
	uint i, j;	
	for(j=8; j>0; j--)
	{
		DSPORT = 0;//先将总线拉低1us
		i++;
		DSPORT = 1;//然后释放总线
		i++;
		i++;//延时6us等待数据稳定
		bi = DSPORT;	 //读取数据，从最低位开始读取
		/*将byte左移一位，然后与上右移7位后的bi，注意移动之后移掉那位补0。*/
		byte = (byte >> 1) | (bi << 7);						  
		i = 4;		//读取完之后等待48us再接着读取下一个数
		while(i--);
	}				
	return byte;
}
/*******************************************************************************
* 函 数 名         : Ds18b20ChangTemp
* 函数功能		   : 让18b20开始转换温度
* 输    入         : com
* 输    出         : 无
*******************************************************************************/

void  Ds18b20ChangTemp()
{
	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);		//跳过ROM操作命令		 
	Ds18b20WriteByte(0x44);	    //温度转换命令
//	Delay1ms(100);	//等待转换成功，而如果你是一直刷着的话，就不用这个延时了
   
}
/*******************************************************************************
* 函 数 名         : Ds18b20ReadTempCom
* 函数功能		   : 发送读取温度命令
* 输    入         : com
* 输    出         : 无
*******************************************************************************/

void  Ds18b20ReadTempCom()
{	

	Ds18b20Init();
	Delay1ms(1);
	Ds18b20WriteByte(0xcc);	 //跳过ROM操作命令
	Ds18b20WriteByte(0xbe);	 //发送读取温度命令
}
/*******************************************************************************
* 函 数 名         : Ds18b20ReadTemp
* 函数功能		   : 读取温度
* 输    入         : com
* 输    出         : 无
*******************************************************************************/

int Ds18b20ReadTemp()
{
	int temp = 0;
	uchar tmh, tml;
	Ds18b20ChangTemp();			 	//先写入转换命令
	Ds18b20ReadTempCom();			//然后等待转换完后发送读取温度命令
	tml = Ds18b20ReadByte();		//读取温度值共16位，先读低字节
	tmh = Ds18b20ReadByte();		//再读高字节
	temp = tmh;
	temp <<= 8;
	temp |= tml;
	return temp;
}









/*nsigned char Time0[9],week[3],week0,DisplayData[8], Data0[5],ADData[8];
/*unsigned char code Seg_Data[]={	 //the information is showed in the digital tube,shows 0-F//共阳数码管的编码，并将数据定义在CODE区 
					        0xc0,/*0*/
//					        0xF9,/*1*/
//				        0xA4,/*2*/
//				        0xB0,/*3*/
//				        0x99,/*4*/
//				        0x92,/*5*/
//0x82,/*6*/
	//				        0xF8,/*7*/
		//			        0x80,/*8*/
			//		        0x90,/*9*/				
					
/*							};
	LcdDisplayTemp0(Ds18b20ReadTemp());//显示温度
void LcdDisplayTemp0(int temp) 	 //lcd显示
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
			{	T[i]=0x30;break;}
			case 0xF8:
			{T[i]=0x36;break;}
			case 0x80:
			{T[i]=0x37;break;}
			case 0x90:
			{T[i]=0x38;break;}			
		}
	}
		   LCD1602_WriteInformation(0x01,0);	//清屏指令
	LCD1602_MoveToPosition(0,0);
           LCD1602_DisplayString(p2);
			 LCD1602_DisplayOneCharOnAddr(0,6,T[1]);
	  	LCD1602_DisplayOneCharOnAddr(0,7,T[2]);
	  	LCD1602_DisplayOneCharOnAddr(0,8,0x2e);//.
	  	LCD1602_DisplayOneCharOnAddr(0,9,T[3]);
       LCD1602_DisplayOneCharOnAddr(0,10,0x06);	//°c
}*/