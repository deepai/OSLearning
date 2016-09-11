#include <sys/idt.h>
#include <vga/frame-buffer.h>
#include <sys/serial.h>
#include <misc/text.h>
#include <lib/common.h>

struct idt_entry idt[256];
struct idt_ptr idtp;

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
    /* We'll leave you to try and code this function: take the
    *  argument 'base' and split it up into a high and low 16-bits,
    *  storing them in idt[num].base_hi and base_lo. The rest of the
    *  fields that you must set in idt[num] are fairly self-
    *  explanatory when it comes to setup */
	idt[num].always0 = 0;
	idt[num].sel = sel;
	idt[num].flags = flags;

	idt[num].base_lo = (base & 0xFFFF);
	idt[num].base_hi = (base >> 16) & 0xFFFF;
}


/* Installs the IDT */
void idt_install()
{
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
	idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
	idtp.base = &idt;

	long long default_value = 0;

	memset(&idt,0,sizeof(struct idt_entry)*256);
	/* Add any new ISRs to the IDT here using idt_set_gate */

	isrs_install();

	/* Points the processor's internal register to the new IDT */
	idt_load();

	for(int i=0; IDT_MESSAGE[i]!='\0'; i++)
		write_serial(IDT_MESSAGE[i]);
}

void isrs_install()
{
	idt_set_gate(0, (unsigned)interrupt_handler_0, 0x08, 0x8E);
	idt_set_gate(1, (unsigned)interrupt_handler_1, 0x08, 0x8E);
	idt_set_gate(2, (unsigned)interrupt_handler_2, 0x08, 0x8E);
	idt_set_gate(3, (unsigned)interrupt_handler_3, 0x08, 0x8E);
	idt_set_gate(4, (unsigned)interrupt_handler_4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned)interrupt_handler_5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned)interrupt_handler_6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned)interrupt_handler_7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned)interrupt_handler_8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned)interrupt_handler_9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned)interrupt_handler_10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned)interrupt_handler_11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned)interrupt_handler_12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned)interrupt_handler_13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned)interrupt_handler_14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned)interrupt_handler_15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned)interrupt_handler_16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned)interrupt_handler_17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned)interrupt_handler_18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned)interrupt_handler_19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned)interrupt_handler_20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned)interrupt_handler_21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned)interrupt_handler_22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned)interrupt_handler_23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned)interrupt_handler_24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned)interrupt_handler_25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned)interrupt_handler_26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned)interrupt_handler_27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned)interrupt_handler_28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned)interrupt_handler_29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned)interrupt_handler_30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned)interrupt_handler_31, 0x08, 0x8E);

	for(int i=0; IDT_MESSAGE[i] != '\0'; i++)
		write_serial(ISR_MESSAGE[i]);
}

void init_idt_isr()
{
	idt_install();
	//isrs_install();
}

/* This is a simple string array. It contains the message that
*  corresponds to each and every exception. We get the correct
*  message by accessing like:
*  exception_message[interrupt_number] */
char *exception_messages[] =
{
    "Division By Zero\n",
    "Debug\n",
    "Non Maskable Interrupt\n",
    "Breakpoint Exception\n",
    "Into Detected Overflow Exception\n",
    "Out of Bounds Exception\n",
    "Invalid Opcode Exception\n",
    "No Coprocessor Exception\n",
    "Double Fault Exception\n",
    "Coprocessor Segment Overrun Exception\n",
    "Bad TSS Exception\n",
    "Segment Not Present Exception\n",
    "Stack Fault Exception\n",
    "General Protection Fault Exception\n",
    "Page Fault Exception\n",
    "Unknown Interrupt Exception\n",
    "Coprocessor Fault Exception\n",
    "Alignment Check Exception (486+)\n",
    "Machine Check Exception (Pentium/586+)\n",
    "Reserved","Reserved","Reserved","Reserved","Reserved\n",
    "Reserved","Reserved","Reserved","Reserved","Reserved\n",
    "Reserved","Reserved","Reserved"
};

/* All of our Exception handling Interrupt Service Routines will
*  point to this function. This will tell us what exception has
*  happened! Right now, we simply halt the system by hitting an
*  endless loop. All ISRs disable interrupts while they are being
*  serviced as a 'locking' mechanism to prevent an IRQ from
*  happening and messing up kernel data structures */
void fault_handler(struct regs *r)
{
    /* Is this a fault whose number is from 0 to 31? */
    if (r->int_no < 32)
    {
        /* Display the description for the Exception that occurred.
        *  In this tutorial, we will simply halt the system using an
        *  infinite loop */
       // write(exception_messages[r->int_no],-1);
        //write(" Exception. System Halted!\n",-1);
        char *exception_message = exception_messages[r->int_no];
        int len = strlen(exception_message);
        
        for(int i=0;i<len;i++)
        	write_serial(exception_message[i]);

    }
}
