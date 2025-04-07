#include "irq.h"

#define ENABLED_IRQS SYS_TIMER_IRQ_1 // //SYS_TIMER_IRQ_1 | SYS_TIMER_IRQ_3

void enable_interrupt(unsigned int irq) {
	 unsigned int n = irq / 32;
	 unsigned int offset = irq % 32;
	 unsigned int enableRegister = GICD_ENABLE_IRQ_BASE + (4*n);
	 write32((void*)enableRegister, 1 << offset);
}

void assign_target(unsigned int irq, unsigned int cpu) {
	 unsigned int n = irq / 4;
	 unsigned int targetRegister = GIC_IRQ_TARGET_BASE + (4*n);
	 // Currently we only enter the target CPU 0
	 write32((void*)targetRegister, read32((void*)targetRegister) | (1 << 8));
}

void enable_interrupt_controller() {
    // gic400_init((void*)GIC400_BASE);
	 assign_target(ENABLED_IRQS, 0);
	 enable_interrupt(ENABLED_IRQS);
    REGS_IRQ->irq0_enable_0 = ENABLED_IRQS;
    // REGS_IRQ->irq0_enable_2 = 1 << 0;
}

void disable_interrupt_controller() {
    REGS_IRQ->irq0_enable_0 = 0;
}

void handle_irq() {
    unsigned int irq = REGS_IRQ->irq0_pending_0;
    // gpio_toggle(ACT_LED_GPIO);
    // gpio_set(ACT_LED_GPIO);

    // while(1){

    //     gpio_toggle(ACT_LED_GPIO);
    //     for(unsigned int i = 0; i < 2500000; i++);

    // }

    while(irq & ENABLED_IRQS) {

        // handle SYS_TIMER_1 INT 
        if (irq & SYS_TIMER_IRQ_1) {
            irq &= ~SYS_TIMER_IRQ_1; // clears reg copy, not actual sys reg

            handle_timer_1();
        }

        // if (irq & SYS_TIMER_IRQ_3) {
        //     irq &= ~SYS_TIMER_IRQ_3;

        //     handle_timer_3();
        // }
    }
}