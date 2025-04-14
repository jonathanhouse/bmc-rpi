//https://abyz.me.uk/rpi/pigpio/
#include <stdio.h>
#include <pigpio.h>
#include <stdlib.h>
#include <pthread.h>

void *toggleGPIO(void* _gpio_pin){


//    static int first_pass = 1;
    unsigned int gpio_pin = ((unsigned int*)_gpio_pin)[0];

//    if(first_pass){
        gpioSetMode(gpio_pin, PI_OUTPUT);
//        first_pass = 0;
//    }

uint32_t us_inc = ((unsigned int*)_gpio_pin)[1];
uint32_t curr_tick = gpioTick();
uint32_t next_tick = curr_tick + us_inc;

while(1){

    if((curr_tick = gpioTick()) >= next_tick){
     next_tick = curr_tick + us_inc; 

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

}

}


int main(){

    if(gpioInitialise() <  0){
        // failed to init
        return -1;
    }


    unsigned int* gpio_pin = malloc(sizeof(unsigned int)*2);
    gpio_pin[0] = 17;

    unsigned int* gpio_pin2 = malloc(sizeof(unsigned int)*2);
    gpio_pin2[0] = 27;


    unsigned int us_timer1 = 1000;
    unsigned int us_timer2 = 1;
   
   gpio_pin[1] = us_timer1;
   gpio_pin2[1] = us_timer2;


    unsigned int timer_num = 0;
    pthread_t p[2];
	
    int rc = pthread_create(&p[0], NULL, toggleGPIO, (void*)gpio_pin);

    int rc2 = pthread_create(&p[1], NULL, toggleGPIO, (void*)gpio_pin2);

//    if( (p = gpioStartThread(&toggleGPIO,NULL)) != NULL){
//	printf("Error in issuing thread");
//        return -2;
//   }
/*
    unsigned int* gpio_pin2 = malloc(sizeof(unsigned int));
    *gpio_pin2 = 27;
    unsigned int ms_timer2 = 10;
    unsigned int timer_num2 = 1;
    if(gpioSetTimerFuncEx(timer_num2, ms_timer2, toggleGPIO, gpio_pin2) != 0){
        printf("Error in issuing callback");
        return -2;
   }
*/

    while(1);
    free(gpio_pin);
//    free(gpio_pin2);
    return 1;

}
