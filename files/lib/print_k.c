#include <lib/printk.h>
#include <sys/serial.h>
#include <lib/common.h>

#define true 1
#define false 0

#define MAX_BUFFER_LEN 1000

static void clear_serial_buffer();
static void flush_serial_buffer();
static int serial_character(char c);
static int serial_int(int i);
static void error(char *string,int pos);
static int serial_unsigned(unsigned u);

int serial_s(char *input);

char serial_buffer[MAX_BUFFER_LEN + 1] = {0};
int buffer_pos_serial = 0;

static void clear_serial_buffer()
{
	for(int i=0;i<MAX_BUFFER_LEN;i++)
		serial_buffer[i] = 0;
	buffer_pos_serial = 0;
}

static void flush_serial_buffer()
{
	int i = 0;
	if(buffer_pos_serial == 0)
		return;
	for(i=0;i<buffer_pos_serial;i++)
		write_serial(serial_buffer[i]);

	clear_serial_buffer();
}

static int serial_character(char c)
{
	if(buffer_pos_serial == MAX_BUFFER_LEN)
	{
		flush_serial_buffer();
	}
	serial_buffer[buffer_pos_serial++] = c; 
	return 1;
}

static int serial_int(int i)
{
	char number[10];
	int pos = 0,count=0;
	if(i < 0)
	{
		serial_character('-');
		count++;
		i = -i;
	}
	if(i == 0)
	{
		serial_character('0');
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
		serial_character(number[pos - 1]);

	return count;
}

static int serial_unsigned(unsigned u)
{
	char number[10];
	int pos = 0,count=0;

	if(u == 0)
	{
		serial_character('0');
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
		serial_character(number[pos - 1]);

	return count;
}
static void error(char *string,int pos)
{
	char *text = "Error at Position : ";
	serial_s(text);
	serial_int(pos);
	serial_s("\n");
	serial_s(string);
	serial_s("\n");
}

int serial_s(char *input)
{
	int len = strlen(input);
	int i = 0;
	for(i =0 ;i < len; i++)
		serial_character(input[i]);

	return len;
}

int print_k(char* format,...) 
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

			chars_written += serial_character(*traverse);
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
				chars_written += serial_character(i);
				//traverse++;
				//string_pos++;
				break;
			case 'd': i = va_arg(arg,int);
				serial_int(i);
				//traverse++;
				//string_pos++;
				break;
			case 'u': u = va_arg(arg,unsigned int);
				chars_written += serial_unsigned(u);
				//traverse++;
				//string_pos++;
				break;
			case 's': s = va_arg(arg,char *);
				chars_written += serial_s(s);
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

	flush_serial_buffer();
	clear_serial_buffer();

	return chars_written;
}