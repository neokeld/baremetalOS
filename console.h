#ifndef _CONSOLE_H_
#define _CONSOLE_H_

void console_init(void);

void console_main(void);

void console_print(char * str);

void console_prompt(void);

void console_print_hexa(char c);

int console_streq(char* str, char* str2);

#endif
