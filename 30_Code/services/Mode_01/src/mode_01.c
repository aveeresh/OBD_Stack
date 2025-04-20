void Mode_01_Req_Handler(CanMsg_t OBDRequest) {
    uint8 A = 0, B = 0, C = 0, D = 0;
    CAN_msg OBDResp;
    uint8 i;
	uint8 PID = OBDRequest.data[2]; 

    // List of supported Mode 01 PIDs
    static const uint8 supported_pids[] = {
        0x00, 0x04, 0x05, 0x20,
        0x2D, 0x2F, 0x40,
        0x45, 0x46, 0x60,
        0x62, 0x63, 0x80,
        0x85, 0x8E, 0xA0, 0xA2,
        0xC0, 0xC3, 0xC4
    };

    uint8 supported = 0;

    if (OBDRequest.len < 3) return; // Invalid request length

    // Check if requested PID is supported
    for (i = 0; i < sizeof(supported_pids) / sizeof(supported_pids[0]); i++) {
        if (supported_pids[i] == PID) {
            supported = 1;
            break;
        }
    }

    if (!supported) return; // PID not supported

    OBDResp.id = 0x7E8;
    OBDResp.data[1] = 0x41; // Response to Mode 01
    OBDResp.data[2] = PID;

    switch (PID) {
        case 0x00:  // Supported PIDs [01 - 20]
            A = (PIDValues[PID_IDX_SUPPORTED_00] >> 24) & 0xFF;
            B = (PIDValues[PID_IDX_SUPPORTED_00] >> 16) & 0xFF;
            C = (PIDValues[PID_IDX_SUPPORTED_00] >> 8) & 0xFF;
            D = PIDValues[PID_IDX_SUPPORTED_00] & 0xFF;
            OBDResp.data[3] = A;
            OBDResp.data[4] = B;
            OBDResp.data[5] = C;
            OBDResp.data[6] = D;
            len = 6;
            break;

        case 0x04:  // Calculated Engine Load (%)
            A = (PIDValues[PID_IDX_ENGINE_LOAD_04] * 255) / 100;
            OBDResp.data[3] = A;
            len = 3;
            break;

        case 0x05:  // Engine Coolant Temperature (°C + 40)
            A = PIDValues[PID_IDX_COOLANT_TEMP_05] + 40;
            OBDResp.data[3] = A;
            len = 3;
            break;

        case 0x20:  // Supported PIDs [21 - 40]
            A = (PIDValues[PID_IDX_SUPPORTED_20] >> 24) & 0xFF;
            B = (PIDValues[PID_IDX_SUPPORTED_20] >> 16) & 0xFF;
            C = (PIDValues[PID_IDX_SUPPORTED_20] >> 8) & 0xFF;
            D = PIDValues[PID_IDX_SUPPORTED_20] & 0xFF;
            OBDResp.data[3] = A;
            OBDResp.data[4] = B;
            OBDResp.data[5] = C;
            OBDResp.data[6] = D;
            len = 6;
            break;

        case 0x2D:  // Fuel Rail Pressure
            A = ((PIDValues[PID_IDX_FUEL_RAIL_PRESSURE_2D] + 100) * 128) / 100;
            OBDResp.data[3] = A;
            len = 3;
            break;

        case 0x2F:  // Fuel Level Input (%)
            A = (PIDValues[PID_IDX_FUEL_LEVEL_2F] * 255) / 100;
            OBDResp.data[3] = A;
            len = 3;
            break;

        case 0x40:  // Supported PIDs [41 - 60]
            A = (PIDValues[PID_IDX_SUPPORTED_40] >> 24) & 0xFF;
            B = (PIDValues[PID_IDX_SUPPORTED_40] >> 16) & 0xFF;
            C = (PIDValues[PID_IDX_SUPPORTED_40] >> 8) & 0xFF;
            D = PIDValues[PID_IDX_SUPPORTED_40] & 0xFF;
            OBDResp.data[3] = A;
            OBDResp.data[4] = B;
            OBDResp.data[5] = C;
            OBDResp.data[6] = D;
            len = 6;
            break;

        case 0x45:  // Ambient Air Temperature (%)
            A = (PIDValues[PID_IDX_AMBIENT_TEMP_45] * 255) / 100;
            OBDResp.data[3] = A;
            len = 3;
            break;

        case 0x46:  // Absolute Barometric Pressure (+40)
            A = PIDValues[PID_IDX_ABS_BARO_PRESSURE_46] + 40;
            OBDResp.data[3] = A;
            len = 3;
            break;

        case 0x60:  // Supported PIDs [61 - 80]
            A = (PIDValues[PID_IDX_SUPPORTED_60] >> 24) & 0xFF;
            B = (PIDValues[PID_IDX_SUPPORTED_60] >> 16) & 0xFF;
            C = (PIDValues[PID_IDX_SUPPORTED_60] >> 8) & 0xFF;
            D = PIDValues[PID_IDX_SUPPORTED_60] & 0xFF;
            OBDResp.data[3] = A;
            OBDResp.data[4] = B;
            OBDResp.data[5] = C;
            OBDResp.data[6] = D;
            len = 6;
            break;

        case 0x62:  // Commanded Equivalence Ratio (+125)
            A = PIDValues[PID_IDX_COMMANDED_EQUIV_RATIO_62] + 125;
            OBDResp.data[3] = A;
            len = 3;
            break;

        case 0x63:  // Engine Reference Torque (2 bytes)
            A = (PIDValues[PID_IDX_ENGINE_REFERENCE_TORQUE_63] >> 8) & 0xFF;
            B = PIDValues[PID_IDX_ENGINE_REFERENCE_TORQUE_63] & 0xFF;
            OBDResp.data[3] = A;
            OBDResp.data[4] = B;
            len = 4;
            break;

        case 0x80:  // Supported PIDs [81 - A0]
            A = (PIDValues[PID_IDX_SUPPORTED_80] >> 24) & 0xFF;
            B = (PIDValues[PID_IDX_SUPPORTED_80] >> 16) & 0xFF;
            C = (PIDValues[PID_IDX_SUPPORTED_80] >> 8) & 0xFF;
            D = PIDValues[PID_IDX_SUPPORTED_80] & 0xFF;
            OBDResp.data[3] = A;
            OBDResp.data[4] = B;
            OBDResp.data[5] = C;
            OBDResp.data[6] = D;
            len = 6;
            break;

        case 0x85:  // Throttle Position (%)
            A = (PIDValues[PID_IDX_THROTTLE_POS_85] * 255) / 100;
            OBDResp.data[3] = A;
            len = 3;
            break;

        case 0x8E:  // Engine Friction Percent Torque (+125)*2
            A = (uint8)((PIDValues[PID_IDX_ENGINE_FRICTION_PERCENT_8E] + 125) * 2);
            OBDResp.data[3] = A;
            len = 3;
            break;

        case 0xA0:  // Supported PIDs [A1 - C0]
            A = (PIDValues[PID_IDX_SUPPORTED_A0] >> 24) & 0xFF;
            B = (PIDValues[PID_IDX_SUPPORTED_A0] >> 16) & 0xFF;
            C = (PIDValues[PID_IDX_SUPPORTED_A0] >> 8) & 0xFF;
            D = PIDValues[PID_IDX_SUPPORTED_A0] & 0xFF;
            OBDResp.data[3] = A;
            OBDResp.data[4] = B;
            OBDResp.data[5] = C;
            OBDResp.data[6] = D;
            len = 6;
            break;

        case 0xA2:  // Engine Percent Torque (scaled)
            A = (PIDValues[PID_IDX_ENGINE_PERCENT_TORQUE_A2] * 128) / 100;
            OBDResp.data[3] = A;
            len = 3;
            break;

        default:
            return; // Do nothing if PID is not matched
    }

    OBDResp.data[0] = len;  // Set response length
    OBDResp.len = len + 1;
    can_tp_transmit(CANCTRL1, OBDResp, OBDResp.len);  // Transmit the response
}
