#include "PIT.h"
#include "derivative.h"

void PIT_Init()
{
	PITCFLMT_PITE = 0;	//关闭PIT PITTF标志位清零
	PITCE_PCE0 = 1;		//PCE0通道使能
	PITMUX = 0x00;		//通道0、1、2、3使用微定时器基准0计数
	PITMTLD0 = 80 - 1;
	PITLD0 = 400 - 1;	//T = (PITMTLD+1)*(PITLD+1)/Fbus = 1ms
	PITINTE_PINTE0 = 1;	//使能PIT
	PITCFLMT_PITE = 1;
};
