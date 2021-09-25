#include "CanLcfg.h"
#include "CanMsg.h"
#include "PLL.h"
#include "derivative.h"

static long time;
long Tick = 0;
long lastTick = 0;
CanMsg msg_get;

CAN_InitType Lcfg =		//��ʼ��CAN����
{
	125,
	PLL,
	1,
	1
};

void CAN_SendCallBack(void)//1ms�ж�һ�Σ�ÿ��Tick+1�����ϴη���ʱ���33��66��100ʱ�ֱ�����Ӧ���ģ�3�����ķ�����ɺ�lastTick=Tick
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
	if (CAN_GetMsg(&msg_get))             //�ж��Ƿ��кϷ��ı�׼֡�յ�
	{
		if (!CAN_SendMsg(msg_get))	//�յ��󷢳�ȥ
		{
			;
		}
	} else
	{
		;
	}
}

