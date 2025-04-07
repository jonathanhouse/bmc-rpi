#include "armtimer.h"

void setup_armtimer(){

    REGS_ARMTIMER->load = 0x4000;

    REGS_ARMTIMER->control = ARMTIMER_CTRL_32BIT | ARMTIMER_CTRL_PRESCALE_256 |
                            ARMTIMER_CTRL_INT_ENABLE | ARMTIMER_CTRL_ENABLE;

}