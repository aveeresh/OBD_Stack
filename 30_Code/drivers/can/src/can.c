#include "CAN_Driver.h"
#include "obd_handler.h"

#define MEG(x) (x * 1000000)
#define KIL(x) (x * 1000)


volatile uint32 can_irq_counter = 0;
uint32 CAN1ErrCount = 0, CAN2ErrCount = 0;
can_msg_t msg_buf_RX; 
can_idx_t CanIdx;
uint16 i;

void CAN_ISR_Rx1()
{
	uint32 *pDest;
// initialize destination pointer	
  pDest = (uint32 *)&msg_buf_RX;
  *pDest = CAN1->RID.StdId.Id;  // len	

  pDest++;
  *pDest =CAN1->RFS.B.DLC; // ID	

  pDest++;
  *pDest = CAN1->RDA.R; // Data A	

  pDest++;
  *pDest = CAN1->RDB.R; // Data B	
	
	if(CAN1->RID.StdId.Id==0x7DF || CAN1->RID.StdId.Id==0x7E0)
	obd_handler(&msg_buf_RX);
	
	CAN1->CMR.B.RRB = 1;
						
}		


void CAN_ISR_Rx2()
{
	uint32 *pDest;
 // initialize destination pointer	
  pDest = (uint32 *)&msg_buf_RX;
 *pDest = CAN2->RID.StdId.Id;  // len	

  pDest++;
  *pDest = CAN2->RFS.B.DLC; // ID	

  pDest++;
  *pDest = CAN2->RDA.R; // Data A	

  pDest++;
  *pDest = CAN2->RDB.R; // Data B	
	
	if(CAN2->RID.StdId.Id==0x7df || CAN2->RID.StdId.Id==0x7E0)
	obd_handler(&msg_buf_RX);
   CAN2->CMR.B.RRB = 1;
	
}


void CAN_IRQHandler(void)  
{		
  uint32 status;
  can_irq_counter++;  // Set a breakpoint or observe with debugger
	
	status= CANCR->CANRxSR;
	
 if ( status & (1 << 8) )
 {
	  CAN_ISR_Rx1();
  }

  if ( status & (1 << 9) )
  {
	   CAN_ISR_Rx2();
  }
	if ( CAN1->GSR.B.ES)
  {
	CAN1ErrCount = CAN1->GSR.R >> 16;
  }
  
	if ( CAN2->GSR.B.ES)
  {
	CAN2ErrCount = CAN2->GSR.R >> 16;
  return;
	}
}


void can_init(can_idx_t CanIdx)  
{
	if(CanIdx==0)
	{
		PCONP.B.PCCAN1 = 0x01; // Power ON CAN1
			// Configure P0.0 (RD1) and P0.1 (TD1) for CAN1
   // PINSEL0.B.P0_0=0x01;
	 // PINSEL0.B.P0_1=0x01;
	}
	else if (CanIdx==1)
	{
		PCONP.B.PCCAN2 = 0x01;  // Power ON CAN2
		// Configure P0.4 (RD2) and P0.5 (TD2) for CAN2
		// PINSEL0.B.P0_4=0x02;
	  // PINSEL0.B.P0_5=0x02;
	}
	else
		return;
	
	// Configure P0.0 (RD1) and P0.1 (TD1) for CAN1
    PINSEL0.B.P0_0=0x01;
	  PINSEL0.B.P0_1=0x01;
	
}

void can_set_baudrate(can_idx_t CanIdx, uint32 baudrate_Kbps, uint32 PCLK_MHz, uint8 SJW, uint8 TSEG1, uint8 TSEG2)
{
	uint8 BRP=(MEG(PCLK_MHz)/ ((KIL(baudrate_Kbps)) *(TSEG1+TSEG2+1)))-1;
	if(CanIdx==0)
	{ 
	  CAN1->MOD.B.RM =1;   /* Reset CAN */
    CAN1->IER.R =0;    /* Disable Receive Interrupt */
    CAN1->GSR.R =0;    /* Reset error counter when CANxMOD is in reset	*/

    CAN1->BTR.B.BRP = BRP;
		CAN1->BTR.B.SJW = SJW;
		CAN1->BTR.B.TSEG1 = TSEG1-1;
		CAN1->BTR.B.TSEG2 = TSEG2-1;
	   
    CAN1->MOD.B.RM =0; // Leave reset mode

		IPR6_t.B.IP_CAN=1;
    ISER0_t.B.ISE_CAN=1;   // Enable CAN interrupt in NVIC
    CAN1->IER.B.RIE =1;   // Enable receive interrupts  
	}
	
	else if(CanIdx==1)
	{
	   CAN2->MOD.B.RM=1;   // Reset CAN 
     CAN2->IER.R=0;      // Disable Receive Interrupt 
     CAN2->GSR.R=0;      // Reset error counter when CANxMOD is in reset	

     CAN2->BTR.B.BRP = BRP;
		 CAN2->BTR.B.SJW = SJW;
		 CAN2->BTR.B.TSEG1 = TSEG1-1;
		 CAN2->BTR.B.TSEG2 = TSEG2-1;
	   
     CAN2->MOD.B.RM =0;      // Leave reset mode
		
		 IPR6_t.B.IP_CAN=1;
     ISER0_t.B.ISE_CAN=1;   // Enable CAN interrupt in NVIC
     CAN2->IER.B.RIE=1;      // Enable receive interrupts   
	}
	else 
		return;
}
void can_set_accf_lookup( void )
{
  uint32 address = 0;
  uint32 i;
  uint32 ID_high, ID_low;

  /* Set explicit standard Frame */ 
	CANAF->SFF_sa.R = address;
  for ( i = 0; i < ACCF_IDEN_NUM; i += 2 )
  {
	ID_low = (i << 29) | (EXP_STD_ID << 16);
	ID_high = ((i+1) << 13) | (EXP_STD_ID << 0);
	*((volatile uint32 *)(CANAF_RAM_BASE + address)) = ID_low | ID_high;
	address += 4; 
  }
		
  /* Set group standard Frame */
  CANAF->SFF_GRP_sa.R = address;
  for ( i = 0; i < ACCF_IDEN_NUM; i += 2 )
  {
	ID_low = (i << 29) | (GRP_STD_ID << 16);
	ID_high = ((i+1) << 13) | (GRP_STD_ID << 0);
	*((volatile uint32 *)(CANAF_RAM_BASE + address)) = ID_low | ID_high;
	address += 4; 
  }
 
  /* Set explicit extended Frame */ 
  CANAF->EFF_sa.R = address;
  for ( i = 0; i < ACCF_IDEN_NUM; i++  )
  {
	ID_low = (i << 29) | (EXP_EXT_ID << 0);
	*((volatile uint32 *)(CANAF_RAM_BASE + address)) = ID_low;
	address += 4; 
  }

  /* Set group extended Frame */
  CANAF->EFF_GRP_sa.R = address;
  for ( i = 0; i < ACCF_IDEN_NUM; i++  )
  {
	ID_low = (i << 29) | (GRP_EXT_ID << 0);
	*((volatile uint32 *)(CANAF_RAM_BASE + address)) = ID_low;
	address += 4; 
  }
   
  /* Set End of Table */
  CANAF->ENDofTable.R = address;
  return;
}


void can_set_accf( uint32 ACCFMode )
{
	 switch ( ACCFMode )
  {
	case ACCF_OFF:
	  CANAF->AFMR.R = ACCFMode;
	  CAN1->MOD.B.RM =CAN2->MOD.B.RM = 1;  	// Reset CAN
	  CAN1->IER.B.RIE =CAN2 ->IER.B.RIE= 0;	// Disable Receive Interrupt
	  CAN1->GSR.R = CAN2->GSR.R = 0;	      // Reset error counter when CANxMOD is in reset
	break;

	case ACCF_BYPASS:
	  CANAF->AFMR.R = ACCFMode;
	break;

	case ACCF_ON:
	case ACCF_FULLCAN:
	  CANAF->AFMR.R = ACCF_OFF;
	  can_set_accf_lookup();
	  CANAF->AFMR.R = ACCFMode;
	break;

	default:
	break;
  }
  return;
}

void can_transmit(can_idx_t CanIdx, can_msg_t* tx_msg) 
{
	if(CanIdx==0)
	{ 
		while (!(CAN1->SR.B.TBS1));          // Wait until TX buffer is empty
		CAN1->TFI1.B.DLC    = tx_msg->len;  //load DLC
		CAN1->TID1.StdId.Id = tx_msg->id;   //TxMsg.id.StdId.value;   can_id.StdId.Id
		CAN1->TDA1.R = *((uint32 *)& tx_msg->data[0]); // Load first 4 bytes
		CAN1->TDB1.R = *((uint32 *)& tx_msg->data[4]);  // Load next 4 bytes
		CAN1->CMR.B.STB1=CAN1->CMR.B.TR=1; // Request transmission
	}
	else if(CanIdx==1)
	{
		while (!(CAN2->SR.B.TBS1));            // Wait until TX buffer is empty
			CAN2->TFI1.B.DLC    = tx_msg->len;  //load DLC
		  CAN2->TID1.StdId.Id = tx_msg->id;   //TxMsg.id.StdId.value;   can_id.StdId.Id
		  CAN2->TDA1.R = *((uint32 *)& tx_msg->data[0]); // Load first 4 bytes
		  CAN2->TDB1.R = *((uint32 *)& tx_msg->data[4]); // Load next 4 bytes
		  CAN2->CMR.B.STB1=CAN2->CMR.B.TR=1; // Request transmission
	}
	else 
		return;
}


uint8 can_receive(can_idx_t CanIdx, can_msg_t* rx_msg)
{
   if(CanIdx==0)
	 {
	    if (CAN1->SR.B.RBS1) 
				{
	        	// Check if Receive Buffer has a message
            rx_msg->id = CAN1->RID.StdId.Id;   // Read Identifier
            rx_msg->len = CAN1->RFS.B.DLC; // Extract Data Length
            *((uint32 *)&rx_msg->data[0]) = CAN1->RDA.R; // Read first 4 bytes
            *((uint32 *)&rx_msg->data[4]) = CAN1->RDB.R; // Read next 4 bytes
            return 1; // Message received successfully
        }
		}
	 else if(CanIdx==1)
	 {
		  if (CAN2->SR.B.RBS1) 
				{
		        // Check if Receive Buffer has a message
            rx_msg->id = CAN2->RID.StdId.Id;   // Read Identifier
            rx_msg->len = CAN2->RFS.B.DLC; // Extract Data Length
            *((uint32 *)&rx_msg->data[0]) = CAN2->RDA.R; // Read first 4 bytes
            *((uint32 *)&rx_msg->data[4]) = CAN2->RDB.R; // Read next 4 bytes
            return 1; // Message received successfully
        }
	 }
	 		return 0;  // No message received
}






