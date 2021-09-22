#include <hidef.h>
#include "derivative.h"

#include "CAN.h"

#define LED PORTC_PC4
#define LED_DIR DDRC_DDRC4
#define ID 0x0001
#define data_len 3

unsigned char a;
unsigned char senddata[3] = {'Z', 'A', 'C'};
Can_Msg msg_send;

void PIT_Init(void)
{
    PITCFLMT_PITE = 0;
    PITCE_PCE0 = 1;
    PITMUX = 0x00;
    PITMTLD0 = 100 - 1;
    PITLD0 = 4000 - 1;    //100ms
    PITINTE_PINTE0 = 1;
    PITCFLMT_PITE = 1;
}

#pragma CODE_SEG __NEAR_SEG NON_BANKED
void interrupt VectorNumber_Vpit0 PIT0(void)
{

    CAN_SendMsg(msg_send);
    PITTF_PTF0 = 1;
}

#pragma CODE_SEG DEFAULT
void main(void)
{
    DisableInterrupts;  //关闭所有中断
    PIT_Init();
    LED_DIR = 1;
    LED = 1;
    CAN_Init();
    EnableInterrupts;

    msg_send.id = ID;
    for(a = 0; a < data_len; a++)
    {
        msg_send.data[a]  = senddata[a];
    }
    msg_send.len = data_len;
    msg_send.RTR = FALSE;

    for(;;)
    {
        ;
    }

}