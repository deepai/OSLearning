INC = -I include/

DEPS = include/vga/*.h include/sys/*.h

OBJECTS = files/sys/loader.o \
	  files/kmain.o \
	  files/vga/frame-buffer.o \
	  files/sys/io.o \
	  files/sys/serial.o \
	  files/lib/printd.o \
	  files/lib/common.o
CC = gcc
CFLAGS = -m32 -nostdlib -fno-builtin -fno-stack-protector $(INC) \
          -std=gnu99 -ffreestanding -c -Wall #-Wextra -c

LD_PATH = files/misc/link.ld

LDFLAGS = -T $(LD_PATH) $(INC) -melf_i386
AS = nasm
ASFLAGS = -f elf32 $(INC)

all: kernel.elf

kernel.elf: $(OBJECTS) $(DEPS)
	ld $(LDFLAGS) $(OBJECTS) $(INC) -o $@

os.iso: kernel.elf
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
		-b boot/grub/stage2_eltorito    \
		-no-emul-boot                   \
		-boot-load-size 4               \
		-A os                           \
		-input-charset utf8             \
		-quiet                          \
		-boot-info-table                \
		-o os.iso                       \
		iso
run: os.iso
	bochs -f bochsrc.txt -q

%.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

%.o: %.s
	$(AS) $(ASFLAGS) $< -o $@
clean:
	rm -rf *.o kernel.elf os.iso files/sys/*.o files/*.o files/vga/*.o
