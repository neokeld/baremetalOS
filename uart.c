#include "uart.h"

#define UART0 0x01C28000
#define LSR 5
#define DR 0x1
#define FCR (1 << 1)
#define THRE (1 << 5)

int i;
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
