#include <lib/printd.h>
#include <sys/serial.h>
#include <lib/common.h>

#define true 1
#define false 0

#define MAX_BUFFER_LEN 1000

char print_buffer[MAX_BUFFER_LEN + 1] = {0};
int buffer_pos = 0;

static void clear_buffer()
{
	for(int i=0;i<MAX_BUFFER_LEN;i++)
		print_buffer[i] = 0;
	buffer_pos = 0;
}

static void flush_buffer()
{
	while(buffer_pos < MAX_BUFFER_LEN)
	{
		//write_serial(print_buffer[buffer_pos]);
		buffer_pos++;
	}
	clear_buffer();
}

static void write_character(char c)
{
	if(buffer_pos == MAX_BUFFER_LEN)
	{
		flush_buffer();
	}
	print_buffer[buffer_pos++] = c; 
}

static int write_int(int i)
{
	char number[10];
	int pos = 0,count=0;
	if(i < 0)
	{
		write_character('-');
		count++;
		i = -i;
	}
	if(i == 0)
	{
		write_character('0');
		count++;
		return count;
	}
	while(i != 0)
	{
		number[pos++] = (mod(i,10) + '0');
		i = i/10;
		count++;
	}

	for(;pos>=0;pos--)
		write_character(number[pos++]);

	return count;
}

static int write_unsigned(unsigned u)
{
	char number[10];
	int pos = 0,count=0;

	if(u == 0)
	{
		write_character('0');
		count++;
		return count;
	}
	while(u != 0)
	{
		number[pos++] = (mod(u,10) + '0');
		u = u/10;
		count++;
	}

	for(;pos>=0;pos--)
		write_character(number[pos++]);

	return count;
}

static int write_long_long(long long l)
{
	return 0;
}
static int write_unsigned_long_long(unsigned long long llu)
{
	return 0;
}

static void error(char *string,int pos)
{

}

void print_d(char* format,...) 
{
	char *traverse; 
	unsigned int u; 
	int i;
	//char *s;
	float f;
	double d;
	long long l;
	unsigned long long ull;

	//Initializing arguments
	va_list arg;
	va_start(arg,format);

	int total_length = 0;

	int error_string = false;

	int string_pos = 0;
	int is_64bit = false,is_double = false;
		//calculate the total length of the format string.
	for(traverse = format; *traverse != '\0'; traverse++,total_length++);

	for(traverse = format; *traverse != '\0' && !error_string; traverse++,string_pos++)
	{
		while(*traverse != '%')
		{
			write_character(*traverse);
			traverse++;
			string_pos++;
		}
		traverse++;
		string_pos++;

		switch(*traverse)
		{
			case 'c': i = va_arg(arg,int);
				write_int(i);
				break;
			case 'd': i = va_arg(arg,int);
				write_int(i);
				break;
			case 'u': u = va_arg(arg,unsigned int);
				write_unsigned(u);
				break;
			// case 'l':
			// 	if((*(traverse + 1) != '\0') && (*(traverse + 1) == 'l'))
			// 	{
			// 		if((*(traverse + 2) != '\0') && (*(traverse + 2) == 'l' || *(traverse + 2) =='u'))
			// 			is_64bit = true;
			// 	}
			// 	else if((*(traverse + 1) != '\0') && (*(traverse + 1) == 'f'))
			// 	{
			// 		is_double = true;
			// 		d = va_arg(arg,double);
			// 		write_double(d);
			// 		traverse++;
			// 		string_pos++;
			// 		break;
			// 	}
			// 	if(!is_64bit && !is_double)
			// 	{
			// 		if(*(traverse + 1) != '\0')
			// 		{
			// 			if(*(traverse + 1) == 'd')
			// 			{
			// 				i = va_arg(arg,int);
			// 				write_int(i);
			// 				traverse++;
			// 				string_pos++;
			// 			}
			// 			else if(*(traverse + 1)  == 'u')
			// 			{
			// 				u = va_arg(arg,unsigned int);
			// 				write_int(i);
			// 				traverse++;
			// 				string_pos++;
			// 			}
			// 			else
			// 			{
			// 				error(format,string_pos);
			// 				error_string = true;
			// 				break;
			// 			}
			// 		}
			// 		else
			// 		{
			// 			i = va_arg(arg,int);
			// 			write_int(i);
			// 			break;
			// 		}
			// 	}
			// 	else if(is_64bit && !is_double)
			// 	{
			// 		if(*(traverse + 2) == 'd')
			// 		{
			// 			l = va_arg(arg,long long int);
			// 			write_long_long(l);
			// 			traverse += 2;
			// 			string_pos += 2;
			// 			break;
			// 		}
			// 		else
			// 			ull = va_arg(arg,unsigned long long int);
			// 			write_unsigned_long_long(ull);
			// 			traverse += 2;
			// 			string_pos += 2;
			// 			break;
			// 	}
			// 	else
			// 	{
			// 		error(format,string_pos);
			// 		break;
			// 	}
			// 	break;
			default:
				error(format,string_pos);
				break;
		}
	}
	va_end(arg);

	flush_buffer();
	clear_buffer();
}