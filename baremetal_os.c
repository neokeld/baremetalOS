/*
 * (C) Copyright 2013-2014
 * Mathias Brulatout
 * Arnaud Duforat
 * Kamal Mallouky
 * Louis Lévèque
 * Nicolas Sarlin
 *
 * WTF License 2.0
 * Do whatever the f*** you want with the content, EXCEPT claim it as your own work.
 */

#include "uart.h"
#include "gpio.h"
#include "console.h"
#include "led.h"
#include "memory.h"

/*Entry point*/
int baremetal_os (int argc, char * const argv[])
{
	uart_init();
	console_print("\r\n");
	console_init();

	console_print("\r\n");

	led_init();

	gpio_init();

	cmd_init();
	
	console_print("\r\n");

      	console_prompt();

	while(1)
	{
	    console_main();
	}

	return 0;
}
