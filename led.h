#ifndef _LED_H_
#define _LED_H_

/*Set LED register to act as an output
 * 1: output
 * 0: input*/
void led_cfg_set(char value);
/*Change the pin state to 0 or 3.3V
 * 1: 3.3V
 * 0: 0 V*/
void led_dat_set(char value);
/*Read LED cfg state
 * 1: output
 * 0: input */
char led_cfg_get_state(void);
/*Read LED dat state
 * 1: 3.3V
 * 0: 0 V*/
char led_dat_get_state(void);

/*Parsing function for the led command
 * Return :
 * 0: Ok
 * -1: Error*/
int led_func(const char * args[], int nb_args);

#endif
