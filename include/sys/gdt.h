#ifndef _GDT_H
#define _GDT_H
/* Defines a GDT entry. We say packed, because it prevents the
*  compiler from doing things that it thinks is best: Prevent
*  compiler "optimization" by packing */
struct gdt_entry
{
	unsigned short limit_low;
	unsigned short base_low;
	unsigned char base_middle;
	unsigned char access;
	unsigned char granularity;
	unsigned char base_high;
} __attribute__((packed));

/* Special pointer which includes the limit: The max bytes
*  taken up by the GDT, minus 1. Again, this NEEDS to be packed */
struct gdt_ptr
{
	unsigned short limit;
	unsigned int base;
} __attribute__((packed));

extern void gdt_flush();

/* Our GDT, with 3 entries, and finally our special GDT pointer */
struct gdt_entry gdt[5];
struct gdt_ptr gp;

void gdt_install();

#endif