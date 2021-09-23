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

extern CanMsg CanMsg_1;//报文1
extern CanMsg CanMsg_2;//报文2
extern CanMsg CanMsg_3;//报文3
extern CanMsg CanMsg_4;//报文4

#endif
