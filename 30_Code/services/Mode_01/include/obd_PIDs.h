#ifndef OBD_PIDS_H
#define OBD_PIDS_H

#include "Types.h"  // Ensure this includes typedef for uint32

// Macro definitions for PID indices
#define PID_SUPPORTED_00                   0
#define PID_ENGINE_LOAD_04                 1
#define PID_COOLANT_TEMP_05                2
#define PID_SUPPORTED_20                   3
#define PID_FUEL_RAIL_PRESSURE_2D          4
#define PID_FUEL_LEVEL_2F                  5
#define PID_SUPPORTED_40                   6
#define PID_AMBIENT_TEMP_45                7
#define PID_ABS_BARO_PRESSURE_46           8
#define PID_SUPPORTED_60                   9
#define PID_COMMANDED_EQUIV_RATIO_62      10
#define PID_ENGINE_REFERENCE_TORQUE_63    11
#define PID_SUPPORTED_80                  12
#define PID_THROTTLE_POS_85               13
#define PID_ENGINE_FRICTION_PERCENT_8E    14
#define PID_SUPPORTED_A0                  15
#define PID_ENGINE_PERCENT_TORQUE_A2      16
#define PID_SUPPORTED_C0                  17

// Total number of supported PIDs
#define PID_COUNT 18

// Enum for PID index access — improves readability
typedef enum {
    PID_IDX_SUPPORTED_00                = PID_SUPPORTED_00,
    PID_IDX_ENGINE_LOAD_04             = PID_ENGINE_LOAD_04,
    PID_IDX_COOLANT_TEMP_05            = PID_COOLANT_TEMP_05,
    PID_IDX_SUPPORTED_20               = PID_SUPPORTED_20,
    PID_IDX_FUEL_RAIL_PRESSURE_2D      = PID_FUEL_RAIL_PRESSURE_2D,
    PID_IDX_FUEL_LEVEL_2F              = PID_FUEL_LEVEL_2F,
    PID_IDX_SUPPORTED_40               = PID_SUPPORTED_40,
    PID_IDX_AMBIENT_TEMP_45            = PID_AMBIENT_TEMP_45,
    PID_IDX_ABS_BARO_PRESSURE_46       = PID_ABS_BARO_PRESSURE_46,
    PID_IDX_SUPPORTED_60               = PID_SUPPORTED_60,
    PID_IDX_COMMANDED_EQUIV_RATIO_62   = PID_COMMANDED_EQUIV_RATIO_62,
    PID_IDX_ENGINE_REFERENCE_TORQUE_63 = PID_ENGINE_REFERENCE_TORQUE_63,
    PID_IDX_SUPPORTED_80               = PID_SUPPORTED_80,
    PID_IDX_THROTTLE_POS_85            = PID_THROTTLE_POS_85,
    PID_IDX_ENGINE_FRICTION_PERCENT_8E = PID_ENGINE_FRICTION_PERCENT_8E,
    PID_IDX_SUPPORTED_A0               = PID_SUPPORTED_A0,
    PID_IDX_ENGINE_PERCENT_TORQUE_A2   = PID_ENGINE_PERCENT_TORQUE_A2,
    PID_IDX_SUPPORTED_C0               = PID_SUPPORTED_C0
} PIDIndex;

// Global PID values array (defined in .c file)
extern uint32 PIDValues[PID_COUNT];

#endif // OBD_PIDS_H
