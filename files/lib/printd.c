#include <lib/printd.h>
#include <sys/io.h>

#define true 1
#define false 0

char print_buffer[1000] = {0};

static void write_character(char c)
{

}

static void write_int(int i)
{

}

static void write_unsigned(unsigned u)
{

}

static void write_float(float f)
{

}

static void write_double(double d)
{

}

static void write_long_long(long long l)
{

}
static void write_unsigned_long_long(unsigned long long llu)
{

}

static void error(char *string,int pos)
{

}

void print_d(char* format,...) 
{
	char *traverse; 
	unsigned int u; 
	int i;
	char *s;
	char c;
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
			case 'f': f = (float)va_arg(arg,double);
				write_float(f);
				break;
			case 'l':
				if((*(traverse + 1) != '\0') && (*(traverse + 1) == 'l'))
				{
					if((*(traverse + 2) != '\0') && (*(traverse + 2) == 'l' || *(traverse + 2) =='u'))
						is_64bit = true;
				}
				else if((*(traverse + 1) != '\0') && (*(traverse + 1) == 'f'))
				{
					is_double = true;
					d = va_arg(arg,double);
					write_double(d);
					traverse++;
					string_pos++;
					break;
				}
				if(!is_64bit && !is_double)
				{
					if(*(traverse + 1) != '\0')
					{
						if(*(traverse + 1) == 'd')
						{
							i = va_arg(arg,int);
							write_int(i);
							traverse++;
							string_pos++;
						}
						else if(*(traverse + 1)  == 'u')
						{
							u = va_arg(arg,unsigned int);
							write_int(i);
							traverse++;
							string_pos++;
						}
						else
						{
							error(format,string_pos);
							error_string = true;
							break;
						}
					}
					else
					{
						i = va_arg(arg,int);
						write_int(i);
						break;
					}
				}
				else if(is_64bit && !is_double)
				{
					if(*(traverse + 2) == 'd')
					{
						l = va_arg(arg,long long int);
						write_long_long(l);
						traverse += 2;
						string_pos += 2;
						break;
					}
					else
						ull = va_arg(arg,unsigned long long int);
						write_unsigned_long_long(ull);
						traverse += 2;
						string_pos += 2;
						break;
				}
				else
				{
					error(format,string_pos);
					break;
				}
				break;
			default:
				error(format,string_pos);
				break;
		}
	}

	va_end(arg);
}