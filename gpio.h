#ifndef _GPIO_H_
#define _GPIO_H_

/*GPIO address*/
#define GPIO 0x01C20800
/*Port I Configure Register 0 offset
 * Responsible of Port I0 to Port I7*/
#define PI_CFG0 0x120
/*Port I Configure Register 1 offset
 * Responsible of Port I8 to Port I15*/
#define PI_CFG1 0x124
/*Position of the first bit of PI0*/
#define PI0 0x0
/*Position of the first bit of PI1*/
#define PI1 0x4
/*Position of the first bit of PI2*/
#define PI2 0x8
/*Position of the first bit of PI3*/
#define PI3 0x12
/*Position of the first bit of PI10*/
#define PI10 0x8
/*Position of the first bit of PI11*/
#define PI11 0x12
/* Port I Data Register offset*/
#define PI_DAT 0x130

/*Initialize GPIO useful registers*/
void gpio_init(void);
/*Set a pin to act as an output
* Can set the pin 9, 11, 13, 15, 17 and 19 of GPIO-2*/
void gpio_input_set(int pin);
/*Set a pin to act as an output*/
void gpio_output_set(int pin);
/*Change the pin state to 3.3V*/
void gpio_activate(int pin);
/*Change the pin state to 0V*/
void gpio_desactivate(int pin);

#endif
