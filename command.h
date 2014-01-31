#ifndef _COMMAND_H_
#define _COMMAND_H_

#define MAX_ARGS 1
#define MAX_LEN_NAME 16
#define MAX_LEN_ARG 16

struct arg {
    char * name;
};

struct cmd {
    char * name;
    char * desc;
    int nb_arg;
    struct arg args[MAX_ARGS];
};

int atoi(const char * str);
void cmd_init(void);
void cmd_parse(const char * str);

#endif
