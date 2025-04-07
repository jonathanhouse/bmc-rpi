#include "gpio.h"

void gpio_fselect(unsigned int mode, unsigned int pin){

    switch(pin/10){

        case 0:
            GPIO_REGS->gpfsel0 = mode << 3*(pin % 10);
            break;
        case 1: 
            GPIO_REGS->gpfsel1 = mode << 3*(pin % 10);
            break;
        case 2: 
            GPIO_REGS->gpfsel2 = mode << 3*(pin % 10);
            break;
        case 3: 
            GPIO_REGS->gpfsel3 = mode << 3*(pin % 10);
            break;
        case 4:
            GPIO_REGS->gpfsel4 = mode << 3*(pin % 10);
            break;
        case 5:
            GPIO_REGS->gpfsel5 = mode << 3*(pin % 10);
            break;

    }

}

void gpio_set(unsigned int pin){

    switch(pin/32){

        case 0:
            GPIO_REGS->gpset0 = 1 << (pin % 32);
            break;
        
        case 1: 
            GPIO_REGS->gpset1 = 1 << (pin % 32);
            break;

    }

}

void gpio_clear(unsigned int pin){
    
    switch(pin/32){

        case 0:{

            GPIO_REGS->gpclr0 = 1 << (pin % 32);
            break;
        }
        
        case 1: {

            GPIO_REGS->gpclr1 = 1 << (pin % 32);
            break;
        }

    }

}

unsigned int gpio_level(unsigned int pin){

    volatile unsigned int level = 0x00U;
    switch(pin/32){

        case 0: 
            level = GPIO_REGS->gplev0;
            level = level & (1 << (pin % 32));
            break;
        case 1: 
            level = GPIO_REGS->gplev1;
            level = level & (1 << (pin % 32));
            break;
    }

    return level > 0x00U ? 0x01U : 0x00U;

}

void gpio_toggle(unsigned int pin){

    volatile unsigned int level = gpio_level(pin);
    if(level > 0x00U){
        gpio_clear(pin);
    }
    else {
        gpio_set(pin);
    }

}