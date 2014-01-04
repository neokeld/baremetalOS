#include "gpio.h"

volatile int * gpio;
volatile int * gpio_cfg0;
volatile int * gpio_cfg1;
volatile int * gpio_dat;

void gpio_init(void)
{
    gpio = (int*) GPIO;
    gpio_cfg0 = (int *)(gpio + PI_CFG0);
    gpio_cfg1 = (int *)(gpio + PI_CFG1);
    gpio_dat = (int *)(gpio + PI_DAT);
}

void gpio_input_set(int pin)
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

void gpio_output_set(int pin)
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
