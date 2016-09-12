#include <sys/irq.h>
#include <lib/printd.h>
#include <lib/common.h>
#include <sys/io.h>
#include <sys/timer.h>

int timer_ticks = 0;

static int freq = 1193180;

void set_timer_phase(int hz)
{
	int divisor = 1193180 / hz;       /* Calculate our divisor */
	outb(0x43, 0x36);             /* Set our command byte 0x36 */
	outb(0x40, divisor & 0xFF);   /* Set low byte of divisor */
	outb(0x40, (divisor >> 8) & 0xFF);     /* Set high byte of divisor */
}

void timer_handler(struct regs *r)
{
    /* Increment our 'tick count' */
	timer_ticks++;

	print_d("%s %d\n","tick - ",timer_ticks);
}

/* Sets up the system clock by installing the timer handler
*  into IRQ0 */
void timer_install()
{
    /* Installs 'timer_handler' to IRQ0 */
    irq_install_handler(0, &timer_handler);
    set_timer_phase(freq);

    print_d("Timer Installed...\n");
}
