#include <sys/serial.h>
#include <sys/io.h>
#include <misc/text.h>
#include <lib/printk.h>

static const int S_PORT = 0x3F8; /*Com1*/

void init_serial()
{
	outb(S_PORT + 1, 0x00);    // Disable all interrupts
	outb(S_PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outb(S_PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outb(S_PORT + 1, 0x00);    //                  (hi byte)
	outb(S_PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outb(S_PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outb(S_PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set

	//write(SERIAL_SUCCESS,SERIAL_SUCCESS_SIZE*sizeof(char));
	print_k("%s\n",SERIAL_SUCCESS);
}

int serial_received() {
	return inb(S_PORT + 5) & 1;
}
 
char read_serial() {
	while (serial_received() == 0);
	return inb(S_PORT);
}

int is_transmit_empty() {
	return inb(S_PORT + 5) & 0x20;
}

void write_serial(char a) {
	while (is_transmit_empty() == 0);
		outb(S_PORT,a);
}