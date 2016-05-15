#ifndef __SERIAL_H
#define __SERIAL_H

#define S_PORT 0x3f8 /*Com1*/

void init_serial_port();
int serial_received();
char read_serial();
int is_transmit_empty();
void write_serial(char a);

#endif