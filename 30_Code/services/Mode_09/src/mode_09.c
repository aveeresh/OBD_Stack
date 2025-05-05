#include "mode_09.h"
#include <string.h>

void mode_09_req_handler(can_msg_t OBDRequest)
{
    int i;
    uint8 PID = OBDRequest.data[2];  // Get the PID from the incoming message
    can_msg_t OBDResp;  // Declare a CAN response message
    uint8 response_data[64];  // Buffer for response data
    uint8 response_len = 0;   // Length of data in the response buffer

    OBDResp.id = 0x7E8;  // Set response CAN ID

    switch(PID)
    {
        case 0x00: // Supported PIDs
        {
            response_data[response_len++] = 0x49;
            response_data[response_len++] = 0x00;
            response_data[response_len++] = 0x50;
            response_data[response_len++] = 0x04;
            response_data[response_len++] = 0x00;
            response_data[response_len++] = 0x00;
            break;
        }

        case 0x02: // VIN (configured size 17 characters)
        {
            char VIN[PID_0x02_SIZE] = "WAUZAB345XY123456";  // VIN number

            response_data[response_len++] = 0x49;
            response_data[response_len++] = 0x02;
            for (i = 0; i < PID_0x02_SIZE; i++)
                response_data[response_len++] = VIN[i];
            break;
        }

        case 0x04: // Calibration ID (configured size 16 characters)
        {
            char CALID[PID_0x04_SIZE] = "ECU_CAL_ID_12345";

            response_data[response_len++] = 0x49;
            response_data[response_len++] = 0x04;
            for (i = 0; i < PID_0x04_SIZE; i++)
                response_data[response_len++] = CALID[i];
            break;
        }

        case 0x0A: // ECU Name (configured size 20 characters)
        {
            char ECUName[PID_0x0A_SIZE] = "Engine_Control_ECU";
            uint8 nameLen = strlen(ECUName);

            response_data[response_len++] = 0x49;
            response_data[response_len++] = 0x0A;
            for (i = 0; i < PID_0x0A_SIZE; i++)
                response_data[response_len++] = (i < nameLen) ? ECUName[i] : 0x00;
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
            can_tp_transmit(can_ctrl_1, OBDResp, OBDResp.len);
            return;
        }
    }

    // Prepare final response frame
    for (i = 0; i < response_len; i++)
        OBDResp.data[i] = response_data[i];
    OBDResp.len = response_len;

    can_tp_transmit(can_ctrl_1, OBDResp, OBDResp.len);  // Send the response
}
