#include "CanLcfg.h"
#include "CanMsg.h"
#include "PLL.h"
#include "derivative.h"

CAN_InitType CAN_InitLcfg =		//初始化CAN配置
{
	CAN_Bps_125,
	CAN_CLK_PLL,
	1,
	1
};

void CAN_SendCallBack(void)//1ms中断一次，每次Tick+1，与上次发送时间差33、66、100时分别发送相应报文，3个报文发送完成后lastTick=Tick
{
	static long can_send_tick = 0;
	static long can_send_last_tick = 0;
	long time;

	can_send_tick++;
	time = can_send_tick - can_send_last_tick;

	if(time == 33)
	{
		CanMsg_Send(CAN_Msg1);
	}
	else if (time == 66)
	{
		CanMsg_Send(CAN_Msg2);
	}
	else if (time >= 100)
	{
		CanMsg_Send(CAN_Msg3);
		last_tick = tick;
	}
	else
	{

	}

	PITTF_PTF0 = 1;
}

void CAN_GetCallBack(void)
{
	CAN_MsgType msg_get;

	if (CAN_GetMsg(&msg_get))             //判断是否有合法的标准帧收到
	{
		if (!CAN_SendMsg(msg_get))	//收到后发出去
		{

		}
	}
	else
	{

	}
}
