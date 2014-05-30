#include "led.h"
#include "console.h"
#include "utils.h"
#include "gpio.h"

#define LED_GPIO 3
#define LED_PIN 7

char led_cfg_value;

void led_cfg_set(char value)
{
    if(value)
	gpio_output_set(LED_GPIO, LED_PIN);
    else
	gpio_input_set(LED_GPIO, LED_PIN);

    led_cfg_value = value;
}

void led_dat_set(char value)
{
    if(value)
	gpio_activate(LED_GPIO, LED_PIN);
    else
	gpio_deactivate(LED_GPIO, LED_PIN);
}

char led_cfg_get_state(void)
{
    return led_cfg_value;
}

char led_dat_get_state(void)
{
    return gpio_is_activated(LED_GPIO, LED_PIN);
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
