#include "mode_03.h"

void mode_03_handler(uint32 id,uint8 len){
	can_msg_t response;
	uint8 dtc_count,i,total_length;
	
	DTC* dtcs = get_confirmed_dtcs(&dtc_count);   // Get the DTCs 

	
	if(len != 1){   //Invalid request format
		response.id = 0x7E8;
		
		response.data[0] = SERVICE_03_RESPONSE_SID;   	//Response SID 0x40 + Request SID
		response.data[1] = SUBFUNCTION_NOT_SUPPORTED;   // Negative response code for invalid format
		
		response.len=2;
		
		can_tp_transmit(can_ctrl_1, response,response.len);
		
		return;
	}

	if(dtc_count == 0){ // If there are no DTCs then service byte followed by zeros is transmitted
		
		response.id = 0x7E8; 
		
		response.data[0] = SERVICE_03_RESPONSE_SID;  //Response SID 0x40 + Request SID
		response.data[1] = 0x00;  // Padding with zeros
		
		response.len = 2;
		
		can_tp_transmit(can_ctrl_1, response,response.len);
		
		return;
	}
	
	
	response.id = 0x7E8; 
	
	response.len = 2 + (dtc_count*2);         // Total frame length including data[0]
	
	response.data[0] = SERVICE_03_RESPONSE_SID;  //Response SID 0x40 + Request SID
	response.data[1] = dtc_count;    //Number of DTCs
	
	
	for(i=0 ;i<dtc_count;i++){
		response.data[2 + (i*2)] = dtcs[i].high_byte;   //Storing the High Byte
		response.data[3 + (i*2)] = dtcs[i].low_byte;	//Storing the Low Byte
	}

	can_tp_transmit(can_ctrl_1, response,response.len);	 //Send this DTC data to the transport layer
}

