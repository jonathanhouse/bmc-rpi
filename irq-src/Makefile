CFILES = $(wildcard *.c)
SFILES = $(wildcard *.S)
OFILES = $(CFILES:.c=.o) $(SFILES:.S=.o)
GCCFLAGS = -Wall -O2 -ffreestanding -nostdinc -nostdlib -nostartfiles -mstrict-align
GCCPATH = ../../arm-gnu-toolchain-14.2.rel1-darwin-arm64-aarch64-none-elf/bin

all: clean kernel8.img

%.o: %.c 
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

%.o: %.S 
	$(GCCPATH)/aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

kernel8.img: $(OFILES)
	$(GCCPATH)/aarch64-none-elf-ld -nostdlib $(OFILES) -T link.ld -o kernel8.elf
	$(GCCPATH)/aarch64-none-elf-objcopy -O binary kernel8.elf kernel8.img

clean: 
	/bin/rm *.elf *.o *.img || true