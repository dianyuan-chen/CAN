#ifndef __CAN_H
#define __CAN_H
#include "hidef.h"
#include "derivative.h"

typedef struct can_msg
{
	unsigned long id;		//id
	Bool RTR;				//远程帧
	unsigned char data[Max_Len];
	unsigned char len;
} CanMsg;
typedef struct can_init
{
	int bps;
	unsigned char clock;
	unsigned char sp;
	unsigned char syn;
} CAN_InitType;
typedef enum msg
{
	CanMsg1 = 0,
	CanMsg2 = 1,
	CanMsg3 = 2
} CanMsg_Num;

void CAN_Init(CAN_InitType *cfg);    //初始化CAN
Bool CAN_SendMsg(CanMsg msg);   //CAN发送
Bool CAN_GetMsg(CanMsg *msg);//CAN接收

#endif
