#include "uart.h"

volatile int * uart;
volatile int * uart_lsr;

void uart_init(void)
{
    uart = (int*) UART0;
    *(uart + FCR) = 0x0;
    uart_lsr = (int *)(uart + LSR);	
}

void uart_putc(char c)
{
    while(!((*uart_lsr) & THRE));
    *uart = c;
}

int uart_getc(void)
{
    if(((*uart_lsr) & DR) > 0)
    {
	return *uart;
    }
    else
	return -1;
}
