#ifndef __CANLCFG_H
#define __CANLCFG_H

#include "CAN.h"

extern CAN_InitType CAN_InitLcfg;	//初始化配置

void CAN_SendCallBack(void);//PIT定时中断发送
void CAN_GetCallBack(void);//接收报文中断

#endif
