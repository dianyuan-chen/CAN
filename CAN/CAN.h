#ifndef __CAN_H
#define __CAN_H

#include <hidef.h>
#include "derivative.h"
#include "CanMsg.h"

void CAN_Init(void);    //初始化CAN
Bool CAN_SendMsg(CanMsg msg);   //CAN发送

#endif
