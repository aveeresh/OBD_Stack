#include "timer.h"

static volatile uint32 timer_count = 0;

void TIMER0_IRQHandler(void) {
    if (TIMER0->IR.R & (1 << 0)) {  // Check interrupt has occured
        TIMER0->IR.R = (1 << 0);  // Clear MR0 interrupt
        timer_count++;
    }
}


void timer_init(void) {
    
		PCONP.R |= (1 << 1);  // Power Timer 0

			
		PCLKSEL0.R &= ~(3 << 2);  // Clear bits 
		PCLKSEL0.R |= (1 << 2);   // 100 MHz clock for Timer0

    
    TIMER0->TCR = 0x02;  // Reset Timer0

    TIMER0->CTCR.R = 0x0; // Enable Timer mode

    TIMER0->PR = 50000 - 1;     // 1 ms : PR = (PCLK / 1000) - 1

    TIMER0->MR0 = 1; //Trigger interrupt every 1ms

    TIMER0->MCR.R = 0x3	; // Enable interrupt on MR0 and reset on MR0 if it matches TC

    ISER0 |= (1 << 1);   // Enable Timer0 interrupt

    TIMER0->TCR = 0x01;  // Start Timer
}

uint32 get_time(void) {
    return timer_count;
}


void delay_ms(uint32 delay) {
    uint32 start_time = get_time();
	while ((get_time() - start_time) < delay);
}