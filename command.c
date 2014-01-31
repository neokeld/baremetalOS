#include "command.h"
#include "console.h"
#include "led.h"
#include "gpio.h"
#include "memory.h"

struct cmd led_cmd;
struct cmd gpio_cmd;
struct cmd reg_cmd;

void cmd_init(void)
{
    led_cmd.name = "led";
    led_cmd.desc = "led [options]\r\n-- Turn on/off the LED1.\r\n-- Options:\r\n---- 1: turn on the LED1\r\n---- 0: turn off the LED1";
    led_cmd.nb_arg = 1;
    led_cmd.func = led_func;

    gpio_cmd.name = "gpio";
    gpio_cmd.desc = "Set the pin n on the GPIO-2.";
    gpio_cmd.nb_arg = 1;
    gpio_cmd.args[0].name = "Pin number";
    gpio_cmd.func = gpio_func;

    reg_cmd.name = "reg";
    reg_cmd.desc = "Print sp, lr and pc registers state.";
    reg_cmd.nb_arg = 0;
    reg_cmd.func = reg_func;
}

void cmd_print_usage(struct cmd cmd_struct)
{
    console_print("Usage :\r\n");
    console_print("-- ");
    console_print(cmd_struct.name);
    console_print("\r\n");
    console_print("-- ");
    console_print(cmd_struct.desc);
    console_print("\r\n");
}

void cmd_parse(char * str)
{
    int name_len, nb_args;
    name_len=0;
    char cmd_name[MAX_LEN_NAME];
    nb_args=0;
    const char * cmd_args[MAX_NB_ARGS];
    char * current_arg;
    while(*str && *str != ' ')
    {
	cmd_name[name_len] = *str;
	name_len++;
	str++;
    }
    cmd_name[name_len] = '\0';
    while(*str == ' ')
	str++;
    current_arg = str;
    while(*str)
    {
	if(*str == ' ')
	{
	    *str = '\0';
	    cmd_args[nb_args] = current_arg;
	    nb_args++;
	    while(*str == ' ')
		str++;
	    current_arg = str;
	}
	str++;
    }
    if(*str != ' ')
    {
	cmd_args[nb_args] = current_arg;
        nb_args++;
    }
    if (console_streq(cmd_name, led_cmd.name))
    {
	if(led_cmd.func(cmd_args, nb_args) == -1)
	    cmd_print_usage(led_cmd);
	console_prompt();
    }
    else if (console_streq(cmd_name, gpio_cmd.name))
    {
	if(gpio_cmd.func(cmd_args, nb_args) == -1)
	    cmd_print_usage(gpio_cmd);
	console_prompt();
    }
    else if (console_streq(cmd_name, reg_cmd.name))
    {
	if(reg_cmd.func(cmd_args, nb_args) == -1)
	    cmd_print_usage(reg_cmd);
	console_prompt();
    }
    else
    {
	console_print("Unknown command : ");
	console_print(cmd_name);
	console_print("\r\n");
	console_prompt();
    }

}
