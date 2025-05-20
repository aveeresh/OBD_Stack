//obd_PIDs.h   
#ifndef OBD_PIDS_H
#define OBD_PIDS_H

#include "Types.h"  // Ensure this includes typedef for uint32

// Macro definitions for PID indices
#define PID_SUPPORTED_00                   0
#define PID_ENGINE_LOAD_04                 1
#define PID_COOLANT_TEMP_05                2
#define PID_ENGINE_RPM_0C                  3
#define PID_SUPPORTED_20                   4
#define	 PID_FUEL_RAIL_PRESSURE_22         5
#define PID_COMMANDED_EGR_2C              6
#define PID_EGR_Error_2D                   7
#define PID_FUEL_LEVEL_2F                  8
#define PID_DISTANCE_SINCE_DTC_31          9
#define PID_SUPPORTED_40                   10
#define PID_AMBIENT_TEMP_45                11
#define PID_ABS_BARO_PRESSURE_46           12
#define PID_SUPPORTED_60                   13
#define PID_Actual_engine_percent_torque_62      14
#define PID_ENGINE_REFERENCE_TORQUE_63    15
#define PID_SUPPORTED_80                  16
#define PID_NOx_reagent_system_85         17
#define PID_ENGINE_FRICTION_PERCENT_8E    18
#define PID_SUPPORTED_A0                  19

 #define  PID_Transmission_Actual_Gear_A4  20
#define	 PID_Commanded_Diesel_Exhaust_Fluid_Dosing_A5  21


// Total number of supported PIDs
#define PID_COUNT 22

// Enum for PID index access — improves readability
typedef enum {
    PID_IDX_SUPPORTED_00                = PID_SUPPORTED_00,
    PID_IDX_ENGINE_LOAD_04             = PID_ENGINE_LOAD_04,
    PID_IDX_COOLANT_TEMP_05            = PID_COOLANT_TEMP_05,
	  PID_IDX_ENGINE_RPM_0C               = PID_ENGINE_RPM_0C ,
    PID_IDX_SUPPORTED_20               = PID_SUPPORTED_20,
	  PID_IDX_FUEL_RAIL_PRESSURE_22      = PID_FUEL_RAIL_PRESSURE_22 ,
	  PID_IDX_COMMANDED_EGR_2C           = PID_COMMANDED_EGR_2C ,
    PID_IDX_EGR_Error_2D              = PID_EGR_Error_2D,
    PID_IDX_FUEL_LEVEL_2F              = PID_FUEL_LEVEL_2F,
	PID_IDX_DISTANCE_SINCE_DTC_31        =	PID_DISTANCE_SINCE_DTC_31 ,
    PID_IDX_SUPPORTED_40               = PID_SUPPORTED_40,
    PID_IDX_AMBIENT_TEMP_45            = PID_AMBIENT_TEMP_45,
    PID_IDX_ABS_BARO_PRESSURE_46       = PID_ABS_BARO_PRESSURE_46,
    PID_IDX_SUPPORTED_60               = PID_SUPPORTED_60,
    PID_IDX_Actual_engine_percent_torque_62   = PID_Actual_engine_percent_torque_62,
    PID_IDX_ENGINE_REFERENCE_TORQUE_63 = PID_ENGINE_REFERENCE_TORQUE_63,
    PID_IDX_SUPPORTED_80               = PID_SUPPORTED_80,
    PID_IDX_NOx_reagent_system_85            = PID_NOx_reagent_system_85,
    PID_IDX_ENGINE_FRICTION_PERCENT_8E = PID_ENGINE_FRICTION_PERCENT_8E,
    PID_IDX_SUPPORTED_A0               = PID_SUPPORTED_A0,
    
 PID_IDX_Transmission_Actual_Gear_A4 =   PID_Transmission_Actual_Gear_A4,
	 PID_IDX_Commanded_Diesel_Exhaust_Fluid_Dosing_A5 =  PID_Commanded_Diesel_Exhaust_Fluid_Dosing_A5,
   
} PIDIndex;

// Global PID values array (defined in .c file)
extern uint32 PIDValues[PID_COUNT];

#endif // OBD_PIDS_H
