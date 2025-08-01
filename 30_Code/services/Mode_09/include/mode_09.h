#ifndef MODE_09_H
#define MODE_09_H



// Configurable constants for Mode 9 PID data sizes
#define PID_0x00_SIZE 6  // Size of Supported PIDs response
#define PID_0x02_SIZE 17 // Size of VIN (17 characters)
#define PID_0x04_SIZE 16 // Size of Calibration ID (16 characters)
#define PID_0x0A_SIZE 20 // Size of ECU Name (20 characters)

void mode_09_req_handler(can_msg_t OBDRequest);

#endif // MODE_09_H
