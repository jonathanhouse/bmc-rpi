#ifndef BASE_H
#define BASE_H

// page 7 says 
/*
"The peripheral addresses specified in this document are legacy master addresses. Software accessing peripherals
using the DMA engines must use 32-bit legacy master addresses. The Main peripherals are available from 0x7C00_0000
to 0x7FFF_FFFF. Behind the scenes, the VideoCore transparently translates these addresses to the 35-bit 0x4_7nnn_nnnn
addresses.
So a peripheral described in this document as being at legacy address 0x7Enn_nnnn is available in the 35-bit address
space at 0x4_7Enn_nnnn, and visible to the ARM at 0x0_FEnn_nnnn if Low Peripheral mode is enabled."
*/
#define PERIPHERAL_BASE 0xFE000000UL

void write32(void *reg, unsigned int x);
unsigned int read32(void *reg);

extern int get_el ( void );

#endif 