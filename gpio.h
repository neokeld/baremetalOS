#ifndef _GPIO_H_
#define _GPIO_H_

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

/*Set a pin to act as an output
* Can set the pin 9, 11, 13, 15, 17 and 19 of GPIO-2*/
void gpio_input_set(int pin);
/*Set a pin to act as an output*/
void gpio_output_set(int pin);
/*Change the pin state to 3.3V*/
void gpio_activate(int pin);
/*Change the pin state to 0V*/
void gpio_desactivate(int pin);
/*Read the pin state
 * 1: activated
 * 0: desactivated
 * -1: Error: not a pin*/
int gpio_is_activated(int pin);
/*Read gpio dat*/
int gpio_read(void);
/*Parsing function for the gpio command
 * Return :
 * 0: Ok
 * -1: Error*/
int gpio_func(const char * args[], int nb_args);

#endif
