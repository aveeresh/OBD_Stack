#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H
#include "Types.h"
#include "Can_Regs.h"
#include "MCU_Regs.h"

#define MAX_PORTS	2		/* Number of CAN port on the chip */


typedef enum{
	can_ctrl_1=0,
	can_ctrl_2=1
}can_idx_t;

typedef struct
{
	uint32 len;
	uint32 id;	// CAN Message ID (11-bit or 29-bit)
	uint8 data[64];
} can_msg_t;


#define ACCF_OFF				  0x01
#define ACCF_BYPASS				0x02
#define ACCF_ON					  0x00
#define ACCF_FULLCAN			0x04
#define ACCF_IDEN_NUM			4
#define FULLCAN_ID				0x100
#define EXP_STD_ID				0x100
#define GRP_STD_ID				0x200
#define EXP_EXT_ID				0x100000
#define GRP_EXT_ID				0x200000

#define BITRATE500K24MHZ          0x001C0002
#define BITRATE125K16MHZ          0x001C0007
#define BITRATE125K18MHZ          0x001C0008
#define BITRATE500K18MHZ          0x001E0001


#define APB0_BASE         (0x40000000UL)
#define CANAF_RAM_BASE    (APB0_BASE + 0x38000)

void can_init(can_idx_t CanIdx);
void can_set_baudrate(can_idx_t CanIdx, uint32 baudrate_Kbps, uint32 PCLK_MHz, uint8 SJW, uint8 TSEG1, uint8 TSEG2);
void can_set_accf_lookup( void );
void can_set_accf( uint32 ACCFMode );
void can_transmit( can_idx_t CanIdx, can_msg_t* tx_msg );
uint8 can_receive(can_idx_t CanIdx, can_msg_t* rx_msg);

#endif




