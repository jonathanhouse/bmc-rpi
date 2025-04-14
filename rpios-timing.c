//https://abyz.me.uk/rpi/pigpio/
#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>

void toggleGPIO(void* _gpio_pin){

    static int first_pass = 1;
    unsigned int gpio_pin = *((unsigned int*)_gpio_pin);

    if(first_pass){
        gpioSetMode(gpio_pin, PI_OUTPUT);
        first_pass = 0;
    }


    int gpio_level = gpioRead(gpio_pin);
    if(gpio_level == 1){
        gpioWrite(gpio_pin,0);
    }
    else if (gpio_level == 0){
        gpioWrite(gpio_pin, 1);
    }
    else { // gpio_level = -1

    }

}


int main(){

    if(gpioInitialise() <  0){
        // failed to init
        return -1;
    }

    unsigned int* gpio_pin = malloc(sizeof(unsigned int));
    *gpio_pin = 17;
    unsigned int ms_timer = 100;
    unsigned int timer_num = 0;
    if(gpioSetTimerFuncEx(timer_num, ms_timer, toggleGPIO, gpio_pin) != 0){
	printf("Error in issuing callback");
        return -2;
   }

    unsigned int* gpio_pin2 = malloc(sizeof(unsigned int));
    *gpio_pin2 = 17;
    unsigned int ms_timer2 = 100;
    unsigned int timer_num2 = 1;
    if(gpioSetTimerFuncEx(timer_num2, ms_timer2, toggleGPIO, gpio_pin2) != 0){
        printf("Error in issuing callback");
        return -2;
   }


    while(1);
    return 1;

}
