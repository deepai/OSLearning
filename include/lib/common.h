#ifndef _H_COMMON
#define _H_COMMON

int mod (int a, int b);
void memcpy(unsigned char *dest, const unsigned char *src, int count);
void memset(unsigned char *dest, unsigned char val, int count);
void memsetw(unsigned short *dest, unsigned short val, int count);
int strlen(const char *str);
int strcmp(const char *a,const char *b);

#endif