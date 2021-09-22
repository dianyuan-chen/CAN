#include "CAN.h"

void CAN_Init()
{
    if (CAN0CTL0_INITRQ == 0)
    {
        CAN0CTL0_INITRQ = 1;
    }
    while (CAN0CTL1_INITAK == 0)
    {
        ;
    }
    CAN0BTR0_SJW = 0;
    CAN0BTR0_BRP = 1;
    CAN0BTR1 = 0x1c;    //比特率:125
    CAN0IDMR0 = 0xFF;
    CAN0IDMR1 = 0xFF;
    CAN0IDMR2 = 0xFF;
    CAN0IDMR3 = 0xFF;
    CAN0IDMR4 = 0xFF;
    CAN0IDMR5 = 0xFF;
    CAN0IDMR6 = 0xFF;
    CAN0IDMR7 = 0xFF;

    CAN0CTL1 = 0xC0;  //使能MSCAN模块，使用总线时钟源
    CAN0CTL0 = 0x00;  //返回一般运行模式
    while (CAN0CTL1_INITAK)  //等待回到一般运行模式
    {
        ;
    }
    while (CAN0CTL0_SYNCH == 0)  //等待总线时钟同步
    {
        ;
    }
    CAN0RIER_RXFIE = 0; //禁止接受中断
}

Bool CAN_SendMsg(Can_Msg msg)//CAN0发送函数
{
    unsigned char send_buf, sp;
    if (msg.len > 8)
    {
        return FALSE;
    }
    if(CAN0CTL0_SYNCH == 0)
    {
        return FALSE;
    }
    send_buf = 0;
    do
    {
        CAN0TBSEL = CAN0TFLG; //选择缓冲器，最低置1位
        send_buf = CAN0TBSEL;
    }
    while (!send_buf);    //寻找空闲的缓冲器
    CAN0TXIDR0 = (unsigned char)(msg.id >> 3);
    CAN0TXIDR1 = (unsigned char)(msg.id << 5);  //写入标识符
    if(msg.RTR)
    {
        CAN0TXIDR1 |= 0x10; //远程帧
    }
    for(sp = 0; sp < msg.len; sp++)
    {
        *((&CAN0TXDSR0) + sp) = msg.data[sp]; //写入数据
    }
    CAN0TXDLR = msg.len;  //写入数据长度
    CAN0TFLG = send_buf;  //清TXx标志（缓冲器准备发送）
    return TRUE;
}
