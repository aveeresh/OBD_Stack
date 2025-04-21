
#ifndef CANTP_H
#define CANTP_H

#include "types.h"
#include "CAN_Driver.h"
#include "timer.h"

#define SINGLE_FRAME 						0x00
#define FIRST_FRAME  						0x10
#define CONSEC_FRAME 						0x20
#define FLOW_CONTROL_FRAME 			0x30

#define FLOW_STATUS_CTS       	0x00
#define FLOW_STATUS_WAIT      	0x01
#define FLOW_STATUS_OVERFLOW  	0x02


bool can_tp_transmit(can_idx_t can_idx, can_msg_t data, uint16 data_length);

bool can_tp_receive(can_idx_t can_idx, can_msg_t *data, uint16 data_length);



#endif 
