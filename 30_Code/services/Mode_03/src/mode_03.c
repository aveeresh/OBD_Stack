#include "mode_03.h"
#include "cantp.h"
DTC dtc_list[] = {
    {0x01, 0x0A},  
    {0x02, 0x1B}   
};

// Function to get the confirmed DTCs
DTC* get_confirmed_dtcs(uint8* dtc_count) {
    if (dtc_count) {
        // Set the count of confirmed DTCs
        *dtc_count = sizeof(dtc_list) / sizeof(DTC);  // Calculate number of DTCs
    }
    
    return dtc_list;  // Return the array of DTCs
}
void mode_03_handler(uint32 id,uint8 len){
	can_msg_t response;
	uint8 dtc_count,i,total_length;
	
	DTC* dtcs = get_confirmed_dtcs(&dtc_count);   // Get the DTCs 

	
	if(len != 1){   //Invalid request format
		response.id = 0x7E8;
		response.data[0] = 0x02	;       // Total no of bytes to be transmitted
		response.data[1] = SERVICE_03_RESPONSE_SID;   	//Response SID 0x40 + Request SID
		response.data[2] = SUBFUNCTION_NOT_SUPPORTED;   // Negative response code for invalid format
		
		response.len=3;
		
		can_tp_transmit(can_ctrl_1, response,response.len);
		
		return;
	}

	if(dtc_count == 0){ // If there are no DTCs then service byte followed by zeros is transmitted
		
		response.id = 0x7E8; 
		response.data[0] = 0x02;
		response.data[1] = SERVICE_03_RESPONSE_SID;  //Response SID 0x40 + Request SID
		response.data[2] = 0x00;  // Padding with zeros
		
		response.len = 3;
		
		can_tp_transmit(can_ctrl_1, response,response.len);
		
		return;
	}
	
	
	response.id = 0x7E8; 
	
	total_length = 2 + (dtc_count*2); 
	response.len = total_length+1;         // Total frame length including data[0]
	
	response.data[0] = total_length;       // No of Bytes excluding itself
	response.data[1] = SERVICE_03_RESPONSE_SID;  //Response SID 0x40 + Request SID
	response.data[2] = dtc_count;    //Number of DTCs
	
	
	for(i=0 ;i<dtc_count;i++){
		response.data[3 + (i*2)] = dtcs[i].high_byte;   //Storing the High Byte
		response.data[4 + (i*2)] = dtcs[i].low_byte;	//Storing the Low Byte
	}

	can_tp_transmit(can_ctrl_1, response,response.len);	 //Send this DTC data to the transport layer
}

