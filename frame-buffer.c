#include "frame-buffer.h"

char *pointer_to_frame_buff = (char *)0x000B8000;

void fb_write_cell(unsigned short i,char c,unsigned char fg,unsigned char bg)
{
	char *temp =pointer_to_frame_buff;
	
	unsigned short value = c;
	value <<= 8;
	
	unsigned short color = ((fg & 0x0F) << 4 | (bg & 0x0F));

	value = value | color;
	
	temp[i] = value;
}
	 
