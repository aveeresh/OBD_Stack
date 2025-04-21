#ifndef MCU_REGS_H
#define MCU_REGS_H

#include "Types.h"

typedef union
{
	uint32 R;
	struct 
	{
		uint32 :1;
		uint32 PCTIM0:1;
		uint32 PCTIM1:1;
		uint32 PCUART0:1;
		uint32 PCUART1:1;
		uint32 :1;
		uint32 PCPWM1:1;
		uint32 PCI2C0:1;
		uint32 PCSPI:1;
		uint32 PCRTC:1;
		uint32 PCSSP1:1;
		uint32 :1;
		uint32 PCADC:1;
		uint32 PCCAN1:1;
		uint32 PCCAN2:1;
		uint32 PCGPIO:1;
		uint32 PCRIT:1;
		uint32 PCMCPWM:1;
		uint32 PCQEI:1;
		uint32 PCI2C1:1;
		uint32 :1;
		uint32 PCSSP0:1;
		uint32 PCTIM2:1;
		uint32 PCTIM3:1;
		uint32 PCUART2:1;
		uint32 PCUART3:1;
		uint32 PCI2C2:1;
		uint32 PCI2S:1;
		uint32 :1;
		uint32 PCGPDMA:1;
		uint32 PCENET:1;
		uint32 PCUSB:1;
	}B;
} PCONP;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 PCLK_WDT:2;
		uint32 PCLK_TIMER0:2;
		uint32 PCLK_TIMER1:2;
		uint32 PCLK_UART0:2;
		uint32 PCLK_UART1:2;
		uint32 :2;
		uint32 PCLK_PWM1:2;
		uint32 PCLK_I2C0:2;
		uint32 PCLK_SPI:2;
		uint32 :2;
