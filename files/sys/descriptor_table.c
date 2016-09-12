#include <sys/descriptor_table.h>
#include <sys/idt.h>
#include <sys/gdt.h>

void init_descriptor_tables()
{
	gdt_install();
	idt_install();
}