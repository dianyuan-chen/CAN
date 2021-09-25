#include "PLL.h"
#include "derivative.h"

void PLL_Init(void)	//��ʼ�����໷
{
	CLKSEL_PLLSEL = 0;        //�ڲ�����ʱ����Դ�ھ���
	PLLCTL_PLLON = 0;         //�ر�PLL
	SYNR = 0x47;
	REFDV = 0x41;
	POSTDIV = 0x00;           //PLL:64M;BUS:32M
	PLLCTL_PLLON = 1;         //��PLL
	_asm(nop);
	_asm(nop);                //�ȴ���������������
	while (CRGFLG_LOCK == 0)  //�ȴ�PLL�ȶ�
	{
		;
	}
	CLKSEL_PLLSEL = 1;        //ѡ��PLL��Ϊʱ��Դ
}
