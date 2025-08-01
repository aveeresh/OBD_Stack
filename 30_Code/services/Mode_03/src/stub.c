#include "mode_03.h"

static DTC dtc_list[] = {
    {0x01, 0x01},  
    {0x01, 0x11},
		{0x01, 0x02},  
    {0x01, 0x03}
};

DTC* get_confirmed_dtcs(uint8* dtc_count) {
    if (dtc_count) {
        *dtc_count = sizeof(dtc_list) / sizeof(DTC);  // Return number of stub DTCs
    }
    return dtc_list;
}
