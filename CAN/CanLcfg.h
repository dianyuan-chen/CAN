#ifndef __CANLCFG_H
#define __CANLCFG_H

#include "CAN.h"

extern long Tick;			//计时
extern long lastTick;		//上次发送时间
extern CAN_InitType Lcfg;	//初始化配置

void CAN_SendCallBack(void);//PIT定时中断发送
void CAN_GetCallBack(void);//接收报文中断

#endif