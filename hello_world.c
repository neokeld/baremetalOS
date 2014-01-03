/*
 * (C) Copyright 2013-2014
 * Mathias Brulatout
 * Arnaud Duforat
 * Louis Lévèque
 *
 * WTF License 2.0
 * Do whatever the f*** you want with the content, EXCEPT claim it as your own work.
 */

#include "uart.h"

int hello_world (int argc, char * const argv[])
{

	uart_init();

	while(1)
	{
	    int i = uart_getc();
	    if(i != -1)
	    {
		uart_putc((char)i);
	    }
	}

	return 0;
}
