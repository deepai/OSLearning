#include <vga/frame-buffer.h>
#include <misc/intro.h>
#include <sys/serial.h>

void kmain()
{
	clear_screen();
	init_serial_port();
	write(INTRODUCTION,(int)(sizeof(INTRODUCTION)/sizeof(char)));
}
