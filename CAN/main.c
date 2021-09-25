#include <hidef.h>
#include "derivative.h"
#include "CAN.h"
#include "config.h"
#include "PLL.h"
#include "PIT.h"
#include "CanMsg.h"
#include "CanLcfg.h"

void main(void)
{
	DisableInterrupts;
	PLL_Init();			//初始化锁相环
	LED_DIR = 1;
	LED = 1;
	CAN_Init(&Lcfg);	//初始化CAN
	PIT_Init();			//初始化PIT中断
	EnableInterrupts;

	for(;;) {}
}
