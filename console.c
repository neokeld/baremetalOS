#include "uart.h"
#include "console.h"
#include "led.h"

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
		  mode = HEXA;
		else if (console_streq(cmd, "led"))
		{
		  led_cfg_set(1);
		  led_dat_set(!led_dat_get_state());
		  console_prompt();
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
  //Affiche l'état des registres

  register unsigned int R13 asm("sp");
  register unsigned int R14 asm("lr");
  register unsigned int R15 asm("pc");


  console_print("r13 (sp) = ");
  console_print_hexa("SP");
  console_print("\r\n");

  console_print("r14 (lr) = ");
  console_print_hexa("LR");
  console_print("\r\n");
  
  console_print("r15 (pc) = ");
  console_print_hexa("PC");
  console_print("\r\n");
}


int console_streq(char * str, char* str2)
{
    while (*str && *str2)
    {
	if(*(str++) != *(str2++))
	    return 0;	    
    }
    return *str == *str2;
}
