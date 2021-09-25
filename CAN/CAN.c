#include "CAN.h"
#include "config.h"
#include "PLL.h"

extern void CAN_SendCallBack(void);
extern void CAN_GetCallBack(void);

void CAN_Init(CAN_InitType *cfg)	//初始化CAN
{
	if (CAN0CTL0_INITRQ == 0)
	{
		CAN0CTL0_INITRQ = 1;
	}
	while (CAN0CTL1_INITAK == 0)
	{

	}

	if (cfg->clock == CAN_CLK_OSC)		//选择系统时钟
	{
		CLKSEL_PLLSEL = 0;
	}
	else (cfg->clock == CAN_CLK_PLL)	//选择PLL时钟
	{
		CLKSEL_PLLSEL = 1;
	}

	CAN0BTR0_SJW = cfg->syn - 1;	//同步跳转宽度

	if (cfg->sp == 1)	//采样
	{
		CAN0BTR1_SAMP = 0;
	}
	else
	{
		CAN0BTR1_SAMP = 1;
	}

	if (cfg->bps == CAN_Bps_125)	//比特率
	{
		CAN0BTR1 |= 0x1D;
		CAN0BTR0_BRP = 0x0E;
	}
	else					//***
	{

	}

	CAN0IDMR0 = 0xFF;
	CAN0IDMR1 = 0xFF;
	CAN0IDMR2 = 0xFF;
	CAN0IDMR3 = 0xFF;
	CAN0IDMR4 = 0xFF;
	CAN0IDMR5 = 0xFF;
	CAN0IDMR6 = 0xFF;
	CAN0IDMR7 = 0xFF;
	CAN0CTL1 = 0xC0;	//使能MSCAN
	CAN0CTL0 = 0x00;	//返回一般运行模式

	while (CAN0CTL1_INITAK)
	{

	}
	while (CAN0CTL0_SYNCH == 0)
	{

	}

	CAN0RIER_RXFIE = 1;
}

Bool CAN_SendMsg(CAN_MsgType msg)  //CAN发送
{
	unsigned char send_buf = 0, sp;
	if (msg.len > MSG_MAX_LEN)
	{
		return FALSE;
	}
	if (CAN0CTL0_SYNCH == 0)
	{
		return FALSE;
	}

	do
	{
		CAN0TBSEL = CAN0TFLG; //选择缓冲器，最低置1位
		send_buf = CAN0TBSEL;
	} while (!send_buf);      //寻找空闲的缓冲器

	CAN0TXIDR0 = (unsigned char)(msg.id >> 21);      //写入标识符
	CAN0TXIDR1 = (unsigned char)(msg.id >> 13) & 0xE0;
	CAN0TXIDR1 |= 0x18;
	CAN0TXIDR1 |= (unsigned char)(msg.id >> 15) & 0x07;
	CAN0TXIDR2 = (unsigned char)(msg.id >> 7);
	CAN0TXIDR3 = (unsigned char)(msg.id << 1);

	if (msg.RTR)
	{
		CAN0TXIDR3 |= 0x01; //远程帧
	}

	for (sp = 0; sp < msg.len; sp++)
	{
		*((&CAN0TXDSR0) + sp) = msg.data[sp]; //写入数据
	}

	CAN0TXDLR = msg.len;  //写入数据长度
	CAN0TFLG = send_buf;  //清TXx标志

	return TRUE;
}

Bool CAN_GetMsg(CAN_MsgType *msg)    //CAN接收
{
	unsigned char sp;

	if (!CAN0RFLG_RXF)
	{
		return FALSE;
	}
	if (!CAN0RXIDR1_IDE)
	{
		return FALSE;
	}

	msg->id = ((unsigned long)(CAN0RXIDR0 & 0xff)) << 21;
	msg->id = msg->id | (((unsigned long)(CAN0RXIDR1 & 0xe0)) << 13);
	msg->id = msg->id | (((unsigned long)(CAN0RXIDR1 & 0x07)) << 15);
	msg->id = msg->id | (((unsigned long)(CAN0RXIDR2 & 0xff)) << 7);
	msg->id = msg->id | (((unsigned long)(CAN0RXIDR3 & 0xfe)) >> 1);

	if (CAN0RXIDR3 & 0x01)
	{
		msg->RTR = TRUE;
	}
	else
	{
		msg->RTR = FALSE;
	}

	msg->len = CAN0RXDLR_DLC;

	for ( sp = 0; sp < msg->len; sp++)
	{
		msg->data[sp] = *((&CAN0RXDSR0) + sp);
	}

	CAN0RFLG = 0x01;

	return TRUE;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED

void interrupt VectorNumber_Vcan0rx CAN_receive(void)
{
	CAN_GetCallBack();	//收到CAN报文触发中断
}

void interrupt VectorNumber_Vpit0 PIT0(void)
{
	CAN_SendCallBack();//PIT中断
}

#pragma CODE_SEG DEFAULT
