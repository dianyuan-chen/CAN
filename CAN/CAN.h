#ifndef __CAN_H
#define __CAN_H

#include <hidef.h>
#include "derivative.h"

typedef struct can_msg
{

    unsigned int id;
    Bool RTR;
    unsigned char data[8];
    unsigned char len;
} Can_Msg;

void CAN_Init(void);
Bool CAN_SendMsg(Can_Msg msg);

#endif