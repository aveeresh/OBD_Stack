#include "CAN_Driver.h"
#include "Can_Regs.h"
#include "MCU_Regs.h"

#define MEG(x) (x * 1000000)
#define KIL(x) (x * 1000)


static Can_GeneralRegs_t *CanRegs[] = {(Can_GeneralRegs_t*)0x40044000, (Can_GeneralRegs_t*)0x40048000};

static can_callback_entry_t registered_callbacks[MAX_CALLBACKS];
static int i;

void can_init(can_idx_t CanIdx) 
{
	if(CanIdx==can_ctrl_1)
		PCONP.B.PCCAN1 = 0x01; // Power ON CAN1
	else
	{
		PCONP.B.PCCAN2 = 0x01;  // Power ON CAN2
	}
	CanRegs[CanIdx]->IER.B.RIE = 1; // Enable receive interrupt
	ISER0_t.B.ISE_CAN=1;   // Enable CAN interrupt in NVIC
	
}

void can_set_baudrate(can_idx_t CanIdx, uint32 baudrate_Kbps, uint32 PCLK_MHz, uint8 SJW, uint8 TSEG1, uint8 TSEG2)
{
    uint8 BRP = (MEG(PCLK_MHz) / (KIL(baudrate_Kbps) * (TSEG1 + TSEG2 + 1))) - 1;
		CanRegs[CanIdx]->MOD.B.RM = 1;
	  CanRegs[CanIdx]->BTR.B.BRP = BRP;
		CanRegs[CanIdx]->BTR.B.SJW = SJW;
		CanRegs[CanIdx]->BTR.B.TSEG1 = TSEG1-1;
		CanRegs[CanIdx]->BTR.B.TSEG2 = TSEG2-1;
	
    CanRegs[CanIdx]->MOD.B.RM = 0; // Leave reset mode
	
}

void can_transmit(can_idx_t CanIdx, can_msg_t msg) 
{
	  while (!(CanRegs[CanIdx]->SR.B.TBS1)); // Wait until TX buffer is empty
		CanRegs[CanIdx]->TFI1.B.DLC    = msg.len;  //load DLC
		CanRegs[CanIdx]->TID1.StdId.Id = msg.id;   //TxMsg.id.StdId.value;   can_id.StdId.Id
		CanRegs[CanIdx]->TDA1.R        = *((uint32 *)& msg.data[0]); // Load first 4 bytes
		CanRegs[CanIdx]->TDB1.R        = *((uint32 *)& msg.data[4]); // Load next 4 bytes
		CanRegs[CanIdx]->CMR.R         = (1 << 5) | (1 << 0); // Request transmission
		//while(!((CAN1->GSR)&(0x01<<3)));
}

uint8 can_receive(can_idx_t CanIdx, can_msg_t *msg)
{
	if (CanRegs[CanIdx]->SR.B.RBS1) {
		// Check if Receive Buffer has a message
            msg->id = CanRegs[CanIdx]->RID.StdId.Id;   // Read Identifier
            msg->len = CanRegs[CanIdx]->RFS.B.DLC; // Extract Data Length
            *((uint32 *)&msg->data[0]) = CanRegs[CanIdx]->RDA.R; // Read first 4 bytes
            *((uint32 *)&msg->data[4]) = CanRegs[CanIdx]->RDB.R; // Read next 4 bytes
            return 1; // Message received successfully
        }
			return 0;  // No message received
}

// Register callback for a specific CAN ID
void can_register_callback(uint32 id, can_callback_t callback)
{
    for (i = 0; i < MAX_CALLBACKS; ++i) {
        if (registered_callbacks[i].callback == 0) {
            registered_callbacks[i].id = id;
            registered_callbacks[i].callback = callback;
            break;
        }
    }
}

void CAN_IRQHandler(void)
{
     can_msg_t *msg;
     can_idx_t CanIdx;
	
	// Check if a message is available in RX buffer
    if (CanRegs[CanIdx]->SR.B.RBS1) 
    {
        // Read CAN message
	   msg->id = CanRegs[CanIdx]->RID.StdId.Id;   // Read Identifier
     msg->len = CanRegs[CanIdx]->RFS.B.DLC; // Extract Data Length
     *((uint32 *)&msg->data[0]) = CanRegs[CanIdx]->RDA.R; // Read first 4 bytes
     *((uint32 *)&msg->data[4]) = CanRegs[CanIdx]->RDB.R; // Read next 4 bytes
	   CanRegs[CanIdx]->CMR.B.RRB=1; // release RX buffer

      for (i = 0; i < MAX_CALLBACKS; ++i) 
	    {
        //if (registered_callbacks[i].callback != 0 && registered_callbacks[i].id == msg->id) 
				// Match registered ID exactly
            // Or match functional ID 0x7DF
            // Or if 0x7E0 is registered, match range 0x7E0–0x7EF
				 if (msg->id == registered_callbacks[i].id ||
                (registered_callbacks[i].id == 0x7DF && msg->id == 0x7DF) ||
                (registered_callbacks[i].id == 0x7E0 && msg->id >= 0x7E0 && msg->id <= 0x7EF))
				{
            registered_callbacks[i].callback(msg);
        }
      }
    }		
}




