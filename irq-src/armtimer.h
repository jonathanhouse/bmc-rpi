#ifndef ARMTIMER_H
#define ARMTIMER_H

#include "base.h"

struct armtimer_regs_bcm2711{

    volatile unsigned int load; // Load : 0x400
    volatile unsigned int value; // Value (Read-only) : 0x404
    volatile unsigned int control; // Control : 0x408
    volatile unsigned int irqcntl; // IRQ Control/ACK : 0x40c
    volatile unsigned int rawirq; // Raw IRQ (Read-only) : 0x410
    volatile unsigned int mskriq; // Masked IRQ : 0x414
    volatile unsigned int reload; // Reload : 0x418
    volatile unsigned int prediv; // Pre-divider : 41c
    volatile unsigned int freecnt; // Free running counter  

};

typedef struct armtimer_regs_bcm2711 armtimer_regs;

#define ARMTIMER_BASE 0xb000UL
#define ARMTIMER_INIT_OFFSET 0x400UL

#define REGS_ARMTIMER ((armtimer_regs *)(PERIPHERAL_BASE + ARMTIMER_BASE + ARMTIMER_INIT_OFFSET))

#define ARMTIMER_CTRL_32BIT (1 << 1)

#define ARMTIMER_CTRL_PRESCALE_256 (2 << 2)
#define ARMTIMER_CTRL_PRESCALE_16 (1 << 2)
#define ARMTIMER_CTRL_PRESCALE_1 (0 << 2)

#define ARMTIMER_CTRL_INT_ENABLE (1 << 5)

#define ARMTIMER_CTRL_ENABLE (1 << 7)

void setup_armtimer();

#endif 
