#ifndef __SERIAL_H
#define __SERIAL_H

void init_serial();

int serial_received();
char read_serial();
int is_transmit_empty();
void write_serial(char a);

#endif