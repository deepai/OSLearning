#include "frame-buffer.h"
#include "intro.h"

void kmain()
{
	clear_screen();
	write(INTRODUCTION,(int)(sizeof(INTRODUCTION)/sizeof(char)));
}
