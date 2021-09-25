#include "PLL.h"
#include "derivative.h"

void PLL_Init(void)	//初始化锁相环
{
	CLKSEL_PLLSEL = 0;        //内部总线时钟来源于晶振
	PLLCTL_PLLON = 0;         //关闭PLL
	SYNR = 0x47;
	REFDV = 0x41;
	POSTDIV = 0x00;           //PLL:64M;BUS:32M
	PLLCTL_PLLON = 1;         //打开PLL
	_asm(nop);
	_asm(nop);                //等待连两个机器周期
	while (CRGFLG_LOCK == 0)  //等待PLL稳定
	{
		;
	}
	CLKSEL_PLLSEL = 1;        //选择PLL作为时钟源
}
