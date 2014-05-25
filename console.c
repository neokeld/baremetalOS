#include "uart.h"
#include "console.h"
#include "command.h"
#include "utils.h"

static char buffer[128]; 
static int pos;
static enum mode_t {DEFAULT, HEXA, NB_MODES} mode;

static void console_run(char * cmd);

void console_init(void)
{
    pos = 0;
    mode = DEFAULT;
}

void console_main(void)
{
    int i = uart_getc();
    if(i != -1)
    {
	if(i == 13) // enter
	{
	    buffer[pos] = '\0';
	    console_run(buffer);
	}
	else
	{
	    buffer[pos++] = (char)i;
	    uart_putc((char)i);
	}
    }
}

static void console_run(char * cmd)
{
	console_print("\r\n");
	switch (mode)
	{
	    case DEFAULT:
		if(streq(cmd, "hexa"))
		  mode = HEXA;
		else {
		    cmd_parse(cmd);
		}
		break;
	    case HEXA:
		if(streq(cmd, "exit"))
		    mode = DEFAULT;
		else
		{
		    while (*cmd)
		    {
			console_print_hexa(*cmd++);
			console_print(" ");
		    }
		    console_print("\r\n");
		}
		if(mode == DEFAULT)
		    console_prompt();
		break;
	    default:
		break;
	}
    pos = 0;
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

void console_print_hexa(unsigned int c)
{
    char out[11];
    int i,p;
    out[0] = '0';
    out[1] = 'x';
    for (i=0, p=9; i<8; i++, p--)
    {
	if(c%16 <10)
	    out[p] = c%16 + 48;
	else
	    out[p] = c%16 + 55;
	c /= 16;
    }
    out[10] = '\0';
    console_print(out);
}

void console_print_registers(void){

    unsigned int spReg, lrReg, pcReg;

    asm volatile ("mov %0, sp" :
                "=r" (spReg));
    
    asm volatile ("mov %0, lr" :
                "=r" (lrReg));

    asm volatile ("mov %0, pc" :
                "=r" (pcReg));
    
  console_print("r13 (sp) = ");
  console_print_hexa(spReg);
  console_print("\r\n");

  console_print("r14 (lr) = ");
  console_print_hexa(lrReg);
  console_print("\r\n");
  
  console_print("r15 (pc) = ");
  console_print_hexa(pcReg);
  console_print("\r\n"); 
}

