#ifndef __PIT_H
#define __PIT_H

typedef enum clk  	//初始化时钟选择
{
	OSC = 0,
	PLL = 1
} PLL_ClkSel;

void PLL_Init(void);

#endif
