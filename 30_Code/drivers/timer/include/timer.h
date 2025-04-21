#ifndef TIMER_H
#define TIMER_H

#include "timer_regs.h"
#include "Types.h"
#include "MCU_Regs.h"

void timer_init(void);
uint32 get_time(void);
void delay_ms(uint32 delay);

#endif

