#ifndef CAN_DRIVER_H
#define CAN_DRIVER_H
#include "Types.h"
#define MAX_CALLBACKS 10

typedef struct {
    uint32 id;
    uint8 data[8];
    uint8 len;
} can_msg_t;

typedef enum{
	can_ctrl_1=0,
	can_ctrl_2=1
}can_idx_t;


typedef void (*can_callback_t)(can_msg_t* msg);

typedef struct {
    uint32 id;
    can_callback_t callback;
} can_callback_entry_t;

void can_init(can_idx_t CanIdx); 
void can_set_baudrate(can_idx_t CanIdx, uint32 baudrate_Kbps, uint32 PCLK_MHz, uint8 SJW, uint8 TSEG1, uint8 TSEG2);
void can_transmit(can_idx_t CanIdx, can_msg_t TxMsg);
uint8 can_receive(can_idx_t CanIdx, can_msg_t TxMsg); 
void can_register_callback(uint32 id, can_callback_t callback);

// These handlers should be linked in your startup code or vector table
void CAN_IRQHandler(void);


#endif
