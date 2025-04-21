#ifndef CAN_REGS_H
#define CAN_REGS_H

#include "Types.h"

typedef union
{
	uint32 R;
	struct 
	{
		uint32 RM:1;
		uint32 LOM:1;
		uint32 STM:1;
		uint32 TPM:1;
		uint32 SM:1;
		uint32 RPM:1;
		uint32 :1;
		uint32 TM:1;
		uint32 :24;
	}B;
} Can_MOD_t;

typedef union
{
	uint32 R;
	struct
	{
		uint32 TR:1;
		uint32 AT:1;
		uint32 RRB:1;
		uint32 CDO:1;
		uint32 SRR:1;
		uint32 STB1:1;
		uint32 STB2:1;
		uint32 STB3:1;
		uint32 :24;
	}B;
}Can_CMR_t;

typedef union
