.globl irq_init_vectors
irq_init_vectors:
    adr x0, vectors
    msr vbar_el1, x0       // move vectors in Vector Base Address Register (@ EL1: Kernel Mode )
    ret

.globl irq_enable
irq_enable:
    msr daifclr, #2         // access to clearing interrupt mask bits. clearing bit 2 enables IRQs. cpsie i in arm32.
    ret

.globl irq_disable
irq_disable:
    msr daifset, #2         // access to setting interrupt mask bits. setting bit 2 disables IRQs. cpsid i in arm32.
    ret

.globl irq_barrier
irq_barrier:
    dsb sy                  // data-synchronization-barrier. "sy" for full system r/w's? See "ARMv8 Reference Manual" Table B2-1
    ret

.globl get_el
get_el:
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ret
