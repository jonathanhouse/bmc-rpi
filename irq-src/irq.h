#ifndef IRQ_H
#define IRQ_H

#include "base.h"
#include "gic-400.h"
#include "systimer.h"

// ARMC Registers - see "BCM2711 ARM Peripherals" Sec 6.5.3 Table 117
struct arm_irq_regs_2711 {
    volatile unsigned int irq0_pending_0;
    volatile unsigned int irq0_pending_1;
    volatile unsigned int irq0_pending_2;
    volatile unsigned int res0;
    volatile unsigned int irq0_enable_0; // really just use this one
    volatile unsigned int irq0_enable_1;
    volatile unsigned int irq0_enable_2;
    volatile unsigned int res1;
    volatile unsigned int irq0_disable_0;
    volatile unsigned int irq0_disable_1;
    volatile unsigned int irq0_disable_2;
    // more registers (eg. irqX denotes core X) but we stop here 
};
typedef struct arm_irq_regs_2711 arm_irq_regs;


// Sec. 6.5.3 Table 117 indicates base phys address is 0x7e00_b000 (maps to 0xfe00_b000). 
// However, noting the table offsets, the first usable address is at +0x200 (not +0x00).
// ARMC_REG_BASE = 0xb200 is acceptable, but we separate offsets for clarity.
#define ARMC_REG_BASE 0x0000B000UL 
#define ARMC_INIT_OFFSET 0x200UL
#define REGS_IRQ ((arm_irq_regs *)(PERIPHERAL_BASE + ARMC_REG_BASE + ARMC_INIT_OFFSET))

// VideoCore GPU IRQs: BCM2711 ARM Peripherals" Sec 6.2.4 Table 102. Says 4 IRQs come from System Timer Ch. 10
enum vc_irqs { 
    SYS_TIMER_IRQ_0 = 1 << 0,
    SYS_TIMER_IRQ_1 = 1 << 1,
    SYS_TIMER_IRQ_2 = 1 << 2,
    SYS_TIMER_IRQ_3 = 1 << 3,
    AUX_IRQ = (1 << 29)
};

void irq_init_vectors();
void irq_enable();
void irq_barrier();
void irq_disable();
void enable_interrupt_controller();
void disable_interrupt_controller();

#endif