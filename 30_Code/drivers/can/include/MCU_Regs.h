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
		uint32 PCLK_SSP1:2;
		uint32 PCLK_DAC:2;
		uint32 PCLK_ADC:2;
		uint32 PCLK_CAN1:2;
		uint32 PCLK_CAN2:2;
		uint32 PCLK_ACF:2;
	}B;
} PCLKSEL0;

typedef union
{
	uint32 R;
	struct 
	{
		uint32  PCLK_QEI:2;
		uint32 PCLK_GPIOINT:2;
		uint32 PCLK_PCB:2;
		uint32 PCLK_I2C1:2;
		uint32 :2;
		uint32 PCLK_SSP0:2;
		uint32 PCLK_TIMER2:2;
		uint32 PCLK_TIMER3:2;
		uint32 PCLK_UART2:2;
		uint32 PCLK_UART3:2;
		uint32 PCLK_I2C2:2;
		uint32 PCLK_I2S:2;
		uint32 :2;
		uint32 PCLK_RIT:2;
		uint32 PCLK_SYSCON:2;
		uint32  PCLK_MC:2;
	}B;
} PCLKSEL1;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 P0_0:2;
		uint32 P0_1:2;
		uint32 P0_2:2;
		uint32 P0_3:2;
		uint32 P0_4:2;
		uint32 P0_5:2;
		uint32 P0_6:2;
		uint32 P0_7:2;
		uint32 P0_8:2;
		uint32 P0_9:2;
		uint32 P0_10:2;
		uint32 P0_11:2;
		uint32 :6;
		uint32 P0_15:2;
	}B;
} PINSEL0;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 P0_16:2;
		uint32 P0_17:2;
		uint32 P0_18:2;
		uint32 P0_19:2;
		uint32 P0_20:2;
		uint32 P0_21:2;
		uint32 P0_22:2;
		uint32 P0_23:2;
		uint32 P0_24:2;
		uint32 P0_25:2;
		uint32 P0_26:2;
		uint32 P0_27:2;
		uint32 P0_28:2;
		uint32 P0_29:2;
		uint32 P0_30:2;
		uint32 :2;
	}B;
} PINSEL1;

typedef union
{
	uint32 R;
	struct 
	{
	  uint32 P0_0_MODE:2;
		uint32 P0_1_MODE:2;
		uint32 P0_2_MODE:2;
		uint32 P0_3_MODE:2;
		uint32 P0_4_MODE:2;
		uint32 P0_5_MODE:2;
		uint32 P0_6_MODE:2;
		uint32 P0_7_MODE:2;
		uint32 P0_8_MODE:2;
		uint32 P0_9_MODE:2;
		uint32 P0_10_MODE:2;
		uint32 P0_11_MODE:2;
		uint32 :6;
		uint32 P0_15_MODE:2;
	}B;
} PINMODE0;

typedef union
{
	uint32 R;
	struct 
	{
	  uint32 P0_16_MODE:2;
		uint32 P0_17_MODE:2;
		uint32 P0_18_MODE:2;
		uint32 P0_19_MODE:2;
		uint32 P0_20_MODE:2;
		uint32 P0_21_MODE:2;
		uint32 P0_22_MODE:2;
		uint32 P0_23_MODE:2;
		uint32 P0_24_MODE:2;
		uint32 P0_25_MODE:2;
		uint32 P0_26_MODE:2;
		uint32 P0_11_MODE:2;
		uint32 :6;
		uint32 :2;
	}B;
} PINMODE1;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 P0_0_OD:1;
	  uint32 P0_1_OD:1;
		uint32 P0_2_OD:1;
		uint32 P0_3_OD:1;
		uint32 P0_4_OD:1;
		uint32 P0_5_OD:1;
		uint32 P0_6_OD:1;
		uint32 P0_7_OD:1;
		uint32 P0_8_OD:1;
		uint32 P0_9_OD:1;
		uint32 P0_10_OD:1;
		uint32 P0_11_OD:1;
		uint32 :3;
		uint32 P0_15_OD:1;
		uint32 P0_16_OD:1;
		uint32 P0_17_OD:1;
		uint32 P0_18_OD:1;
		uint32 P0_19_OD:1;
		uint32 P0_20_OD:1;
		uint32 P0_21_OD:1;
		uint32 P0_22_OD:1;
		uint32 P0_23_OD:1;
		uint32 P0_24_OD:1;
		uint32 P0_25_OD:1;
		uint32 P0_26_OD:1;
		uint32 :2;
		uint32 P0_29_OD:1;
		uint32 P0_30_OD:1;
		uint32 :1;
	}B;
} PINMODE_OD0;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 P1_0_OD:1;
	  uint32 P1_1_OD:1;
		uint32 :2;
		uint32 P1_4_OD:1;
		uint32 :3;
		uint32 P1_8_OD:1;
		uint32 P1_9_OD:1;
		uint32 P1_10_OD:1;
		uint32 :3;
		uint32 P1_14_OD:1;
		uint32 P1_15_OD:1;
		uint32 P1_16_OD:1;
		uint32 P1_17_OD:1;
		uint32 P1_18_OD:1;
		uint32 P1_19_OD:1;
		uint32 P1_20_OD:1;
		uint32 P1_21_OD:1;
		uint32 P1_22_OD:1;
		uint32 P1_23_OD:1;
		uint32 P1_24_OD:1;
		uint32 P1_25_OD:1;
		uint32 P1_26_OD:1;
		uint32 P1_27_OD:1;
		uint32 P1_28_OD:1;
		uint32 P1_29_OD:1;
		uint32 P1_30_OD:1;
		uint32 P1_31_OD:1;
	}B;
} PINMODE_OD1;


//#define PINMODE1_REG  (*(volatile PINMODE1 *)0x4002C044)

#define PINSEL0 (*(volatile PINSEL0 *)0x4002C000)
#define PINSEL1  (*(volatile PINSEL1 *)0x4002C004)
#define PINMODE0 (*(volatile PINMODE0 *)0x4002C040)
#define PINMODE1 (*(volatile PINMODE1 *)0x4002C044)
#define PINMODE_OD0 (*(volatile PINMODE_OD0 *)0x4002C068)
#define PINMODE_OD1 (*(volatile PINMODE_OD1 *)0x4002C06C)
#define PCONP (*(volatile PCONP *)0x400FC0C4)
#define PCLKSEL0 (*(volatile PCLKSEL0 *)0x400FC1A8)
#define PCLKSEL1 (*(volatile PCLKSEL1 *)0x400FC1AC)

#endif

