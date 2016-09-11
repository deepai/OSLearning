#include <lib/printd.h>
#include <sys/serial.h>
#include <lib/common.h>
#include <vga/frame-buffer.h>

#define true 1
#define false 0

#define MAX_BUFFER_LEN 1000

static void clear_print_buffer();
static void flush_print_buffer();
static int print_character(char c);
static int print_int(int i);
static void error(char *string,int pos);
static int print_unsigned(unsigned u);

int print_s(char *input);

char print_buffer[MAX_BUFFER_LEN + 1] = {0};
int buffer_pos = 0;

static void clear_print_buffer()
{
	for(int i=0;i<MAX_BUFFER_LEN;i++)
		print_buffer[i] = 0;
	buffer_pos = 0;
}

static void flush_print_buffer()
{
	if(buffer_pos == 0)
		return;
	write(print_buffer,buffer_pos);
	clear_print_buffer();
}

static int print_character(char c)
{
	if(buffer_pos == MAX_BUFFER_LEN)
	{
		flush_print_buffer();
	}
	print_buffer[buffer_pos++] = c; 
	return 1;
}

static int print_int(int i)
{
	char number[10];
	int pos = 0,count=0;
	if(i < 0)
	{
		print_character('-');
		count++;
		i = -i;
	}
	if(i == 0)
	{
		print_character('0');
		count++;
		return count;
	}
	while(i != 0)
	{
		number[pos++] = (mod(i,10) + '0'); //Integer value in terms of character
		i = i/10;
		count++;
	}

	for(;pos>0;pos--)
		print_character(number[pos - 1]);

	return count;
}

static int print_unsigned(unsigned u)
{
	char number[10];
	int pos = 0,count=0;

	if(u == 0)
	{
		print_character('0');
		count++;
		return count;
	}
	while(u != 0)
	{
		number[pos++] = (mod(u,10) + '0');
		u = u/10;
		count++;
	}

	for(;pos>0;pos--)
		print_character(number[pos - 1]);

	return count;
}
static void error(char *string,int pos)
{
	char *text = "Error at Position : ";
	print_s(text);
	print_int(pos);
	print_s("\n");
	print_s(string);
	print_s("\n");
}

int print_s(char *input)
{
	int len = strlen(input);
	int i = 0;
	for(i =0 ;i < len; i++)
		print_character(input[i]);

	return len;
}

int print_d(char* format,...) 
{
	char *traverse; 
	unsigned int u; 
	int i;
	char *s;

	//Initializing arguments
	va_list arg;
	va_start(arg,format);

	int error_string = false;

	int string_pos = 0;

	int chars_written = 0;

	for(traverse = format; *traverse != '\0' && !error_string; traverse++,string_pos++)
	{
		while(*traverse != '%')
		{
			if(*traverse == '\0')
				break;

			chars_written += print_character(*traverse);
			traverse++;
			string_pos++;
		}

		if(*traverse == '\0')
			break;

		traverse++;
		string_pos++;

		switch(*traverse)
		{
			case 'c': i = va_arg(arg,int);
				chars_written += print_character(i);
				//traverse++;
				//string_pos++;
				break;
			case 'd': i = va_arg(arg,int);
				print_int(i);
				//traverse++;
				//string_pos++;
				break;
			case 'u': u = va_arg(arg,unsigned int);
				chars_written += print_unsigned(u);
				//traverse++;
				//string_pos++;
				break;
			case 's': s = va_arg(arg,char *);
				chars_written += print_s(s);
				//traverse++;
				//string_pos++;
				break;
			default:
				error(format,string_pos);
				chars_written = -1;
				break;
		}
	}
	va_end(arg);

	flush_print_buffer();
	clear_print_buffer();

	return chars_written;
}