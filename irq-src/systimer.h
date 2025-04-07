#ifndef SYSTIMER_H
#define SYSTIMER_H

#include "base.h"
#include "gpio.h"
#include "irq.h"

#define CLOCKHZ 1000000

// See Sec. 10.2 Table 166 of "BCM2711 ARM Peripherals"
struct systimer_regs {
    volatile unsigned int control_status;
    volatile unsigned int counter_lo;
    volatile unsigned int counter_hi;
    volatile unsigned int compare[4];
};

#define SYSTIMER_BASE_REG 0x3000UL
#define REGS_SYSTIMER ((struct systimer_regs *)(PERIPHERAL_BASE + SYSTIMER_BASE_REG))

void handle_timer_1();
void timer_init();
// void handle_timer_3();

#endif