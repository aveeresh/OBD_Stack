
#ifndef MODE03_H
#define MODE03_H

#include "cantp.h"
#include "Types.h"

// Service IDs
#define SERVICE_03_REQUEST_SID     0x03
#define SERVICE_03_RESPONSE_SID    0x43

// Negative Response Codes
#define GENERAL_REJECT                0x10
#define SERVICE_NOT_SUPPORTED         0x11
#define SUBFUNCTION_NOT_SUPPORTED     0x12
#define BUSY_REPEAT_REQUEST           0x21
#define CONDITIONS_NOT_CORRECT        0x22
#define REQUEST_RECEIVED_RESP_PENDING 0x78


typedef struct {
    uint8 high_byte;
    uint8 low_byte;
} DTC;


void mode_03_handler(uint32 id, uint8 len);
DTC* get_confirmed_dtcs(uint8* dtc_count);

#endif 
