#include "gpio.h"
#include "console.h"
#include "utils.h"
#define GPIO2_PIN_MAP_SIZE 34

volatile unsigned int * gpio_cfg;
volatile unsigned int * gpio_dat;

int gpio_init(int);

int gpio2_pin_map[GPIO2_PIN_MAP_SIZE][2] = {
		      {-1,-1}, /* pin 0 : doesn't exist */
		      {-1,-1}, /* pin 1 */
		      {-1,-1},
                      {-1,-1},
                      {-1,-1},
		      {-1,-1},
		      {-1,-1},
		      {-1,-1},
		      {-1,-1},
		      {PI, 0}, /* pin 9 */
		      {-1,-1},
		      {PI, 1}, /* pin 11 */
		      {-1,-1},
		      {PI, 2}, /* pin 13 */
		      {-1,-1},
		      {PI, 3}, /* pin 15 */
		      {-1,-1},
		      {PI,10}, /* pin 17 */
		      {-1,-1},
		      {PI,11}, /* pin 19 */
		      {-1,-1},
		      {PC,3}, /* pin 21 */
		      {-1,-1},
		      {PC,7}, /* pin 23 */
		      {-1,-1},
		      {PC,16}, /* pin 25 */
		      {-1,-1},
		      {PC,17}, /* pin 27 */
		      {-1,-1},
		      {PC,18}, /* pin 29 */
		      {-1,-1},
		      {PC,23}, /* pin 31 */
		      {-1,-1},
		      {PC,24}  /* pin 33 */
		    };

int gpio_init(int pin)
{
    if(pin >= GPIO2_PIN_MAP_SIZE) {
	return -1;
    }
    else {
	int pio_name = gpio2_pin_map[pin][0];
	int pio_number = gpio2_pin_map[pin][1];
	if (pio_name == -1) {
	    return -2;
	}
	else {
	    gpio_cfg = (unsigned int *)(P_CFG(pio_name, pio_number / 8));
	    gpio_dat = (unsigned int *)(P_DAT(pio_name));
	    return 0;
	}
    }
}

void gpio_output_set(int pin)
{
    int pio_number = gpio2_pin_map[pin][1];
    if(gpio_init(pin) == 0)
	*gpio_cfg |= (1 << PIO_FIRST_BIT(pio_number));
	    
}

void gpio_input_set(int pin)
{
    int pio_number = gpio2_pin_map[pin][1];
    if(gpio_init(pin) == 0)
	*gpio_cfg &= ~(1 << PIO_FIRST_BIT(pio_number));
}

void gpio_activate(int pin)
{
    int pio_number = gpio2_pin_map[pin][1];
    if(gpio_init(pin) == 0)
	*gpio_dat |= (1 << pio_number);
}

void gpio_desactivate(int pin)
{
    int pio_number = gpio2_pin_map[pin][1];
    if(gpio_init(pin) == 0)
	*gpio_dat &= ~(1 << pio_number);
}

int gpio_is_activated(int pin)
{
    int pio_number = gpio2_pin_map[pin][1];
    if(gpio_init(pin) == 0)
	return (*gpio_dat >> pio_number) & 1;
    else
	return -1;
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
	    if(gpio2_pin_map[arg_value][0] != -1)
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
