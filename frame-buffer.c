#include "frame-buffer.h"
#include "io.h"


char *pointer_to_frame_buff = (char *)0x000B8000;

unsigned short *cursor = (unsigned short *)0x000B8000;
unsigned int cursor_loc = 0;

void fb_write_cell(unsigned short pos,char c,unsigned char fg,unsigned char bg)
{
	unsigned short value = 0;
	
	unsigned short attrib = ((bg & 0x0F) << 4 | (fg & 0x0F));
	attrib <<= 8;

	value = value | attrib;

	value = value | c;
	
	cursor[pos] = value;
}


void fb_move_cursor(unsigned short pos)
{
	outb(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
	outb(FB_DATA_PORT, ((pos>>8)&0x00FF));

	outb(FB_COMMAND_PORT,FB_LOW_BYTE_COMMAND);
	outb(FB_DATA_PORT, pos&0x00FF);	
}

void clear_row(int row)
{
	for(int j=0;j<80;j++)
		fb_write_cell(row*80+j,' ',15,0);
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


void fb_scroll_up()
{
	unsigned short *temp = (unsigned short *)pointer_to_frame_buff;

	for(int i=0;i<24;i++)
		for(int j=0;j<79;j++)
		{
			temp[i*80 + j] = temp[(i+1)*80 + j];			
		}

	clear_row(24);
}

void fb_scroll_down()
{
	unsigned short *temp = (unsigned short *)pointer_to_frame_buff;

        for(int i=24;i>0;i--)
                for(int j=0;j<79;j++)
                {
                	temp[i*80 + j] = temp[(i-1)*80 + j];        
                }

        clear_row(0);
}

void advance_cursor()
{
	cursor_loc++;
	if(cursor_loc == (80 * 25))
	{
		cursor_loc = 79 * 25;
		fb_scroll_up();
	}
	fb_move_cursor(cursor_loc);
}


int write(const char *buf,int len)
{
	int count_char_written = 0;
	for(int i=0;i<len;i++)
	{
		fb_write_cell(cursor_loc,buf[i],15,0);
		advance_cursor();
		count_char_written++;
	}
	return count_char_written;
}
	 
