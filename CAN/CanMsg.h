#ifndef __CANMSG_H
#define __CANMSG_H

#include <hidef.h>

typedef struct can_msg
{
	unsigned long id;		//id
	Bool RTR;				//远程帧
	unsigned char data[8];
	unsigned char len;		//长度
}CanMsg;

Bool CanMsg_SendAll(void);

#endif
