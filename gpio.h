#ifndef _GPIO_H_
#define _GPIO_H_

/*Set a pin to act as an output
* Can set the pins of GPIO-2 and GPIO-3*/
void gpio_input_set(const int gpio, const int pin);
/*Set a pin to act as an output*/
void gpio_output_set(const int gpio, const int pin);
/*Change the pin state to 3.3V*/
void gpio_activate(const int gpio, const int pin);
/*Change the pin state to 0V*/
void gpio_deactivate(const int gpio, const int pin);
/*Read the pin state
 * 1: activated
 * 0: deactivated
 * -1: Error: not a pin*/
int gpio_is_activated(const int gpio, const int pin);
/*Read gpio dat*/
int gpio_read(void);
/*Parsing function for the gpio command
 * Return :
 * 0: Ok
 * -1: Error*/
int gpio_func(const char * args[], int nb_args);

#endif
