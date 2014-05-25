#include "gpio.h"
#include "console.h"
#include "utils.h"

volatile unsigned int * gpio_cfg0;
volatile unsigned int * gpio_cfg1;
volatile unsigned int * gpio_dat;

void gpio_init(void)
{
    gpio_cfg0 = (unsigned int *)(GPIO_CFG0);
    gpio_cfg1 = (unsigned int *)(GPIO_CFG1);
    gpio_dat = (unsigned int *)(GPIO_DAT);
}

void gpio_output_set(int pin)
{
    switch(pin)
    {
	case 9:
	    *gpio_cfg0 |= (1 << PI0);
	    break;
	case 11:
	    *gpio_cfg0 |= (1 << PI1);
	    break;
	case 13:
	    *gpio_cfg0 |= (1 << PI2);
	    break;
	case 15:
	    *gpio_cfg0 |= (1 << PI3);
	    break;
	case 17:
	    *gpio_cfg1 |= (1 << PI10);
	    break;
	case 19:
	    *gpio_cfg1 |= (1 << PI11);
	    break;
	default:
	    break;
    }
}

void gpio_input_set(int pin)
{
    switch(pin)
    {
	case 9:
	    *gpio_cfg0 &= ~(1 << PI0);
	    break;
	case 11:
	    *gpio_cfg0 &= ~(1 << PI1);
	    break;
	case 13:
	    *gpio_cfg0 &= ~(1 << PI2);
	    break;
	case 15:
	    *gpio_cfg0 &= ~(1 << PI3);
	    break;
	case 17:
	    *gpio_cfg1 &= ~(1 << PI10);
	    break;
	case 19:
	    *gpio_cfg1 &= ~(1 << PI11);
	    break;
	default:
	    break;
    }
}

void gpio_activate(int pin)
{
    switch(pin)
    {
	case 9:
	    *gpio_dat |= (1 << 0);
	    break;
	case 11:
	    *gpio_dat |= (1 << 1);
	    break;
	case 13:
	    *gpio_dat |= (1 << 2);
	    break;
	case 15:
	    *gpio_dat |= (1 << 3);
	    break;
	case 17:
	    *gpio_dat |= (1 << 10);
	    break;
	case 19:
	    *gpio_dat |= (1 << 11);
	    break;
	default:
	    break;
    }
}

void gpio_desactivate(int pin)
{
    switch(pin)
    {
	case 9:
	    *gpio_dat &= ~(1 << 0);
	    break;
	case 11:
	    *gpio_dat &= ~(1 << 1);
	    break;
	case 13:
	    *gpio_dat &= ~(1 << 2);
	    break;
	case 15:
	    *gpio_dat &= ~(1 << 3);
	    break;
	case 17:
	    *gpio_dat &= ~(1 << 10);
	    break;
	case 19:
	    *gpio_dat &= ~(1 << 11);
	    break;
	default:
	    break;
    }
}

int gpio_is_activated(int pin)
{
     switch(pin)
    {
	case 9:
	    return (*gpio_dat >> 0) & 1;
	    break;
	case 11:
	    return (*gpio_dat >> 1) & 1;
	    break;
	case 13:
	    return (*gpio_dat >> 2) & 1;
	    break;
	case 15:
	    return (*gpio_dat >> 3) & 1;
	    break;
	case 17:
	    return (*gpio_dat >> 10) & 1;
	    break;
	case 19:
	    return (*gpio_dat >> 11) & 1;
	    break;
	default:
	    return -1;
	    break;
    } 
}

int gpio_read(void)
{
    return *gpio_dat;    
}

int gpio_func(const char * args[], int nb_args)
{
	int arg_value;
	if(nb_args == 0)
	{
	    gpio_output_set(9);
	    gpio_activate(9);
	}
	else if (nb_args == 1)
	{
	    arg_value = atoi(args[0]);
	    if(arg_value == 9 || arg_value == 11 || arg_value == 13 || arg_value == 15 || arg_value == 17 || arg_value == 19)
	    {
		if(gpio_is_activated(arg_value))
		{
		    gpio_output_set(arg_value);
		    gpio_desactivate(arg_value);
		}
		else
		{
		    gpio_output_set(arg_value);
		    gpio_activate(arg_value);
		}
	    }
	    else
	    {
		console_print("Bad argument : Not a pin number.\r\n");
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
