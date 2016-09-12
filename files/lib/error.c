#include <lib/printk.h>
#include <lib/printd.h>
#include <lib/error.h>
#include <sys/elf.h>

extern elf_t kernel_elf;

void panic (const char *msg)
{
  print_d("*** System panic: %s\n", msg);
  print_stack_trace();
  print_d ("***\n");
  for (;;);
}

void print_stack_trace()
{
	unsigned int *ebp, *eip;
	asm volatile ("mov %%ebp, %0" : "=r" (ebp)); // Start with the current EBP value.
	while (ebp)
	{
		eip = ebp+1;
		print_d("%u %s()\n", *eip, elf_lookup_symbol (*eip, &kernel_elf));
		ebp = (unsigned*) *ebp;
	}
}