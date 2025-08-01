#ifndef TIMER_REGS_H
#define TIMER_REGS_H

#include "types.h"  

typedef union {
    uint32 R;
    struct {
        uint32 CE:4;
        uint32 CR:4;
        uint32 :24;
    } B;
} Timer_IR_t;

typedef union {
    uint32 R;
    struct {
        uint32 CIS:2;
        uint32 :14;
        uint32 CAP:1;
        uint32 :15;
    } B;
} Timer_CR_t;

typedef union {
    uint32 R;
    struct {
        uint32 MR0I:1;
        uint32 MR0R:1;
        uint32 MR0S:1;
        uint32 MR1I:1;
        uint32 MR1R:1;
        uint32 MR1S:1;
        uint32 MR2I:1;
        uint32 MR2R:1;
        uint32 MR2S:1;
        uint32 MR3I:1;
        uint32 MR3R:1;
        uint32 MR3S:1;
        uint32 :20;
    } B;
} Timer_MCR_t;

typedef union {
    uint32 R;
    struct {
        uint32 PWMC0:1;
        uint32 PWMC1:1;
        uint32 PWMC2:1;
        uint32 PWMC3:1;
        uint32 :28;
    } B;
} Timer_PWMC_t;

typedef union {
    uint32 R;
    struct {
        uint32 CTM:2;
        uint32 CIS:2;
        uint32 :28;
    } B;
} Timer_CTCR_t;

typedef union {
    uint32 R;
    struct {
        uint32 ENABLE:1;
        uint32 RESET:1;
        uint32 :30;
    } B;
} Timer_TCR_t;


typedef struct {
    Timer_IR_t IR;
    uint32 TCR;
    uint32 TC;
    uint32 PR;
    uint32 PC;
    Timer_MCR_t MCR;
    uint32 MR0;
    uint32 MR1;
    uint32 MR2;
    uint32 MR3;
    Timer_CR_t CCR;
    uint32 CR0;
    uint32 CR1;
    Timer_CTCR_t CTCR;
    uint32 PWMC;
} Timer_Regs_t;

#define TIMER0      ((volatile Timer_Regs_t*) 0x40004000)
#define ISER0       (*(volatile uint32*) 0xE000E100)
#define IPR0 				((volatile uint8 *)0xE000E400)
#endif 
