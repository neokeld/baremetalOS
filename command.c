#include "command.h"
#include "console.h"
#include "led.h"
#include "gpio.h"
#include "memory.h"
#include "utils.h"

struct cmd led_cmd;
struct cmd gpio_cmd;
struct cmd reg_cmd;
struct cmd help_cmd;

int cmd_help_func(const char * args[], int nb_args);

void cmd_init(void)
{
    led_cmd.name = "led";
    led_cmd.desc = "led [options]\r\n-- Turn on/off the LED1.\r\n-- Options:\r\n---- 1: turn on the LED1\r\n---- 0: turn off the LED1";
    led_cmd.nb_arg = 1;
    led_cmd.func = led_func;

    gpio_cmd.name = "gpio";
    gpio_cmd.desc = "Set/Unset the pin n on the GPIO-2.";
    gpio_cmd.nb_arg = 1;
    gpio_cmd.args[0].name = "Pin number";
    gpio_cmd.func = gpio_func;

    reg_cmd.name = "reg";
    reg_cmd.desc = "Print sp, lr and pc registers state.";
    reg_cmd.nb_arg = 0;
    reg_cmd.func = reg_func;

    help_cmd.name = "help";
    help_cmd.desc = "bOS, version 0.0.1\r\nList of the commands:\r\n";
    help_cmd.nb_arg = 0;
    help_cmd.func = cmd_help_func;
}

void cmd_print_usage(const struct cmd cmd_struct)
{
    console_print("Usage :\r\n");
    console_print("-- ");
    console_print(cmd_struct.name);
    console_print("\r\n");
    console_print("-- ");
    console_print(cmd_struct.desc);
    console_print("\r\n");
}

void cmd_print_all_usages(void)
{
    cmd_print_usage(led_cmd);
    cmd_print_usage(gpio_cmd);
    cmd_print_usage(reg_cmd);
    cmd_print_usage(help_cmd);
}

void cmd_parse(char * str)
{
    int name_len, nb_args;
    name_len=0;
    char cmd_name[MAX_LEN_NAME];
    nb_args=0;
    const char * cmd_args[MAX_NB_ARGS];
    char * current_arg;
    while(*str && *str != ' ' && *str != '\0')
    {
	cmd_name[name_len] = *str;
	name_len++;
	str++;
    }
    *str = '\0';
    cmd_name[name_len] = '\0';
    str++;
    while(*str == ' ')
	str++;
    if(*str != '\0')
    {
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
    }
    /*TODO : use cmd_get_struct_cmd*/
    if (streq(cmd_name, led_cmd.name))
    {
	if(led_cmd.func(cmd_args, nb_args) == -1)
	    cmd_print_usage(led_cmd);
	console_prompt();
    }
    else if (streq(cmd_name, gpio_cmd.name))
    {
	if(gpio_cmd.func(cmd_args, nb_args) == -1)
	    cmd_print_usage(gpio_cmd);
	console_prompt();
    }
    else if (streq(cmd_name, reg_cmd.name))
    {
	if(reg_cmd.func(cmd_args, nb_args) == -1)
	    cmd_print_usage(reg_cmd);
	console_prompt();
    }
    else if (streq(cmd_name, help_cmd.name))
    {
	if(help_cmd.func(cmd_args, nb_args) == -1)
	    cmd_print_usage(help_cmd);
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

int cmd_is_cmd(const char * str)
{
    return streq(led_cmd.name,  str)
	|| streq(gpio_cmd.name, str)
	|| streq(reg_cmd.name,  str)
	|| streq(help_cmd.name, str);
}

const struct cmd * cmd_get_struct_cmd(const char * str)
{
    if(streq(led_cmd.name, str))
	return &led_cmd;	
    else if(streq(gpio_cmd.name, str))
	return &gpio_cmd;
    else if (streq(reg_cmd.name,  str))
	return &reg_cmd;
    else if (streq(help_cmd.name, str))
	return &help_cmd;
    else
	return NULL;
}

int cmd_help_func(const char * args[], int nb_args)
{
    if(nb_args == 0)
    {
	cmd_print_all_usages();
	return 0;
    }
    else if (nb_args == 1)
    {
	if(cmd_is_cmd(args[0]))
	{
	    const struct cmd * cmd_struct = cmd_get_struct_cmd(args[0]);
	    cmd_print_usage(*cmd_struct);
	    return 0;
	}
	else
	{
	    console_print("Bad argument : Not a command.\r\n");
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
