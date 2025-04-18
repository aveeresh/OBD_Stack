#ifndef CANTP_H
#define CANTP_H

#include "types.h"
#include "CAN_Driver.h"


bool can_tp_transmit(can_idx_t can_idx, can_msg_t data, uint16 data_length);

bool can_tp_receive(can_idx_t can_idx, can_msg_t *data, uint16 data_length);



#endif 
