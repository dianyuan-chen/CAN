#include "CanMsg.h"

static CanMsg CanMsg_1 =
{
	0x1806E5F4,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '1'},
	8
};
static CanMsg CanMsg_2 =
{
	0x1806E6F4,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '2'},
	8
};
static CanMsg CanMsg_3 =
{
	0x1800EFF4,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '3'},
	8
};

void CanMsg_Send(Can_MsgNum num)//发送指定报文
{
	if (num == CanMsg1)
	{
		if (!CAN_SendMsg(CanMsg_1))
		{
			;
		}
	} else if (num == CanMsg2)
	{
		if (!CAN_SendMsg(CanMsg_2))
		{
			;
		}
	} else if (num == CanMsg3)
	{
		if (!CAN_SendMsg(CanMsg_3))
		{
			;
		}
	}
}