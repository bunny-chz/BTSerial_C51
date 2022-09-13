#include<reg52.h>
#include <stdio.h>              //printf头文件 
#define uc unsigned char   
#define uint unsigned int  
#include "uart.h"

#define RELOAD_COUNT 0xFA  
 
unsigned char receiveData;
  
void main()  
{  
	UART_Init();  
 
	while(1)  
	{  
		UART_SendString("1");//此处示例是通过串口不断发送"1",如果用于其他数据传输，请把这里的传输参数改为要传输的字符串
	}  
}  
void UART_Init(void)
{
	SCON|=0X50;			//设置为工作方式1
	TMOD|=0X20;			//设置计数器工作方式2
	PCON=0X80;			//波特率加倍
	TH1=RELOAD_COUNT;	//计数器初始值设置
	TL1=TH1;
	ES=0;				//关闭接收中断
	EA=1;				//打开总中断
	TR1=1;				//打开计数器
//	TI=1;          //发送中断标记位，如果使用printf函数的必须设置	
}

void UART_SendData(u8 dat)
{
	ES=0; //关闭串口中断
	TI=0; //清发送完毕中断请求标志位
	SBUF=dat; //发送
	while(TI==0); //等待发送完毕
	TI=0; //清发送完毕中断请求标志位
	ES=1; //允许串口中断
}

void UART_SendString(u8 *pbuf)
{
	while(*pbuf!='\0') //遇到空格跳出循环	
	{
		UART_SendData(*pbuf);
		
		pbuf++;	
	}
}

u8 UART_RX_BUF[UART_REC_LEN];     //接收缓冲,最大UART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 UART_RX_STA=0;       //接收状态标记	