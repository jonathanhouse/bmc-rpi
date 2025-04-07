#include "kernel.h"


void main(void)
{
    irq_init_vectors();
    
    enable_interrupt_controller();
    irq_barrier();
    // GPIO_REGS->gpfsel4 = 0b001 << 6;
    gpio_fselect(0b001, ACT_LED_GPIO); // 0b001 -> output mode 
    timer_init(); 
    // setup_armtimer();

    irq_enable();
    // really subtle sneaky thing bypass gic with interrupt tutorial coming after multicore?... 
  
    // At reset this means the interrupt signal will not be routed to the CPU running code in order to be able to respond to the interrupt.
    //  We will have to add RPI4-specific code which allows us to configure the GIC peripheral to pass the interrupt signal on to one of the CPU cores. 
    //  As we're not doing any multi-core work at the moment we can configure the GIC to
    //   route all interrupt signals to CPU0 which has our interrupt service routines. BrianS
    // gpio_clear(ACT_LED_GPIO);
    // int el = get_el();
    while(1){

        // gpio_toggle(ACT_LED_GPIO);
        // for(unsigned int i = 0; i < 10000000; i++);

    }

}