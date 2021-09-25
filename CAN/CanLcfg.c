#include "CanLcfg.h"
#include "CanMsg.h"
#include "PLL.h"
#include "derivative.h"

static long time;
long Tick = 0;
long lastTick = 0;
CanMsg msg_get;

CAN_InitType Lcfg =		//初始化CAN配置
{
	125,
	PLL,
	1,
	1
};

void CAN_SendCallBack(void)//1ms中断一次，每次Tick+1，与上次发送时间差33、66、100时分别发送相应报文，3个报文发送完成后lastTick=Tick
{
	Tick++;
	time = Tick - lastTick;
	if(time == 33)
	{
		CanMsg_Send(CanMsg1);
	} else if (time == 66)
	{
		CanMsg_Send(CanMsg2);
	} else if (time >= 100)
	{
		CanMsg_Send(CanMsg3);
		lastTick = Tick;
	}
	PITTF_PTF0 = 1;
}
void CAN_GetCallBack(void)
{
	if (CAN_GetMsg(&msg_get))             //判断是否有合法的标准帧收到
	{
		if (!CAN_SendMsg(msg_get))	//收到后发出去
		{
			;
		}
	} else
	{
		;
	}
}

