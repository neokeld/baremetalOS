#include "uart.h"
#include "console.h"

void console_main(void)
{
    int i = uart_getc();
    if(i != -1)
    {
	if(i == 13)
	{
	    //uart_putc(10);
	    console_print("\r\n");
	    console_prompt();
	}
	else
	    uart_putc((char)i);
    }

}

void console_print(char * str)
{
    while (*str)
	uart_putc(*(str++));
}

void console_prompt(void)
{
    console_print("bOS> ");
}

void console_print_hexa(char c)
{
    char out[5];
    int i,p;
    out[0] = '0';
    out[1] = 'x';
    for (i=0, p=3; i<2; i++, p--)
    {
	if(c%16 <10)
	    out[p] = c%16 + 48;
	else
	    out[p] = c%16 + 55;
	c /= 16;
    }
    out[4] = '\0';
    console_print(out);
}
