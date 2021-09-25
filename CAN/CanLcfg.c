#include "CanLcfg.h"
#include "CanMsg.h"
#include "PLL.h"
#include "derivative.h"

CAN_InitType CAN_InitLcfg =		//��ʼ��CAN����
{
	CAN_Bps_125,
	CAN_CLK_PLL,
	1,
	1
};

void CAN_SendCallBack(void)//1ms�ж�һ�Σ�ÿ��Tick+1�����ϴη���ʱ���33��66��100ʱ�ֱ�����Ӧ���ģ�3�����ķ�����ɺ�lastTick=Tick
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

	if (CAN_GetMsg(&msg_get))             //�ж��Ƿ��кϷ��ı�׼֡�յ�
	{
		if (!CAN_SendMsg(msg_get))	//�յ��󷢳�ȥ
		{

		}
	}
	else
	{

	}
}
