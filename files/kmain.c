#include <vga/frame-buffer.h>
#include <misc/text.h>
#include <sys/serial.h>
#include <sys/gdt.h>
//#include <lib/printd.h>
#include <sys/idt.h>
#include <sys/irq.h>

void kmain()
{
	clear_screen();
	init_serial();
	gdt_install();
	init_idt_isr();

	asm volatile ("int $0x3");

	//irq_install();
	//enable_interrupts();
	//init_serial_port();

	// //print_d("%d",5);
	// int val1 = 5;
	// int val2 = 6 - 4 - 2;
	// val1 = val1/val2;
	//write(INTRODUCTION,INTRODUCTION_SIZE * sizeof(char));
}
