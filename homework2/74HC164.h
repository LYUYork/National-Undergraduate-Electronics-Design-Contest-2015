//#include<reg52.h>
sbit CLK=P2^0;    //串行时钟
sbit INPUT=P2^1;  //串行数据，接B或者A，这里我们接B
sbit A=P2^2;  //悬空的令一端(A或B),这里是A，接P22

void delay(unsigned int cnt) ;
void HC164(unsigned char temp);