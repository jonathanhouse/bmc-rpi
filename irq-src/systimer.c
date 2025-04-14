#include "systimer.h"

// System timer needs to be setup in start.S. System Timer C/S reg routes bits to interrupt controller.
// sys timer only works in boot when we use no offset? 

unsigned int timer2_int = CLOCKHZ; // init to this period, but gets modified in timer_init
unsigned int timer2_val = 0;

unsigned int timer1_int = CLOCKHZ;
unsigned int timer1_val = 0;

void timer_init(unsigned int timer_num, unsigned int timer_period) {
    // timer1_val = REGS_SYSTIMER->counter_lo; // read-only register with low 32b of current running count 
    // timer1_val += timer1_int; // sys ticks started in boot, so this is already running

    // // compare[1] for timer1. Once the low 32b of current count matches this value, bit is set in System Timer C/S reg
    // REGS_SYSTIMER->compare[timer_num] = timer1_val; 

    switch(timer_num){

        case 1:{

            timer1_int = timer_period;
            timer1_val = REGS_SYSTIMER->counter_lo; // read-only register with low 32b of current running count 
            timer1_val += timer1_int; // sys ticks started in boot, so this is already running
            // compare[1] for timer1. Once the low 32b of current count matches this value, bit is set in System Timer C/S reg
            REGS_SYSTIMER->compare[timer_num] = timer1_val; 
            break;
        } 
        case 2: {
            timer2_int = timer_period;
            timer2_val = REGS_SYSTIMER->counter_lo; // read-only register with low 32b of current running count 
            timer2_val += timer2_int; // sys ticks started in boot, so this is already running
            // compare[1] for timer1. Once the low 32b of current count matches this value, bit is set in System Timer C/S reg
            REGS_SYSTIMER->compare[timer_num] = timer2_val; 
            break;
        }
    }

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

void handle_timer_2() {

    gpio_toggle(TEST_LED);
    timer2_val += timer2_int; // means timer1_int ticks have passed, increment value another timer1_int ticks
    REGS_SYSTIMER->compare[2] = timer2_val; // and then set this to output compare 
    REGS_SYSTIMER->control_status |= SYS_TIMER_IRQ_2; // and write a 1 to clear the match detect status bit and IRQ line

}