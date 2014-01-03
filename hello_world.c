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
#include "console.h"

int hello_world (int argc, char * const argv[])
{

	uart_init();

	console_prompt();


	while(1)
	{
	    console_main();
	}

	return 0;
}
