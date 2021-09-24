#include "CanMsg.h"
#include "CAN.h"

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
static CanMsg CanMsg_4 =
{
	0x18FF50E4,
	0,
	{'C', 'A', 'N', 'M', 'S', 'G', '_', '4'},
	8
};

Bool CanMsg_SendAll()
{
	if ((!CAN_SendMsg(CanMsg_1)) ||
		(!CAN_SendMsg(CanMsg_2)) ||
		(!CAN_SendMsg(CanMsg_3)) ||
		(!CAN_SendMsg(CanMsg_4)))
	{
		return FALSE;//发送失败
	}
}
