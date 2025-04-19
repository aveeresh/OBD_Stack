#ifndef MODE_09_H
#define MODE_09_H

#include <stdint.h>   // for uint8_t, uint16_t, etc.
#include "Types.h"
#include <string.h> 

// CAN Message structure
typedef struct {
    uint32 id;       // CAN ID
    uint8 len;       // Length of the data
    uint8 data[8];   // CAN message data (8 bytes)
} CanMsg_t;

// Function prototypes
void Mode_09_Req_Handler(CanMsg_t OBDRequest);

#endif // MODE_09_HANDLER_H
