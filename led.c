#include "led.h"
#include "console.h"
#include "utils.h"

volatile unsigned int * led;
volatile unsigned int * led_cfg0;
volatile unsigned int * led_dat;

char led_cfg_value;
char led_dat_value;

void led_init(void)
{
    led_cfg0 = (unsigned int *)(LED_CFG0);
    led_dat = (unsigned int *)(LED_DAT);
    led_cfg_value = 1;
    led_dat_value = 1;
}

void led_cfg_set(char value)
{
    unsigned int tmp;
    tmp = *led_cfg0;
    if(value)
	tmp |= (1 << PH2);
    else
	tmp &= ~(1 << PH2);
    *led_cfg0 = tmp;
    led_cfg_value = value;
}

void led_dat_set(char value)
{
    unsigned int tmp;
    tmp = *led_dat;
    if(value)
	tmp |= (1 << PH2_DATA);
    else
	tmp &= ~(1 << PH2_DATA);
    *led_dat = tmp;
    led_dat_value = value;
}

char led_cfg_get_state(void)
{
    return led_cfg_value;
}

char led_dat_get_state(void)
{
    return led_dat_value;
}

int led_func(const char * args[], int nb_args)
{
	int arg_value;
	led_cfg_set(1);
	if(nb_args == 0)
	{
	    led_dat_set(!led_dat_get_state());
	}
	else if (nb_args == 1)
	{
	    arg_value = atoi(args[0]);
	    if(arg_value == 1 || arg_value == 0)
		led_dat_set(arg_value);
	    else
	    {
		console_print("Bad argument : Not 0 or 1.\r\n");
		return -1;
	    }
	}
	else
	{
	    console_print("Bad number of arguments\r\n");
	    return -1;
	}
        return 0;
}
