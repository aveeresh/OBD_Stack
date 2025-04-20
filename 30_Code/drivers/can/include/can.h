#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H
#include "Types.h"

typedef struct {
    uint32 id;
    uint8 data[8];
    uint8 len;
} can_msg_t;

typedef enum{
	can_ctrl_1=0,
	can_ctrl_2=1
}can_idx_t;


void can_init(can_idx_t CanIdx); 
void can_set_baudrate(can_idx_t CanIdx, uint32 baudrate_Kbps, uint32 PCLK_MHz, uint8 SJW, uint8 TSEG1, uint8 TSEG2);
void can_transmit(can_idx_t CanIdx, can_msg_t TxMsg);
uint8 can_receive(can_idx_t CanIdx, can_msg_t *RxMsg); 


#endif
