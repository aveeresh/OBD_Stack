#ifndef CAN_REGS_H
#define CAN_REGS_H

#include "Types.h"

typedef union
{
	uint32 R;
	struct 
	{
		uint32 RM:1;
		uint32 LOM:1;
		uint32 STM:1;
		uint32 TPM:1;
		uint32 SM:1;
		uint32 RPM:1;
		uint32 :1;
		uint32 TM:1;
		uint32 :24;
	}B;
} Can_MOD_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 TR:1;
		uint32 AT:1;
		uint32 RRB:1;
		uint32 CDO:1;
		uint32 SRR:1;
		uint32 STB1:1;
		uint32 STB2:1;
		uint32 STB3:1;
		uint32 :24;
	}B;
}Can_CMR_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 RBS:1;
		uint32 DOS:1;
		uint32 TBS:1;
		uint32 TCS:1;
		uint32 RS:1;
		uint32 TS:1;
		uint32 ES:1;
		uint32 BS:1;
		uint32 :8;
		uint32 RXERR:8;
		uint32 TXERR:8;
	}B;
}Can_GSR_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 RI:1;
		uint32 TI1:1;
		uint32 EI:1;
		uint32 DOI:1;
		uint32 WUI:1;
		uint32 EPI:1;
		uint32 ALI:1;
		uint32 BEI:1;
		uint32 IDI:1;
		uint32 TI2:1;
		uint32 TI3:1;
		uint32 :5;
		uint32 ERRBIT:5;
		uint32 ERRDIR:1;
		uint32 ERRC1:2;
		uint32 ALCBIT:8;
	}B;
}Can_ICR_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 RIE:1;
		uint32 TIE1:1;
		uint32 EIE:1;
		uint32 DOIE:1;
		uint32 WUIE:1;
		uint32 EPIE:1;
		uint32 ALIE:1;
		uint32 BEIE:1;
		uint32 IDIE:1;
		uint32 TIE2:1;
		uint32 TIE3:1;
		uint32 :21;
	}B;
}Can_IER_t;

typedef union 
{
	uint32 R;
	struct
	{
		uint32 BRP:10;
		uint32 :4;
		uint32 SJW:2;
		uint32 TSEG1:4;
		uint32 TSEG2:3;
		uint32 SAM:1;
		uint32 :8;
	}B;
} Can_BTR_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 EWL:8;
		uint32 :24;
	}B;
}Can_EWL_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 RBS:1;
		uint32 DOS:1;
		uint32 TBS1:1;
		uint32 TCS1:1;
		uint32 RS:1;
		uint32 TS1:1;
		uint32 ES:1;
		uint32 BS:1;
		uint32 RBS1:1;
		uint32 DOS1:1;
		uint32 TBS2:1;
		uint32 TCS2:1;
		uint32 RS1:1;
		uint32 TS2:1;
		uint32 ES1:1;
		uint32 BS1:1;
		uint32 RBS2:1;
		uint32 DOS2:1;
		uint32 TBS3:1;
		uint32 TCS3:1;
		uint32 RS2:1;
		uint32 TS3:1;
		uint32 ES3:1;
		uint32 BS3:1;
		uint32 :8;
		
	}B;
}Can_SR_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 IdIdx:10;
		uint32 BP:1;
		uint32 :5;
		uint32 DLC:4;
		uint32 :10;
		uint32 RTR:1;
		uint32 FF:1;
	}B;
}Can_RFS_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 Id:11;
		uint32 :21;
	}StdId;
	struct
	{
		uint32 Id:29;
		uint32 :3;
	}ExtId;
}Can_RID_t;

typedef union
{
	uint32 R;
	struct
	{
		uint8 Data1:8;
		uint8 Data2:8;
		uint8 Data3:8;
		uint8 Data4:8;
	}B;
}Can_RDA_t;

typedef union
{
	uint32 R;
	struct
	{
		uint8 Data5:8;
		uint8 Data6:8;
		uint8 Data7:8;
		uint8 Data8:8;
	}B;
}Can_RDB_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 PRIO:8;
		uint32 :8;
		uint32 DLC:4;
		uint32 :10;
		uint32 RTR:1;
		uint32 FF:1;
	}B;
}Can_TFI_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 Id:11;
		uint32 :21;
	}StdId;
	struct
	{
		uint32 Id:29;
		uint32 :3;
	}ExtId;
}Can_TID_t;

typedef union
{
	uint32 R;
	struct
	{
		uint8 Data1:8;
		uint8 Data2:8;
		uint8 Data3:8;
		uint8 Data4:8;
	}B;
}Can_TDA_t;

typedef union
{
	uint32 R;
	struct
	{
		uint8 Data5:8;
		uint8 Data6:8;
		uint8 Data7:8;
		uint8 Data8:8;
	}B;
}Can_TDB_t;

typedef struct
{
	uint32 R;
	struct
	{
		uint32 :1;
		uint32 CAN1SLEEP:1;
		uint32 CAN2SLEEP:1;
		uint32 :29;
	}B;
}Can_CANSLEEPCLR_t;

typedef struct
{
	uint32 R;
	struct
	{
		uint32 :1;
		uint32 CAN1WAKE:1;
		uint32 CAN2WAKE:1;
		uint32 :29;
	}B;
}Can_CANWAKEFLAGS_t;	

/* 
 * Define register collections here 
 *
*/



typedef union
{
    uint32 R;  
    struct 
    {
        uint32 ACCOFF: 1;  
        uint32 ACCBP: 1;   
        uint32 eFCA: 1;    
        uint32 : 29;       
    } B;
} AFMR_t;

typedef union
{
    uint32 R;
    struct
    {
        uint32 :2;
        uint32 SFF_sa :9;
        uint32 :21;
    } B;
} SFF_sa_t;

typedef union
{
    uint32 R;
    struct
    {
        uint32 :2;
        uint32 SFF_GRP_sa :10;
        uint32 :20;
    } B;
} SFF_GRP_sa_t;

typedef union
{
    uint32 R;
    struct
    {
        uint32 :2;
        uint32 EFF_sa :9;
        uint32 :21;
    } B;
} EFF_sa_t;

typedef union
{
    uint32 R;
    struct
    {
        uint32 :2;
        uint32 EFF_GRP_sa :10;
        uint32 :20;
    } B;
} EFF_GRP_sa_t;

typedef union
{
    uint32 R;
    struct
    {
        uint32 :2;
        uint32 ENDofTable :10;
        uint32 :20;
    } B;
} ENDofTable_t;



typedef union
{
	uint32 R;
	struct 
	{
		uint32 ISE_WDT:1;
	  uint32 ISE_TIMER0:1;
		uint32 ISE_TIMER1:1;
		uint32 ISE_TIMER2:1;
		uint32 ISE_TIMER3:1;
		uint32 ISE_UART0:1;
		uint32 ISE_UART1:1;
		uint32 ISE_UART2:1;
		uint32 ISE_UART3:1;
		uint32 ISE_PWM:1;
		uint32 ISE_I2C0:1;
		uint32 ISE_I2C1:1;
		uint32 ISE_I2C2:1;
		uint32 ISE_SPI:1;
		uint32 ISE_SSP0:1;
		uint32 ISE_SSP1:1;
		uint32 ISE_PLL0:1;
		uint32 ISE_RTC:1;
		uint32 ISE_EINT0:1;
		uint32 ISE_EINT1:1;
		uint32 ISE_EINT2:1;
		uint32 ISE_EINT3:1;
		uint32 ISE_ADC:1;
		uint32 ISE_BOD:1;
		uint32 ISE_USB:1;
		uint32 ISE_CAN:1;
		uint32 ISE_DMA:1;
		uint32 ISE_I2S:1;
		uint32 ISE_ENET:1;
		uint32 ISE_RIT:1;
		uint32 ISE_MCPWM:1;
		uint32 ISE_QEI:1;	
	}B;
} ISER0_t;


typedef union
{
	uint32 R;
	struct 
	{
		uint32 ISE_PLL1:1;
	  uint32 ISE_USBACT:1;
		uint32 ISE_CANACT:1;
		uint32 :29;
	}B;
} ISER1_t;


typedef union
{
	uint32 R;
	struct 
	{
		uint32 ICE_WDT:1;
	  uint32 ICE_TIMER0:1;
		uint32 ICE_TIMER1:1;
		uint32 ICE_TIMER2:1;
		uint32 ICE_TIMER3:1;
		uint32 ICE_UART0:1;
		uint32 ICE_UART1:1;
		uint32 ICE_UART2:1;
		uint32 ICE_UART3:1;
		uint32 ICE_PWM:1;
		uint32 ICE_I2C0:1;
		uint32 ICE_I2C1:1;
		uint32 ICE_I2C2:1;
		uint32 ICE_SPI:1;
		uint32 ICE_SSP0:1;
		uint32 ICE_SSP1:1;
		uint32 ICE_PLL0:1;
		uint32 ICE_RTC:1;
		uint32 ICE_EINT0:1;
		uint32 ICE_EINT1:1;
		uint32 ICE_EINT2:1;
		uint32 ICE_EINT3:1;
		uint32 ICE_ADC:1;
		uint32 ICE_BOD:1;
		uint32 ICE_USB:1;
		uint32 ICE_CAN:1;
		uint32 ICE_DMA:1;
		uint32 ICE_I2S:1;
		uint32 ICE_ENET:1;
		uint32 ICE_RIT:1;
		uint32 ICE_MCPWM:1;
		uint32 ICE_QEI:1;	
	}B;
} ICER0_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 ICE_PLL1:1;
	  uint32 ICE_USBACT:1;
		uint32 ICE_CANACT:1;
		uint32 :29;
	}B;
} ICER1_t;


typedef union
{
	uint32 R;
	struct 
	{
		uint32 ISP_WDT:1;
	  uint32 ISP_TIMER0:1;
		uint32 ISP_TIMER1:1;
		uint32 ISP_TIMER2:1;
		uint32 ISP_TIMER3:1;
		uint32 ISP_UART0:1;
		uint32 ISP_UART1:1;
		uint32 ISP_UART2:1;
		uint32 ISP_UART3:1;
		uint32 ISP_PWM:1;
		uint32 ISP_I2C0:1;
		uint32 ISP_I2C1:1;
		uint32 ISP_I2C2:1;
		uint32 ISP_SPI:1;
		uint32 ISP_SSP0:1;
		uint32 ISP_SSP1:1;
		uint32 ISP_PLL0:1;
		uint32 ISP_RTC:1;
		uint32 ISP_EINT0:1;
		uint32 ISP_EINT1:1;
		uint32 ISP_EINT2:1;
		uint32 ISP_EINT3:1;
		uint32 ISP_ADC:1;
		uint32 ISP_BOD:1;
		uint32 ISP_USB:1;
		uint32 ISP_CAN:1;
		uint32 ISP_DMA:1;
		uint32 ISP_I2S:1;
		uint32 ISP_ENET:1;
		uint32 ISP_RIT:1;
		uint32 ISP_MCPWM:1;
		uint32 ISP_QEI:1;	
	}B;
} ISPR0_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 ISP_PLL1:1;
	  uint32 ISP_USBACT:1;
		uint32 ISP_CANACT:1;
		uint32 :29;
	}B;
} ISPR1_t;


typedef union
{
	uint32 R;
	struct 
	{
		uint32 ICP_WDT:1;
	  uint32 ICP_TIMER0:1;
		uint32 ICP_TIMER1:1;
		uint32 ICP_TIMER2:1;
		uint32 ICP_TIMER3:1;
		uint32 ICP_UART0:1;
		uint32 ICP_UART1:1;
		uint32 ICP_UART2:1;
		uint32 ICP_UART3:1;
		uint32 ICP_PWM:1;
		uint32 ICP_I2C0:1;
		uint32 ICP_I2C1:1;
		uint32 ICP_I2C2:1;
		uint32 ICP_SPI:1;
		uint32 ICP_SSP0:1;
		uint32 ICP_SSP1:1;
		uint32 ICP_PLL0:1;
		uint32 ICP_RTC:1;
		uint32 ICP_EINT0:1;
		uint32 ICP_EINT1:1;
		uint32 ICP_EINT2:1;
		uint32 ICP_EINT3:1;
		uint32 ICP_ADC:1;
		uint32 ICP_BOD:1;
		uint32 ICP_USB:1;
		uint32 ICP_CAN:1;
		uint32 ICP_DMA:1;
		uint32 ICP_I2S:1;
		uint32 ICP_ENET:1;
		uint32 ICP_RIT:1;
		uint32 ICP_MCPWM:1;
		uint32 ICP_QEI:1;	
	}B;
} ICPR0_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 ICP_PLL1:1;
	  uint32 ICP_USBACT:1;
		uint32 ICP_CANACT:1;
		uint32 :29;
	}B;
} ICPR1_t;


typedef union
{
	uint32 R;
	struct 
	{
		uint32 IAB_WDT:1;
	  uint32 IAB_TIMER0:1;
		uint32 IAB_TIMER1:1;
		uint32 IAB_TIMER2:1;
		uint32 IAB_TIMER3:1;
		uint32 IAB_UART0:1;
		uint32 IAB_UART1:1;
		uint32 IAB_UART2:1;
		uint32 IAB_UART3:1;
		uint32 IAB_PWM:1;
		uint32 IAB_I2C0:1;
		uint32 IAB_I2C1:1;
		uint32 IAB_I2C2:1;
		uint32 IAB_SPI:1;
		uint32 IAB_SSP0:1;
		uint32 IAB_SSP1:1;
		uint32 IAB_PLL0:1;
		uint32 IAB_RTC:1;
		uint32 IAB_EINT0:1;
		uint32 IAB_EINT1:1;
		uint32 IAB_EINT2:1;
		uint32 IAB_EINT3:1;
		uint32 IAB_ADC:1;
		uint32 IAB_BOD:1;
		uint32 IAB_USB:1;
		uint32 IAB_CAN:1;
		uint32 IAB_DMA:1;
		uint32 IAB_I2S:1;
		uint32 IAB_ENET:1;
		uint32 IAB_RIT:1;
		uint32 IAB_MCPWM:1;
		uint32 IAB_QEI:1;	
	}B;
} IABR0_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 IAB_PLL1:1;
	  uint32 IAB_USBACT:1;
		uint32 IAB_CANACT:1;
		uint32 :29;
	}B;
} IABR1_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 :3;
	  uint32 IP_WDT:5;
		uint32 :3;
		uint32 IP_TIMER0:5;
			uint32 :3;
		uint32 IP_TIMER1:5;
			uint32 :3;
		uint32 IP_TIMER2:5;
	}B;
} IPR0_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 :3;
	  uint32 IP_TIMER3:5;
		uint32 :3;
		uint32 IP_UART0:5;
			uint32 :3;
		uint32 IP_UART1:5;
			uint32 :3;
		uint32 IP_UART2:5;
	}B;
} IPR1_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 :3;
	  uint32 IP_UART3:5;
		uint32 :3;
		uint32 IP_PWM:5;
			uint32 :3;
		uint32 IP_I2C0:5;
			uint32 :3;
		uint32 IP_I2C1:5;
	}B;
} IPR2_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 :3;
	  uint32 IP_I2C2:5;
		uint32 :3;
		uint32 IP_SPI:5;
			uint32 :3;
		uint32 IP_SSP0:5;
			uint32 :3;
		uint32 IP_SSP1:5;
	}B;
} IPR3_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 :3;
	  uint32 IP_PLL0:5;
		uint32 :3;
		uint32 IP_RTC:5;
			uint32 :3;
		uint32 IP_EINT0:5;
			uint32 :3;
		uint32 IP_EINT1:5;
	}B;
} IPR4_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 :3;
	  uint32 IP_EINT2:5;
		uint32 :3;
		uint32 IP_EINT3:5;
			uint32 :3;
		uint32 IP_ADC:5;
			uint32 :3;
		uint32 IP_BOD:5;
	}B;
} IPR5_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 :3;
	  uint32 IP_USB:5;
		uint32 :3;
		uint32 IP_CAN:5;
			uint32 :3;
		uint32 IP_DMA:5;
			uint32 :3;
		uint32 IP_I2S:5;
	}B;
} IPR6_t;


typedef union
{
	uint32 R;
	struct 
	{
		uint32 :3;
	  uint32 IP_ENET:5;
		uint32 :3;
		uint32 IP_RIT:5;
			uint32 :3;
		uint32 IP_MCPWM:5;
			uint32 :3;
		uint32 IP_QEI:5;
	}B;
} IPR7_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 :3;
	  uint32 IP_PLL1:5;
		uint32 :3;
		uint32 IP_USBACT:5;
			uint32 :3;
		uint32 IP_CANACT:5;
			uint32 :8;
	}B;
} IPR8_t;

typedef union
{
	uint32 R;
	struct 
	{
		uint32 INTID:9;
	  uint32 :23;
	}B;
} STIR_t;

 
/** @brief  Controller Area Network Acceptance Filter(CANAF) register structure definition */

typedef struct
{
    volatile AFMR_t AFMR;
    volatile SFF_sa_t SFF_sa;
    volatile SFF_GRP_sa_t SFF_GRP_sa;
    volatile EFF_sa_t EFF_sa;
    volatile EFF_GRP_sa_t EFF_GRP_sa;
    volatile ENDofTable_t ENDofTable;
} Can_AF_Regs_t;

/** @brief  Controller Area Network Central (CANCR) register structure definition */

typedef struct 
{
	volatile uint32 CANTxSR;
	volatile uint32 CANRxSR;
	volatile uint32 CANMSR;
}Can_CentralRegs_t;

/** @brief  Controller Area Network Controller (CAN) register structure definition */


typedef struct 
{
	volatile Can_MOD_t MOD;    //Controls the operating mode of the CAN Controller.
	volatile Can_CMR_t CMR;    //Command bits that affect the state of the CAN Controller
	volatile Can_GSR_t GSR;    //Global Controller Status and Error Counters
	volatile Can_ICR_t ICR;    // Interrupt status, Arbitration Lost Capture, Error Code Capture
	volatile Can_IER_t IER;    //Interrupt Enable
	volatile Can_BTR_t BTR;    // Bus Timing
	volatile Can_EWL_t EWL;    // Error Warning Limit
	volatile Can_SR_t SR;      // Status Register
	volatile Can_RFS_t RFS;    // Receive frame status
	volatile Can_RID_t RID;    // Received Identifier
	volatile Can_RDA_t RDA;    // Received data bytes 1-4
	volatile Can_RDB_t RDB;    // Received data bytes 5-8
	volatile Can_TFI_t TFI1;   // Transmit frame info (Tx Buffer 1)
	volatile Can_TID_t TID1;   // Transmit Identifier (Tx Buffer 1)
	volatile Can_TDA_t TDA1;   // Transmit data bytes 1-4 (Tx Buffer 1)
	volatile Can_TDB_t TDB1;   // Transmit data bytes 5-8 (Tx Buffer 1)
	volatile Can_TFI_t TFI2;    // Transmit frame info (Tx Buffer 2)
	volatile Can_TID_t TID2;    // Transmit Identifier (Tx Buffer 2)
	volatile Can_TDA_t TDA2;    // Transmit data bytes 1-4 (Tx Buffer 2)
	volatile Can_TDB_t TDB2;    // Transmit data bytes 5-8 (Tx Buffer 2)
	volatile Can_TFI_t TFI3;    // Transmit frame info (Tx Buffer 3)
	volatile Can_TID_t TID3;    // Transmit Identifier (Tx Buffer 3)
	volatile Can_TDA_t TDA3;    // Transmit data bytes 1-4 (Tx Buffer 3)
	volatile Can_TDB_t TDB3;    // Transmit data bytes 5-8 (Tx Buffer 3)
}Can_GeneralRegs_t;


#define APB0_BASE         (0x40000000UL)

//#define CANAF_RAM_BASE    (APB0_BASE + 0x38000)
#define CANAF_BASE        (APB0_BASE + 0x3C000)
#define CANCR_BASE        (APB0_BASE + 0x40000)
#define CAN1_BASE         (APB0_BASE + 0x44000)
#define CAN2_BASE         (APB0_BASE + 0x48000)

//#define CANAF_RAM         ((CANAF_RAM_TypeDef *) CANAF_RAM_BASE)
#define CANAF             ((Can_AF_Regs_t     *) CANAF_BASE    )
#define CANCR             ((Can_CentralRegs_t     *) CANCR_BASE    )
#define CAN1              ((Can_GeneralRegs_t     *) CAN1_BASE     )
#define CAN2              ((Can_GeneralRegs_t     *) CAN2_BASE     )


#define ISER0_t (*(volatile ISER0_t *) 0xE000E100)
#define ISER1_t (*(volatile ISER1_t *) 0xE000E104)
	
#define ICER0_t (*(volatile ICER0_t *)0xE000E180)
#define ICER1_t (*(volatile ICER1_t *)0xE000E184)
	
#define ISPR0_t (*(volatile ISPR0_t *)0xE000E200)
#define ISPR1_t (*(volatile ISPR1_t *)0xE000E204)
	
#define ICPR0_t (*(volatile ICPR0_t *)0xE000E280)
#define ICPR1_t (*(volatile ICPR1_t *)0xE000E284)
	
#define IABR0_t (*(volatile IABR0_t *)0xE000E300)
#define IABR1_t (*(volatile IABR1_t *)0xE000E304)

#define IPR0_t (*(volatile IPR0_t *)0xE000E400)
#define IPR1_t (*(volatile IPR1_t *)0xE000E404)
#define IPR2_t (*(volatile IPR2_t *)0xE000E408)
#define IPR3_t (*(volatile IPR3_t *)0xE000E40C)
#define IPR4_t (*(volatile IPR4_t *)0xE000E410)
#define IPR5_t (*(volatile IPR5_t *)0xE000E414)
#define IPR6_t (*(volatile IPR6_t *)0xE000E418)
#define IPR7_t (*(volatile IPR7_t *)0xE000E41C)
#define IPR8_t (*(volatile IPR8_t *)0xE000E420)	
	
#define STIR_t (*(volatile STIR_t *)0xE000EF00)


#endif
