#include "CanMsg.h"

static CAN_MsgType CanMsg_1 =
{
	0x1806E5F4,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '1'},
	8
};
static CAN_MsgType CanMsg_2 =
{
	0x1806E6F4,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '2'},
	8
};
static CAN_MsgType CanMsg_3 =
{
	0x1800EFF4,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '3'},
	8
};

void CanMsg_Send(CAN_MsgSel msg_num)//发送指定报文
{
	if (msg_num == CAN_Msg1)
	{
		if (!CAN_SendMsg(CanMsg_1))
		{

		}
	}
	else if (msg_num == CAN_Msg2)
	{
		if (!CAN_SendMsg(CanMsg_2))
		{

		}
	}
	else if (msg_num == CAN_Msg3)
	{
		if (!CAN_SendMsg(CanMsg_3))
		{

		}
	}
	else
	{

	}
}
