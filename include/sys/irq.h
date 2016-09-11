#ifndef __IRQ_H
#define __IRQ_H

#include <sys/idt.h>

extern void irq_handler_0();
extern void irq_handler_1();
extern void irq_handler_2();
extern void irq_handler_3();
extern void irq_handler_4();
extern void irq_handler_5();
extern void irq_handler_6();
extern void irq_handler_7();
extern void irq_handler_8();
extern void irq_handler_9();
extern void irq_handler_10();
extern void irq_handler_11();
extern void irq_handler_12();
extern void irq_handler_13();
extern void irq_handler_14();
extern void irq_handler_15();

void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void irq_handler();

#endif