#include "CAN_Driver.h"
#include "Can_Regs.h"
#include "MCU_Regs.h"

#define MEG(x) (x * 1000000)
#define KIL(x) (x * 1000)


static Can_GeneralRegs_t *CanRegs[] = {(Can_GeneralRegs_t*)0x40044000, (Can_GeneralRegs_t*)0x40048000};

void can_init(can_idx_t CanIdx) 
{
	if(CanIdx==can_ctrl_1)
		PCONP.B.PCCAN1 = 0x01; // Power ON CAN1
	else
	{
		PCONP.B.PCCAN2 = 0x01;  // Power ON CAN2
	}
}

void can_set_baudrate(can_idx_t CanIdx, uint32 baudrate_Kbps, uint32 PCLK_MHz, uint8 SJW, uint8 TSEG1, uint8 TSEG2)
{
	uint8 BRP;
	switch (baudrate_Kbps) {
        case 125:  
            BRP = (MEG(PCLK_MHz)/ ((KIL(baudrate_Kbps)) *(TSEG1+TSEG2+1)))-1;
            break;
        case 250:  
            BRP = (MEG(PCLK_MHz)/ ((KIL(baudrate_Kbps)) *(TSEG1+TSEG2+1)))-1;
            break;
        case 500:  
            BRP = (MEG(PCLK_MHz)/ ((KIL(baudrate_Kbps)) *(TSEG1+TSEG2+1)))-1; 
            break;
        case 1000: 
            BRP = (MEG(PCLK_MHz)/ ((KIL(baudrate_Kbps)) *(TSEG1+TSEG2+1)))-1;
            break;
        
    }
    //BRP = (MEG(PCLK_MHz)/ ((KIL(baudrate_Kbps)) *(TSEG1+TSEG2+1)))-1;
		CanRegs[CanIdx]->MOD.B.RM = 1;
	  CanRegs[CanIdx]->BTR.B.BRP = BRP;
		CanRegs[CanIdx]->BTR.B.SJW = SJW;
		CanRegs[CanIdx]->BTR.B.TSEG1 = TSEG1-1;
		CanRegs[CanIdx]->BTR.B.TSEG2 = TSEG2-1;
		CanRegs[CanIdx]->MOD.B.RM = 0;
		//#endif
}

void can_transmit(can_idx_t CanIdx, can_msg_t msg) 
{
	  while (!(CanRegs[CanIdx]->SR.B.TBS1)); // Wait until TX buffer is empty
		CanRegs[CanIdx]->TFI1.B.DLC    = msg.len;  //load DLC
		CanRegs[CanIdx]->TID1.StdId.Id = msg.id;   //TxMsg.id.StdId.value;   can_id.StdId.Id
		CanRegs[CanIdx]->TDA1.R        = *((uint32 *)& msg.data[0]); // Load first 4 bytes
		CanRegs[CanIdx]->TDB1.R        = *((uint32 *)& msg.data[4]); // Load next 4 bytes
	  CanRegs[CanIdx]->CMR.R         = (1 << 5) | (1 << 0); // Request transmission
	  //CanRegs[CanIdx]->CMR.B.TR   = 1;  // Transmission Request
   // CanRegs[CanIdx]->CMR.B.STB1 = 1;  // Select Tx Buffer 1
	  
		//while(!((CAN1->GSR)&(0x01<<3)));
}

uint8 can_receive(can_idx_t CanIdx, can_msg_t *msg)
{
	 // Check if Receive Buffer has a message
	 if (CanRegs[CanIdx]->SR.B.RBS1) 
		 {
            msg->id = CanRegs[CanIdx]->RID.StdId.Id;   // Read Identifier
            msg->len = CanRegs[CanIdx]->RFS.B.DLC; // Extract Data Length
            *((uint32 *)&msg->data[0]) = CanRegs[CanIdx]->RDA.R; // Read first 4 bytes
            *((uint32 *)&msg->data[4]) = CanRegs[CanIdx]->RDB.R; // Read next 4 bytes
            return 1; // Message received successfully
     }
			return 0;  // No message received
}



