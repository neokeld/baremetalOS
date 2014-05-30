#include "gpio.h"
#include "console.h"
#include "utils.h"
#define GPIO2_PIN_MAP_SIZE 34
#define GPIO3_PIN_MAP_SIZE 41

/*PIO module base address*/
#define PIO 0x01C20800
/*Port n Configure Register p*/
#define P_CFG(n,p) (PIO + (n) * 0x24 + 0x04 *(p))
/* Port n Data Register*/
#define P_DAT(n) (PIO + (n) * 0x24 + 0x10)

#define PA 0
#define PB 1
#define PC 2
#define PD 3
#define PE 4
#define PF 5
#define PG 6
#define PH 7
#define PI 8

/*Position of the first bit of PIO
 * example of pio_number : in PA0, 0 is the pio_number*/
#define PIO_FIRST_BIT(pio_number) (((pio_number) % 8)*4)

volatile unsigned int * gpio_cfg;
volatile unsigned int * gpio_dat;

int gpio_init(int);

const int gpio2_pin_map[GPIO2_PIN_MAP_SIZE][2] = {
		      {-1,-1}, /* pin 0 : doesn't exist */
		      {-1,-1}, /* pin 1 */
		      {-1,-1},
		      {-1,-1},
		      {-1,-1},
		      {-1,-1},
		      {PE, 0},
		      {-1,-1},
		      {PE, 1},
		      {PI, 0}, /* pin 9 */
		      {PE, 2},
		      {PI, 1}, /* pin 11 */
		      {PE, 3},
		      {PI, 2}, /* pin 13 */
		      {PE, 4},
		      {PI, 3}, /* pin 15 */
		      {PE, 5},
		      {PI,10}, /* pin 17 */
		      {PE, 6},
		      {PI,11}, /* pin 19 */
		      {PE, 7},
		      {PC, 3}, /* pin 21 */
		      {PE, 8},
		      {PC, 7}, /* pin 23 */
		      {PE, 9},
		      {PC,16}, /* pin 25 */
		      {PE,10},
		      {PC,17}, /* pin 27 */
		      {PE,11},
		      {PC,18}, /* pin 29 */
		      {PI,14},
		      {PC,23}, /* pin 31 */
		      {PI,15},
		      {PC,24}  /* pin 33 */
		    };

const int gpio3_pin_map[GPIO3_PIN_MAP_SIZE][2] = {
		      {-1,-1}, /* pin 0 : doesn't exist */
		      {-1,-1}, /* pin 1 */
		      {-1,-1},
		      {-1,-1}, /* pin 3 */
		      {-1,-1},
		      {PH, 0}, /* pin 5 */
		      {PB, 3},
		      {PH, 2}, /* pin 7 */
		      {PB, 4},
		      {PH, 7}, /* pin 9 */
		      {PB, 5},
		      {PH, 9}, /* pin 11 */
		      {PB, 6},
		      {PH,10}, /* pin 13 */
		      {PB, 7},
		      {PH,11}, /* pin 15 */
		      {PB, 8},
		      {PH,12}, /* pin 17 */
		      {PB,10},
		      {PH,13}, /* pin 19 */
		      {PB,11},
		      {PH,14}, /* pin 21 */
		      {PB,12},
		      {PH,15}, /* pin 23 */
		      {PB,13},
		      {PH,16}, /* pin 25 */
		      {PB,14},
		      {PH,17}, /* pin 27 */
		      {PB,15},
		      {PH,18}, /* pin 29 */
		      {PB,16},
		      {PH,19}, /* pin 31 */
		      {PB,17},
		      {PH,20}, /* pin 33 */
		      {PH,24},
		      {PH,21}, /* pin 35 */
		      {PH,25},
		      {PH,22}, /* pin 37 */
		      {PH,26},
		      {PH,23}, /* pin 39 */
		      {PH,27}
		    };

int gpio_init_priv(const int gpio_pin_map[][2], const int pin)
{
    if(pin >= GPIO3_PIN_MAP_SIZE) {
	return -1;
    }
    else {
	int pio_name = gpio_pin_map[pin][0];
	int pio_number = gpio_pin_map[pin][1];
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

void gpio_output_set_priv(const int gpio_pin_map[][2], const int pin)
{
    int pio_number = gpio_pin_map[pin][1];
    if(gpio_init_priv(gpio_pin_map, pin) == 0)
	*gpio_cfg |= (1 << PIO_FIRST_BIT(pio_number));
	    
}

void gpio_input_set_priv(const int gpio_pin_map[][2], const int pin)
{
    int pio_number = gpio_pin_map[pin][1];
    if(gpio_init_priv(gpio_pin_map, pin) == 0)
	*gpio_cfg &= ~(1 << PIO_FIRST_BIT(pio_number));
}

void gpio_activate_priv(const int gpio_pin_map[][2], const int pin)
{
    int pio_number = gpio_pin_map[pin][1];
    if(gpio_init_priv(gpio_pin_map, pin) == 0)
	*gpio_dat |= (1 << pio_number);
}

void gpio_desactivate_priv(const int gpio_pin_map[][2], const int pin)
{
    int pio_number = gpio_pin_map[pin][1];
    if(gpio_init_priv(gpio_pin_map, pin) == 0)
	*gpio_dat &= ~(1 << pio_number);
}

int gpio_is_activated_priv(const int gpio_pin_map[][2], const int pin)
{
    int pio_number = gpio_pin_map[pin][1];
    if(gpio_init_priv(gpio_pin_map, pin) == 0)
	return (*gpio_dat >> pio_number) & 1;
    else
	return -1;
}

void gpio_input_set(const int gpio, const int pin)
{
    if(gpio == 2)
	gpio_input_set_priv(gpio2_pin_map, pin);
    else if(gpio == 3)
	gpio_input_set_priv(gpio3_pin_map, pin);
}
void gpio_output_set(const int gpio, const int pin)
{
    if(gpio == 2)
	gpio_output_set_priv(gpio2_pin_map, pin);
    else if(gpio == 3)
	gpio_output_set_priv(gpio3_pin_map, pin);
}
void gpio_activate(const int gpio, const int pin)
{
    if(gpio == 2)
	gpio_activate_priv(gpio2_pin_map, pin);
    else if(gpio == 3)
	gpio_activate_priv(gpio3_pin_map, pin);
}
void gpio_desactivate(const int gpio, const int pin)
{
    if(gpio == 2)
	gpio_desactivate_priv(gpio2_pin_map, pin);
    else if(gpio == 3)
	gpio_desactivate_priv(gpio3_pin_map, pin);
}
int gpio_is_activated(const int gpio, const int pin)
{
    if(gpio == 2)
	return gpio_is_activated_priv(gpio2_pin_map, pin);
    else if(gpio == 3)
	return gpio_is_activated_priv(gpio3_pin_map, pin);
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
	    gpio_output_set(2, 9); // TODO : gpio number arg
	    gpio_activate(2, 9);
	}
	else if (nb_args == 1)
	{
	    arg_value = atoi(args[0]);
	    if(arg_value > 0 && arg_value <= 40 && gpio2_pin_map[arg_value][0] != -1)
	    {
		if(gpio_is_activated(2, arg_value))
		{
		    gpio_output_set(2, arg_value);
		    gpio_desactivate(2, arg_value);
		}
		else
		{
		    gpio_output_set(2, arg_value);
		    gpio_activate(2, arg_value);
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
