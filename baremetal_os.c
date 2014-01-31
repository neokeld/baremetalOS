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
	/*volatile unsigned int * gpio;
	volatile unsigned int * gpio_cfg0;
	volatile unsigned int * gpio_cfg1;
	volatile unsigned int * gpio_dat;
	gpio = (unsigned int*) GPIO;
	gpio_cfg0 = (unsigned int *)(gpio + PI_CFG0);
	gpio_cfg1 = (unsigned int *)(gpio + PI_CFG1);
	gpio_dat = (unsigned int *)(gpio + PI_DAT);
*/


	uart_init();
	console_print("\r\n");
	console_init();

	console_print("\r\n");


	led_init();


	gpio_init();

	cmd_init();
	
        //gpio_output_set(9);

/*gpio_output_set(11);
	gpio_input_set(13);
	gpio_input_set(15);*/
        //gpio_activate(9);
	/*gpio_activate(13);
	gpio_activate(17);
	gpio_activate(19);*/

	/*console_print_hexa((char) *gpio); console_print("--");
	console_print_hexa((char) *gpio_cfg0); console_print("--");
	console_print_hexa((char) *gpio_cfg1); console_print("--");
	console_print_hexa((char) *gpio_dat); console_print("--");*/

	console_print("\r\n");

	//led_cfg_set(0);
	//led_dat_set(1);

      	console_prompt();

	while(1)
	{
	    //console_print_hexa(gpio_read());
	    console_main();
	}

	return 0;
}
