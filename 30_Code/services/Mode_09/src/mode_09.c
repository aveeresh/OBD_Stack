#include "Mode_09.h"
#include "CAN_Driver.h"  // Include CAN communication library
#include "Types.h"
#include <string.h>  

void Mode_09_Req_Handler(CanMsg_t OBDRequest)
{
	int i;
    uint8 PID = OBDRequest.data[2];  // Get the PID from the incoming message
    CanMsg_t OBDResp;  // Declare a CAN response message

    OBDResp.id = 0x7E8;  // Set response CAN ID

    switch(PID)
    {
        case 0x00: // Supported PIDs 
        {
            // Set the supported PIDs as a bitmask
            OBDResp.len = 8;
            OBDResp.data[0] = 0x06;
            OBDResp.data[1] = 0x49;
            OBDResp.data[2] = 0x00;
            OBDResp.data[3] = 0x50;
            OBDResp.data[4] = 0x00;
            OBDResp.data[5] = 0x04;
            OBDResp.data[6] = 0x00;
         can_tp_transmit(can_idx, OBDResp, OBDResp.len);
            break;
        }
        case 0x02: // VIN (17 characters)
        {
            char VIN[17] = "WAUZAB345XY123456";  // VIN number

            // First frame
            OBDResp.len = 8;
            OBDResp.data[0] = 0x10;
            OBDResp.data[1] = 0x14;
            OBDResp.data[2] = 0x49;
            OBDResp.data[3] = 0x02;
            OBDResp.data[4] = VIN[0];
            OBDResp.data[5] = VIN[1];
            OBDResp.data[6] = VIN[2];
            OBDResp.data[7] = VIN[3];
      can_tp_transmit(can_idx, OBDResp, OBDResp.len);

            // Second frame
            OBDResp.data[0] = 0x21;
            for (i = 0; i < 7; i++)
                OBDResp.data[i + 1] = VIN[i + 4];
     can_tp_transmit(can_idx, OBDResp, OBDResp.len);

            // Third frame
            OBDResp.data[0] = 0x22;
            for (i = 0; i < 7; i++)
                OBDResp.data[i + 1] = VIN[i + 11];
       can_tp_transmit(can_idx, OBDResp, OBDResp.len);
            break;
        }

        case 0x04: // Calibration ID (16 characters)
        {
            char CALID[16] = "ECU_CAL_ID_12345";

            // First frame
            OBDResp.len = 8;
            OBDResp.data[0] = 0x10;
            OBDResp.data[1] = 0x13;
            OBDResp.data[2] = 0x49;
            OBDResp.data[3] = 0x04;
            OBDResp.data[4] = CALID[0];
            OBDResp.data[5] = CALID[1];
            OBDResp.data[6] = CALID[2];
            OBDResp.data[7] = CALID[3];
          can_tp_transmit(can_idx, OBDResp, OBDResp.len);

            // Second frame
            OBDResp.data[0] = 0x21;
            for (i = 0; i < 7; i++)
                OBDResp.data[i + 1] = CALID[i + 4];
          can_tp_transmit(can_idx, OBDResp, OBDResp.len);

            // Third frame
            OBDResp.data[0] = 0x22;
            for (i = 0; i < 8; i++)
                OBDResp.data[i + 1] = CALID[i + 11];
           can_tp_transmit(can_idx, OBDResp, OBDResp.len);
            break;
        }

        case 0x0A: // ECU Name (ASCII string, padded to 20)
        {
            char ECUName[20] = "Engine_Control_ECU";
            uint8 nameLen = strlen(ECUName);

            OBDResp.len = 8;
            OBDResp.data[0] = 0x10;
            OBDResp.data[1] = 0x17;
            OBDResp.data[2] = 0x49;
            OBDResp.data[3] = 0x0A;
            OBDResp.data[4] = ECUName[0];
            OBDResp.data[5] = ECUName[1];
            OBDResp.data[6] = ECUName[2];
            OBDResp.data[7] = ECUName[3];
           can_tp_transmit(can_idx, OBDResp, OBDResp.len);

            OBDResp.data[0] = 0x21;
            for (i = 0; i < 7; i++)
                OBDResp.data[i + 1] = ECUName[i + 4];
          can_tp_transmit(can_idx, OBDResp, OBDResp.len);

            OBDResp.data[0] = 0x22;
            for ( i = 0; i < 8; i++)
                OBDResp.data[i + 1] = (i + 11 < nameLen) ? ECUName[i + 11] : 0x00;
          can_tp_transmit(can_idx, OBDResp, OBDResp.len);
            break;
        }

        default:
        {
            // Negative Response
            OBDResp.len = 4;
            OBDResp.data[0] = 0x03;
            OBDResp.data[1] = 0x7F;
            OBDResp.data[2] = 0x09;
            OBDResp.data[3] = 0x12;
           can_tp_transmit(can_idx, OBDResp, OBDResp.len);
            break;
        }
    }
}
