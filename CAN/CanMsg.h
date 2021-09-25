#ifndef __CANMSG_H
#define __CANMSG_H

typedef enum msg
{
	CanMsg1 = 0,
	CanMsg2 = 1,
	CanMsg3 = 3
} CanMsg_Num;

void CanMsg_Send(CanMsg_Num num);	//发送指定报文

#endif