#ifndef _UART_H_
#define _UART_H_

/*UART0 address*/
#define UART0 0x01C28000
/*UART0's FIFO Control Register Offset*/
#define FCR (1 << 1)
/*UART0's Line Status Register offset*/
#define LSR 5
/*Data Ready Bit : First bit in LSR*/
#define DR 0x1
/*TX Holding Register Empty Bit : Sixth bit in LSR*/
#define THRE (1 << 5)

/*Initialize UART0 useful registers*/
void uart_init(void);
/*Put c in UART0 when it's ready*/
void uart_putc(char c);
/*Get sent char to UART0*/
int uart_getc(void);

#endif
