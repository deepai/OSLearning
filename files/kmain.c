#include <misc/text.h>
#include <sys/serial.h>
#include <lib/printd.h>
#include <sys/timer.h>
#include <sys/descriptor_table.h>
#include <sys/kb.h>
#include <sys/multiboot.h>
#include <lib/error.h>
#include <sys/elf.h>
#include <vga/frame-buffer.h>

elf_t kernel_elf;

void kmain(multiboot_t *mboot_ptr)
{
	clear_screen();
	print_d("%s\n",INTRODUCTION);

	init_serial();
	init_descriptor_tables();

	//asm volatile("int $0x3"); 
	//asm volatile("int $0x4");
	asm volatile("sti");
	//timer_install();
	register_keyboard();

	kernel_elf = elf_from_multiboot (mboot_ptr);

	// unregister_keyboard();

	
//	asm volatile ("int $0x3");

	//
	//enable_interrupts();
	//init_serial_port();

	// int val1 = 5;
	// int val2 = 6 - 4 - 2;
	// val1 = val1/val2;
}
