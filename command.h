#ifndef _COMMAND_H_
#define _COMMAND_H_

#define MAX_ARGS 2
#define MAX_LEN_NAME 16
#define MAX_NB_ARGS 16

struct arg {
  char * name;
};

struct cmd {
  char * name;
  char * desc;
  int nb_arg;
  struct arg args[MAX_ARGS];
  int (*func)(const char * args[], int nb_args);
};

/*Initialize the command module*/
void cmd_init(void);
/*Print usage of a command*/
void cmd_print_usage(const struct cmd cmd_struct);
/*Print all usages*/
void cmd_print_all_usages(void);
/*Parse and execute the command str*/
void cmd_parse(char * str);
/*Test if a string is a command*/
int cmd_is_cmd(const char * str);
/*Get command struct corresponding to a string*/
const struct cmd * cmd_get_struct_cmd(const char * str);

#endif
