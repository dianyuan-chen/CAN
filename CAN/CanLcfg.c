#include "CanLcfg.h"
#include "CanMsg.h"
#include "PLL.h"
#include "derivative.h"

CAN_InitType CAN_InitLcfg =		//³õÊ¼»¯CANÅäÖÃ
{
	CAN_Bps_125,
	CAN_CLK_PLL,
	1,
	1
};

void CAN_SendCallBack(void)//1msÖÐ¶ÏÒ»´Î£¬Ã¿´ÎTick+1£¬ÓëÉÏ´Î·¢ËÍÊ±¼ä²î33¡¢66¡¢100Ê±·Ö±ð·¢ËÍÏàÓ¦±¨ÎÄ£¬3¸ö±¨ÎÄ·¢ËÍÍê³ÉºólastTick=Tick
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
		can_send_last_tick = can_send_tick;
	}
	else
	{

	}

	PITTF_PTF0 = 1;
}

void CAN_GetCallBack(void)
{
	CAN_MsgType msg_get;

	if (CAN_GetMsg(&msg_get))             //ÅÐ¶ÏÊÇ·ñÓÐºÏ·¨µÄ±ê×¼Ö¡ÊÕµ½
	{
		if (!CAN_SendMsg(msg_get))	//ÊÕµ½ºó·¢³öÈ¥
		{

		}
	}
	else
	{

	}
}
