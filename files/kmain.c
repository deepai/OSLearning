#include <vga/frame-buffer.h>
#include <misc/text.h>
#include <sys/serial.h>
#include <sys/gdt.h>
#include <lib/printd.h>

void kmain()
{
	clear_screen();
	init_serial();
	gdt_install();
	//init_serial_port();

	//print_d("%d",5);
	write(INTRODUCTION,INTRODUCTION_SIZE * sizeof(char));
}
