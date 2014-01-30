#include "gpio.h"
#include "console.h"
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
    //unsigned int tmp;
    switch(pin)
    {
	case 9:
	    //tmp = *gpio_cfg0;
	    //tmp |= (1 << PI0);
	    //*gpio_cfg0 = tmp;
	    *gpio_cfg0 |= (1 << PI0);
	    //*gpio_cfg1 = 0x11111111;
	    //console_print_hexa(*gpio_cfg0);
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
    //unsigned int tmp;
    switch(pin)
    {
	case 9:
	    //tmp = *gpio_dat;
	    //tmp = 0xffffffff;
	    *gpio_dat |= (1 << 0);
	    //console_print_hexa(tmp);
	    //console_print("\r\nbob=");
	    //console_print_hexa(*gpio_dat);
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

int gpio_read(void)
{
    return *gpio_dat;    
}
