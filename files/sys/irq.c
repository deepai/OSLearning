#include <sys/irq.h>
#include <sys/io.h>
#include <lib/printk.h>
#include <lib/common.h>
#include <vga/frame-buffer.h>
#include <lib/common.h>
#include <misc/text.h>

/* This array is actually an array of function pointers. We use
*  this to handle custom IRQ handlers for a given IRQ */
void *irq_routines[16] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

/* This installs a custom IRQ handler for the given IRQ */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

/* This clears the handler for a given IRQ */
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}


/* We first remap the interrupt controllers, and then we install
*  the appropriate ISRs to the correct entries in the IDT. This
*  is just like installing the exception handlers */
void irq_install()
{
    idt_set_gate(32, (unsigned)irq_handler_0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)irq_handler_1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)irq_handler_2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)irq_handler_3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)irq_handler_4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)irq_handler_5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)irq_handler_6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)irq_handler_7, 0x08, 0x8E);
    idt_set_gate(40, (unsigned)irq_handler_8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)irq_handler_9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned)irq_handler_10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)irq_handler_11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)irq_handler_12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)irq_handler_13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)irq_handler_14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned)irq_handler_15, 0x08, 0x8E);

    print_k("%s\n",IRQ_MESSAGE);
}

/* Each of the IRQ ISRs point to this function, rather than
*  the 'fault_handler' in 'isrs.c'. The IRQ Controllers need
*  to be told when you are done servicing them, so you need
*  to send them an "End of Interrupt" command (0x20). There
*  are two 8259 chips: The first exists at 0x20, the second
*  exists at 0xA0. If the second controller (an IRQ from 8 to
*  15) gets an interrupt, you need to acknowledge the
*  interrupt at BOTH controllers, otherwise, you only send
*  an EOI command to the first controller. If you don't send
*  an EOI, you won't raise any more IRQs */
void irq_handler(struct regs *r)
{
    /* If the IDT entry that was invoked was greater than 40
    *  (meaning IRQ8 - 15), then we need to send an EOI to
    *  the slave controller */
    print_k("Interrupt Generated = %d \n",r->int_no);

	if (r->int_no >= 40)
	{
		outb(0xA0, 0x20);
	}
	/* In either case, we need to send an EOI to the master
	*  interrupt controller too */
	outb(0x20, 0x20);
	/* This is a blank function pointer */
	void (*handler)(struct regs *r);

	/* Find out if we have a custom handler to run for this
	*  IRQ, and then finally, run it */
	handler = irq_routines[r->int_no - 32];
	if (handler)
	{
		handler(r);
	}
}

