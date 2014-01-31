#include "command.h"
#include "console.h"
#include "led.h"
#include "gpio.h"

struct cmd led_cmd;
struct cmd gpio_cmd;

void cmd_init(void)
{
    led_cmd.name = "led";
    led_cmd.desc = "led [options]\r\n-- Turn on/off the LED1.\r\n-- Options:\r\n---- 1: turn on the LED1\r\n---- 0: turn off the LED1";
    led_cmd.nb_arg = 0;
    led_cmd.func = led_func;

    gpio_cmd.name = "gpio";
    gpio_cmd.desc = "Set the pin n on the GPIO-2.";
    gpio_cmd.nb_arg = 1;
    gpio_cmd.args[0].name = "Pin number";
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

void cmd_parse(const char * str)
{
   int name_len, arg_len, nb_args;
   name_len=0;
   char cmd_name[MAX_LEN_NAME];
   arg_len=0;
   char cmd_arg[MAX_LEN_ARG];
   nb_args=0;
   while(*str && *str != ' ')
   {
	cmd_name[name_len] = *str;
	name_len++;
        str++;
   }
   cmd_name[name_len] = '\0';
   while(*str && *str == ' ')
        str++;
   while(*str && *str != ' ')
   {
        cmd_arg[arg_len] = *str;
	arg_len++;
	str++;
   }
   cmd_arg[arg_len] = '\0';
   if(arg_len != 0)
       nb_args = 1;
   if (console_streq(cmd_name, led_cmd.name))
   {
	if(led_cmd.func(cmd_arg, nb_args) == -1)
	    cmd_print_usage(led_cmd);
        console_prompt();
   }
   else if (console_streq(cmd_name, gpio_cmd.name))
   {
        gpio_output_set(9);
        gpio_activate(9);
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
