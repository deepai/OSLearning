#include <vga/frame-buffer.h>
#include <misc/intro.h>

void kmain()
{
	clear_screen();
	write(INTRODUCTION,(int)(sizeof(INTRODUCTION)/sizeof(char)));
}
