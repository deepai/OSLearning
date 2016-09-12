#include <misc/text.h>
#include <sys/serial.h>
#include <lib/printd.h>
#include <sys/timer.h>
#include <sys/descriptor_table.h>
#include <vga/frame-buffer.h>

void kmain()
{
	clear_screen();
	print_d("%s\n",INTRODUCTION);

	init_serial();
	init_descriptor_tables();

	//asm volatile("int $0x3"); 
	//asm volatile("int $0x4");
	asm volatile("sti");
	timer_install();

//	asm volatile ("int $0x3");

	//
	//enable_interrupts();
	//init_serial_port();

	// //print_d("%d",5);
	// int val1 = 5;
	// int val2 = 6 - 4 - 2;
	// val1 = val1/val2;
}
