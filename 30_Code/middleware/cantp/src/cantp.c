#include "cantp.h"

bool can_tp_transmit(can_idx_t can_idx, can_msg_t data, uint16 data_length) {
	
		can_msg_t frame = {0}, fc, cf = {0};
		uint8 i, block_size, stmin, frames_sent=0, sn=1, bytes_left, bytes_to_copy;
		uint16 offset = 6;
		
    if(data_length <= 7){ //Transmit single frame
		
				frame.id = data.id;    // Response ID
		
        frame.data[0] = SINGLE_FRAME | (data_length & 0x0F);
		
        for(i=0; i<data_length;i++){
						frame.data[i+1]= data.data[i]; // Copying the data into the frame
				}
		
        frame.len = data_length + 1;
		
        can_transmit(can_idx,frame);
		
    } 
		else{ 
				
        // Send First Frame
        frame.id = data.id;    // Response ID

        frame.data[0] = FIRST_FRAME | ((data_length >> 8) & 0x0F);
        frame.data[1] = data_length & 0xFF;
		
        for (i = 0; i < 6; i++) {
						frame.data[i + 2] = data.data[i];
				}
		
        frame.len = 8;
		
        can_transmit(can_idx,frame);

        // Wait for Flow Control Frame
        if (!can_receive(can_idx, &fc)) {
						
						// Check if the frame is Flow Control Frame
						if ((fc.data[0] & 0xF0) == FLOW_CONTROL_FRAME){
								
								if((fc.data[0] & 0x0F) == FLOW_STATUS_OVERFLOW){
										return FALSE;
								}
								else if((fc.data[0] & 0x0F) == FLOW_STATUS_CTS){
										block_size = fc.data[1];
										stmin = fc.data[2];
								}
								else if((fc.data[0] & 0x0F) == FLOW_STATUS_WAIT){
										return FALSE;
								}
								else{
										return FALSE;
								}
						}
						else{
								return FALSE;
						}
			
				}
		
				// Send Consecutive Frame

        while(offset < data_length){
						
						cf.id= data.id;
					
            cf.data[0] = CONSEC_FRAME | (sn & 0x0F);
			
            bytes_left = data_length - offset;  //No of bytes remaining to transmit
						bytes_to_copy=7;   // 7 bytes of data can be transmitted per Consecutive frame
			
						if(bytes_left < 7){
								bytes_to_copy = bytes_left; 
						}
			
			
            for (i = 0; i < bytes_to_copy; i++) {
								cf.data[i + 1] = data.data[offset + i];
						}
            
						cf.len = bytes_to_copy + 1; //Length of the Consecutive Frame
						
						can_transmit(can_idx,cf);
						
						offset += bytes_to_copy;
						sn = (sn+1) % 16;           //When sn reaches 15 it will wraparound and set it to zero
						frames_sent++;              
						
						
						if (block_size != 0 && frames_sent == block_size) {  // Checking if no of frames sent is equal to block size
                if (!can_receive(can_idx, &fc) || (fc.data[0] & 0xF0) != FLOW_CONTROL_FRAME){
										return FALSE;
								}
                if ((fc.data[0] & 0x0F) == FLOW_STATUS_OVERFLOW){
										return FALSE;
								}
								if (fc.data[0] == FLOW_STATUS_CTS) {
										block_size = fc.data[1];
										stmin = fc.data[2];
								}
                frames_sent = 0;
            }
						delay_ms(stmin); // Delay between Consecutive Frames
        }
    }
		return TRUE;
}



bool can_tp_receive(can_idx_t can_idx, can_msg_t *data, uint16 data_length) {
    can_msg_t frame, fc = {0};
    uint8 frame_type, sn = 1, i, len;
    uint16 offset = 0, total_len;
    uint8 bytes_to_copy, block_size = 3, frames_received = 0;

    // Wait for first frame (Single or First Frame)
    if (!can_receive(can_idx, &frame)) {
        return FALSE;
    }

    frame_type = frame.data[0] & 0xF0;  //Checking what is the frame type

    if (frame_type == SINGLE_FRAME) {
			
        len = frame.data[0] & 0x0F;

        if (len > data_length){
						return FALSE;
				}
				
				//Copying the data
				
				data->len = len;   
        data->id = frame.id;
				
        for (i = 0; i < len; i++) {
            data->data[i] = frame.data[i + 1];
        }

        return TRUE;
    } 
    
    else if (frame_type == FIRST_FRAME) {
        total_len = ((frame.data[0] & 0x0F) << 8) | frame.data[1];

        if (total_len > data_length){
						return FALSE;
				}

        for (i = 0; i < 6; i++) {
            data->data[i] = frame.data[i + 2];
        }

        offset = 6;

        // Send Flow Control
        fc.id = frame.id;
        fc.data[0] = FLOW_CONTROL_FRAME; // CTS
        fc.data[1] = block_size;
        fc.data[2] = 0x00; // STmin
        fc.len = 8;

        can_transmit(can_idx, fc);

        // Receive Consecutive Frames
        while (offset < total_len) {
            if (!can_receive(can_idx, &frame)) {
                return FALSE;
            }

            if ((frame.data[0] & 0xF0) != CONSEC_FRAME) {
                return FALSE;
            }

            if ((frame.data[0] & 0x0F) != (sn & 0x0F)) {
                return FALSE; // Sequence number mismatch
            }

            sn = (sn + 1) % 16;

            bytes_to_copy = total_len - offset; //No of bytes remaining to copy
						
            if (bytes_to_copy > 7) {
								bytes_to_copy = 7;
						}

            for (i = 0; i < bytes_to_copy; i++) {
                data->data[offset + i] = frame.data[i + 1];
            }

            offset += bytes_to_copy;
            frames_received++;

            if (block_size != 0 && frames_received == block_size) { 
							
                frames_received = 0;

                // Send another Flow Control if needed
                fc.data[0] = FLOW_CONTROL_FRAME;
                fc.data[1] = block_size;
                fc.data[2] = 0x00;
							
                can_transmit(can_idx, fc);
            }
        }

        data->len = total_len;
        data->id = frame.id;

        return TRUE;
    }

    return FALSE; // Not a supported frame type
}
