/*
 * (C) Copyright 2000
 * Wolfgang Denk, DENX Software Engineering, wd@denx.de.
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#define UART0 0x01C28000
#define LSR 5
#define DR 0x1
#define FCR 2

int hello_world (int argc, char * const argv[])
{
	/* **THE TEST** */
	int i;
	volatile int * uart;
	volatile int * uart_lsr;
	uart = (int*) UART0;

	*(uart + FCR) = 0x0;
	uart_lsr = (int *)(uart + LSR);
	
	while(1)
	{
		//printf("%x = ", *(int *)(uart + LSR) & DR);
		if(((*uart_lsr) & DR) > 0)
		{

		i = *uart;
		*uart = i;
		
		}
	}

	return 0;
}
