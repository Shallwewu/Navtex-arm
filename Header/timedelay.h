#ifndef	_TIMEDELAY_H
#define _TIMEDELAY_H

void delay_init(u8 SYSCLK);
void delay_us(u32 nus);
void delay_ms(u16 nms);

#endif