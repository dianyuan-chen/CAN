#ifndef __CAN_H
#define __CAN_H

#include "hidef.h"
#include "derivative.h"
#include "config.h"

typedef enum _CAN_ClkSel  	//初始化时钟选择
{
	CAN_CLK_OSC = 0,
	CAN_CLK_PLL = 1
} CAN_ClkSel;

typedef enum _CAN_BpsSel  	//波特率选择
{
	CAN_Bps_125 = 0,
	CAN_Bps_250 = 1
} CAN_BpsSel;

typedef enum _CAN_MsgSel
{
	CAN_Msg1 = 0,
	CAN_Msg2 = 1,
	CAN_Msg3 = 2
} CAN_MsgSel;

typedef struct _CAN_MsgType
{
	unsigned long id;		//id
	Bool RTR;				//远程帧
	unsigned char data[MSG_MAX_LEN];
	unsigned char len;
} CAN_MsgType;

typedef struct _CAN_InitType
{
	CAN_BpsSel bps;
	CAN_ClkSel clock;
	unsigned char sp;
	unsigned char syn;
} CAN_InitType;

void CAN_Init(CAN_InitType *cfg);    //初始化CAN
Bool CAN_SendMsg(CAN_MsgType msg);   //CAN发送
Bool CAN_GetMsg(CAN_MsgType *msg);//CAN接收

#endif
