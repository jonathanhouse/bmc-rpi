//https://abyz.me.uk/rpi/pigpio/
#include <stdio.h>
#include <pigio.h>


void toggleGPIO(void* gpio_pin_ptr){

    static int first_pass = 1;

    if(first_pass){
        gpioSetMode(gpio_pin, PI_OUTPUT);
        first_pass = 0;
    }

    unsigned int gpio_pin = *((unsigned int*)gpio_pin_ptr);

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

    unsigned int gpio_pin = 17;

    // p_thread_t* t1;
    // t1 = gpioStartThread(toggleLED, gpio_pin); 

    unsigned int ms_timer = 100
    unsigned int timer_num = 0;
    if(gpioSetTimerFuncEx(timer_num, ms_timer, toggleGPIO, gpio_pin)){
        return -2;
    }

    while(1);

    return 1;
}