#include <lib/common.h>

int mod(int a,int b)
{
	int c = a/b;
	int v = a - b*c;
	return v;
}


/* You will need to code these up yourself!  */
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
	for(int i=0;i<count;i++)
		dest[i] = src[i];
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
	for(int i=0;i<count;i++)
		dest[i] = val;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
    /* Same as above, but this time, we're working with a 16-bit
    *  'val' and dest pointer. Your code can be an exact copy of
    *  the above, provided that your local variables if any, are
    *  unsigned short */
    for(int i=0;i<count;i++)
	dest[i] = val;
}

int strlen(const char *str)
{
    /* This loops through character array 'str', returning how
    *  many characters it needs to check before it finds a 0.
    *  In simple words, it returns the length in bytes of a string */
    int len = 0;
    for(len=0; str[len] != '\0'; len++);

    return len;
}

