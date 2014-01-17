#ifndef _CONSOLE_H_
#define _CONSOLE_H_

/*Initialize console to default mode*/
void console_init(void);
/*Execute command when Enter is pressed*/
void console_main(void);
/*Print command*/
void console_print(char * str);
/*Print prompt*/
void console_prompt(void);
/*Print hexa code*/
void console_print_hexa(unsigned int c);
/*Returns 0 if str = str2, else 1*/
int console_streq(char* str, char* str2);

#endif
