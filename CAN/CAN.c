#include "CAN.h"
#include "config.h"

void CAN_Init()//CAN初始化
{
	if (CAN0CTL0_INITRQ == 0)	//查询是否进入初始化
	{
		CAN0CTL0_INITRQ = 1;	//进入初始化
	}
	while (CAN0CTL1_INITAK == 0)//初始化握手标志，初始化模块使能
	{
		;
	}
	CAN0BTR0_SJW = 0;
	CAN0BTR0_BRP = 1;
	CAN0BTR1 = 0x1c;	//比特率:125Kbps

	CAN0IDMR0 = 0xFF;
	CAN0IDMR1 = 0xFF;
	CAN0IDMR2 = 0xFF;
	CAN0IDMR3 = 0xFF;
	CAN0IDMR4 = 0xFF;
	CAN0IDMR5 = 0xFF;
	CAN0IDMR6 = 0xFF;
	CAN0IDMR7 = 0xFF;	//关闭滤波器

	CAN0CTL1 = 0xC0;  //使能MSCAN模块，使用总线时钟源
	CAN0CTL0 = 0x00;  //返回一般运行模式
	while (CAN0CTL1_INITAK)  //等待回到一般运行模式
	{
		;
	}
	while (CAN0CTL0_SYNCH == 0)  //等待总线时钟同步
	{
		;
	}
}
Bool CAN_SendMsg(CanMsg msg)//CAN0发送函数
{
	unsigned char send_buf, sp;
	if (msg.len > MAX_LEN)
	{
		return FALSE;
	}
	if(CAN0CTL0_SYNCH == 0)
	{
		return FALSE;
	}
	send_buf = 0;
	do
	{
		CAN0TBSEL = CAN0TFLG; //选择缓冲器，最低置1位
		send_buf = CAN0TBSEL;
	}
	while (!send_buf);    //寻找空闲的缓冲器
	CAN0TXIDR0 = (unsigned char)(msg.id >> 21);      //写入标识符
	CAN0TXIDR1 = (unsigned char)(msg.id >> 13) & 0xE0;//写入CAN0TXIDR1前三位
	CAN0TXIDR1 |= 0x18;	//写入CAN0TXIDR1中间两位SRR、IDR
	CAN0TXIDR1 |= (unsigned char)(msg.id >> 15) & 0x07;//写入CAN0TXIDR1后三位
	CAN0TXIDR2 = (unsigned char)(msg.id >> 7);
	CAN0TXIDR3 = (unsigned char)(msg.id << 1);
	if(msg.RTR)
	{
		CAN0TXIDR3 |= 0x01; //远程帧
	}
	for(sp = 0; sp < msg.len; sp++)
	{
		*((&CAN0TXDSR0) + sp) = msg.data[sp]; //写入数据
	}
	CAN0TXDLR = msg.len;  //写入数据长度
	CAN0TFLG = send_buf;  //清TXEx标志（缓冲器准备发送）
	return TRUE;
}
