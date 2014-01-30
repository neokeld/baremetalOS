#include "led.h"
#include "console.h"
volatile unsigned int * led;
volatile unsigned int * led_cfg0;
volatile unsigned int * led_dat;

char led_cfg_value;
char led_dat_value;

void led_init(void)
{
    led_cfg0 = (unsigned int *)(LED_CFG0);
    led_dat = (unsigned int *)(LED_DAT);
    led_cfg_value = 1;
    led_dat_value = 1;
}

void led_cfg_set(char value)
{
    //console_print_hexa(*led_cfg0);
    //console_print("\r\n");

    unsigned int tmp;
    tmp = *led_cfg0;
    if(value)
	tmp |= (1 << PH2);
    else
	tmp &= ~(1 << PH2);
    *led_cfg0 = tmp;
    /*console_print("led cfg set ");
    console_print_hexa(*led_cfg0);
    console_print(" \r\n");
    console_print_hexa(tmp);*/
    led_cfg_value = value;
}

void led_dat_set(char value)
{
    //console_print_hexa(*led_dat);
    //console_print("\r\n");

    unsigned int tmp;
    tmp = *led_dat;
    if(value)
	tmp |= (1 << PH2_DATA);
    else
	tmp &= ~(1 << PH2_DATA);
    *led_dat = tmp;
    //console_print("led dat ");
    //console_print_hexa(*led_dat);
    //console_print(" \r\n");
    //console_print_hexa(tmp);
    led_dat_value = value;
}

char led_cfg_get_state(void)
{
    return led_cfg_value;
}

char led_dat_get_state(void)
{
    return led_dat_value;
}
