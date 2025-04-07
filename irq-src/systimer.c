#include "systimer.h"

const unsigned int timer1_int = CLOCKHZ;
unsigned int timer1_val = 0;

// const unsigned int timer3_int = CLOCKHZ / 4;
// unsigned int timer3_val = 0;

// System timer needs to be setup in start.S. System Timer C/S reg routes bits to interrupt controller.
// sys timer only works in boot when we use no offset? 

void timer_init() {
    timer1_val = REGS_SYSTIMER->counter_lo; // read-only register with low 32b of current running count 
    timer1_val += timer1_int; // sys ticks started in boot, so this is already running

    // compare[1] for timer1. Once the low 32b of current count matches this value, bit is set in System Timer C/S reg
    REGS_SYSTIMER->compare[1] = timer1_val; 

    // timer3_val = REGS_TIMER->counter_lo;
    // timer3_val += timer3_int;
    // REGS_TIMER->compare[3] = timer3_val;
}

void handle_timer_1() {

    gpio_toggle(ACT_LED_GPIO);
    timer1_val += timer1_int; // means timer1_int ticks have passed, increment value another timer1_int ticks
    REGS_SYSTIMER->compare[1] = timer1_val; // and then set this to output compare 
    REGS_SYSTIMER->control_status |= SYS_TIMER_IRQ_1; // and write a 1 to clear the match detect status bit and IRQ line

}