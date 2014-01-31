#ifndef _COMMAND_H_
#define _COMMAND_H_

#define MAX_ARGS 1
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

int atoi(const char * str);
void cmd_init(void);
void cmd_parse(char * str);

#endif
