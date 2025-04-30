#include "irq.h"

#define ENABLED_IRQS SYS_TIMER_IRQ_1 // //SYS_TIMER_IRQ_1 | SYS_TIMER_IRQ_3

void enable_interrupt(unsigned int irq) {
	 unsigned int n = irq / 32;
	 unsigned int offset = irq % 32;
	 unsigned int enableRegister = GICD_ENABLE_IRQ_BASE + (4*n);  // 12.9.27 
	 write32((void*)enableRegister, 1 << offset);
}

void assign_target(unsigned int irq, unsigned int cpu) {
	 unsigned int n = irq / 4;
     unsigned int offset = irq % 4;
	 unsigned int targetRegister = GIC_IRQ_TARGET_BASE + (4*n);
	 // Currently we only enter the target CPU 0
     // first byte corresponds to INT0, and setting a 1 in bits 0:7 maps to using CPU0 -> CPU7
     // therefore, set for INT1 and use CPU0, we set bit 8. 
     // theoretically, by the same logic setting bit 16 should give INT2 to CPU0, but it's not working
	//  write32((void*)targetRegister, read32((void*)targetRegister) | (1 << (8*offset))); 
    write32((void*)targetRegister, 1 << (8*offset) );
}

void enable_interrupt_controller() {

	//  assign_target(SYS_TIMER_IRQ_1, 0);
	//  enable_interrupt(SYS_TIMER_IRQ_1); // probably okay

    // can literally be disabled for timer 1 and still works?? 
	 assign_target(1, 0); // can be 1, NOT SYS_TIMER_IRQ_1, and still works
	 enable_interrupt(1); // can be 1, not SYS_TIMER_IRQ_1, and still works 

    //  write32((void*)GICD_CTLR, 0x00000000);

    // gic400_init((void*)(GIC400_BASE));
    //  assign_target(96+1, 0); // global to all cpu interfaces, should use INT ID. If you check math on address there's 
                                // enough space for ID0-ID1019 which exactly the total number listed in doc
    //  enable_interrupt(96+1); // 

    //  write32((void*)GICD_CTLR, 0x00000001);

    //  write32((void*)GICC_PMR, 0xf0);
    //  write32((void*)GICC_CTLR, 0x00000001);


    REGS_IRQ->irq0_enable_0 = ENABLED_IRQS;
    // REGS_IRQ->irq0_enable_2 = 1 << 0;
}

void disable_interrupt_controller() {
    REGS_IRQ->irq0_enable_0 = 0;
}

void handle_irq() {
    unsigned int irq = REGS_IRQ->irq0_pending_0;

    while(irq & ENABLED_IRQS) {

        // handle SYS_TIMER_1 INT 
        if (irq & SYS_TIMER_IRQ_1) {
            irq &= ~SYS_TIMER_IRQ_1; // clears reg copy, not actual sys reg

            handle_timer_1();
        }

        if (irq & SYS_TIMER_IRQ_2) {
            irq &= ~SYS_TIMER_IRQ_2; // clears reg copy, not actual sys reg

            handle_timer_2();
        }

        // if (irq & SYS_TIMER_IRQ_3) {
        //     irq &= ~SYS_TIMER_IRQ_3;

        //     handle_timer_3();
        // }
    }
}