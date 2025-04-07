#ifndef GPIO_H
#define GPIO_H


#include "base.h"

#define ACT_LED_GPIO_BIT 10
#define ACT_LED_GPIO 42

// GPIO Register View. See "BMC2711 ARM Peripherals" Sec 5.2 page 66
#define GPIO_OFFSET 0x200000UL
struct arm_2711_gpio_regs {
    volatile unsigned int gpfsel0;      /* GPIO Function Select 0: offset=0x00 */
    volatile unsigned int gpfsel1;      /* GPIO Function Select 1: 0x04 */
    volatile unsigned int gpfsel2;      /* GPIO Function Select 2: 0x08 */
    volatile unsigned int gpfsel3;      /* GPIO Function Select 3: 0x0c */
    volatile unsigned int gpfsel4;      /* GPIO Function Select 4: 0x10 */
    volatile unsigned int gpfsel5;      /* GPIO Function Select 4: 0x14 */
    volatile unsigned int padding0;     /* 0x18 */
    volatile unsigned int gpset0;       /* GPIO Pin Output Set 0: 0x1c */
    volatile unsigned int gpset1;       /* GPIO Pin Output Set 1: 0x20 */
    volatile unsigned int padding1;     /* 0x24 */
    volatile unsigned int gpclr0;       /* GPIO Pin Output Clear 0: 0x28 */
    volatile unsigned int gpclr1;       /* GPIO Pin Output Clear 1: 0x2c */
    volatile unsigned int padding2;     /* 0x30 */
    volatile unsigned int gplev0;       /* GPIO Pin Level 0: 0x34 */
    volatile unsigned int gplev1;       /* GPIO Pin Level 1: 0x38 */
    volatile unsigned int padding3;     /* 0x3c */
    volatile unsigned int gpeds0;       /* GPIO Pin Event Detection Status 0: 0x40 */
    volatile unsigned int gpeds1;       /* GPIO Pin Event Detection Status 1: 0x44 */
    volatile unsigned int padding4;     /* 0x48 */
    volatile unsigned int gpren0;       /* GPIO Pin Rising Edge Detect Enable 0: 0x4c */
    volatile unsigned int gpren1;       /* GPIO Pin Rising Edge Detect Enable 1: 0x50 */
    volatile unsigned int padding5;     /* 0x54 */
    volatile unsigned int gpfen0;       /* GPIO Pin Falling Edge Detect Enable 0: 0x58 */
    volatile unsigned int gpfen1;       /* GPIO Pin Falling Edge Detect Enable 1: 0x5c */
    volatile unsigned int padding6;     /* 0x60 */
    volatile unsigned int gphen0;       /* GPIO Pin High Detect Enable 0: 0x64 */
    volatile unsigned int gphen1;       /* GPIO Pin High Detect Enable 1: 0x68 */
    volatile unsigned int padding7;     /* 0x6c */
    volatile unsigned int gplen0;       /* GPIO Pin Low Detect Enable 0: 0x70 */
    volatile unsigned int gplen1;       /* GPIO Pin Low Detect Enable 1: 0x74 */
    volatile unsigned int padding8;     /* 0x78 */
    volatile unsigned int gparen0;      /* GPIO Pin Async Rising Edge Detect Enable 0: 0x7c */
    volatile unsigned int gparen1;      /* GPIO Pin Async Rising Edge Detect Enable 1: 0x80 */
    volatile unsigned int padding9;     /* 0x84 */
    volatile unsigned int gpafen0;      /* GPIO Pin Async Falling Edge Detect Enable 0: 0x88 */
    volatile unsigned int gpafen1;      /* GPIO Pin Async Falling Edge Detect Enable 1: 0x8c */
    volatile unsigned int padding10[(0xe4 - 0x90) / 4]; /* 0x90 - 0xe4 */
    volatile unsigned int gpio_pup_pdn_cntrl_reg0;   /* GPIO Pull-up / Pull-down Register 0: 0xe4 */
    volatile unsigned int gpio_pup_pdn_cntrl_reg1;   /* GPIO Pull-up / Pull-down Register 1: 0xe8 */
    volatile unsigned int gpio_pup_pdn_cntrl_reg2;   /* GPIO Pull-up / Pull-down Register 2: 0xec */
    volatile unsigned int gpio_pup_pdn_cntrl_reg3;   /* GPIO Pull-up / Pull-down Register 3: 0xf0 */
};
typedef struct arm_2711_gpio_regs arm_gpio_regs;
#define GPIO_REGS ((arm_gpio_regs *)(PERIPHERAL_BASE + GPIO_OFFSET))

void gpio_fselect(unsigned int mode, unsigned int pin);
void gpio_set(unsigned int pin);
void gpio_clear(unsigned int pin);
unsigned int gpio_level(unsigned int pin);
void gpio_toggle(unsigned int pin);

#endif