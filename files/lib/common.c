#include <lib/common.h>

int mod(int a,int b)
{
	int c = a/b;
	int v = a - b*c;
	return v;
}