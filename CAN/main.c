#include <hidef.h>
#include "derivative.h"
#include "config.h"
#include "CAN.h"
#include "CanMsg.h"
#include "PIT.h"

void main(void)
{
	DisableInterrupts;  //关闭所有中断
	PIT_Init();     //初始化PIT
	LED_DIR = 1;
	LED = 1;
	CAN_Init();     //初始化CAN
	EnableInterrupts;

	for(;;)
	{
		;
	}

}
#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt VectorNumber_Vpit0 PIT0(void) //PIT中断函数
{
	if ((!CAN_SendMsg(CanMsg_1)) ||
		(!CAN_SendMsg(CanMsg_2)) ||
		(!CAN_SendMsg(CanMsg_3)) ||
		(!CAN_SendMsg(CanMsg_4)))
	{
		LED = !LED;
	}
	PITTF_PTF0 = 1;
}
#pragma CODE_SEG DEFAULT
