#include "uart.h"
#include "console.h"

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
		if(console_streq(cmd, "hexa"))
		{
		    mode = HEXA;
		}
		else
		{
		    console_print("Unknown command : ");
		    console_print(cmd);
		    console_print("\r\n");
		    console_prompt();
		}
		break;
	    case HEXA:
		if(console_streq(cmd, "exit"))
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

/* Retourne 1 si str et str2 sont égales, 0 sinon */
int console_streq(char * str, char* str2)
{
    while (*str && *str2)
    {
	if(*(str++) != *(str2++))
	{
	    return 0;	    
	}
    }

    return *str == *str2;
}
