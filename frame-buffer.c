#include "frame-buffer.h"
#include "io.h"


char *pointer_to_frame_buff = (char *)0x000B8000;

void fb_write_cell(unsigned short i,char c,unsigned char fg,unsigned char bg)
{
	unsigned short *temp = (unsigned short *)pointer_to_frame_buff;
	
	unsigned short value = 0;
	
	unsigned short attrib = ((bg & 0x0F) << 4 | (fg & 0x0F));
	attrib <<= 8;

	value = value | attrib;

	value = value | c;
	
	temp[i] = value;
}

void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos>>8)&0x00FF));

	outb(FB_COMMAND_PORT,FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos&0x00FF);	
}

void clear_screen()
{
	for(int i=0;i<25;i++)
		for(int j=0;j<80;j++)
		{
			fb_write_cell(i*80+j,' ',15,0);
		}	
	fb_move_cursor(0);
}
	 
