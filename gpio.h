#ifndef _GPIO_H_
#define _GPIO_H_

/*GPIO address*/
#define GPIO 0x01C20800
/*Port I Configure Register 0 offset
 * Responsible of Port I0 to Port I7 - 120*/
#define PI_CFG0 0x120
#define GPIO_CFG0 GPIO + PI_CFG0
/*Port I Configure Register 1 offset
 * Responsible of Port I8 to Port I15 - 124*/
#define PI_CFG1 0x124
#define GPIO_CFG1 GPIO + PI_CFG1
/*Position of the first bit of PI0*/
#define PI0 0
/*Position of the first bit of PI1*/
#define PI1 4
/*Position of the first bit of PI2*/
#define PI2 8
/*Position of the first bit of PI3*/
#define PI3 12
/*Position of the first bit of PI10*/
#define PI10 8
/*Position of the first bit of PI11*/
#define PI11 12
/* Port I Data Register offset - 0x130*/
#define PI_DAT 0x130
#define GPIO_DAT GPIO + PI_DAT

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
int gpio_read(void);
#endif
