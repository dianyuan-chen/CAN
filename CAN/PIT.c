#include "PIT.h"
#include "derivative.h"

void PIT_Init(void)
{
	PITCFLMT_PITE = 0;	//关闭PIT
	PITCE_PCE0 = 1;		//PCE0通道使能
	PITMUX = 0x00;		//使用微定时器0计数
	PITMTLD0 = 100 - 1;
	PITLD0 = 4000 - 1;	//T = (PITMTLD+1)*(PITLD+1)/Fbus = 100ms
	PITINTE_PINTE0 = 1;	//使能PIT
	PITCFLMT_PITE = 1;
};
