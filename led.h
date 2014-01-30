#ifndef _LED_H_
#define _LED_H_

/*LED address*/
#define LED 0x01C20800
/*Port I Configure Register 0 offset
 * Responsible of Port H0*/
#define PH_CFG0 0xFC
#define LED_CFG0 (LED + PH_CFG0)
/*Position of the first bit of PH0*/
#define PH2 8
/* Port H Data Register offset*/
#define PH_DAT 0x10C
#define LED_DAT (LED + PH_DAT)
/*Position of the PH2 in the data register */
#define PH2_DATA 2

/*Initialize LED useful registers*/
void led_init(void);
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

#endif
