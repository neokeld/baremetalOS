#include "utils.h"

int atoi(const char * str)
{
   int i;
   i=0;
   while(*str)
   {
      i = (i<<3) + (i<<1) + (*str - '0');
      str++;
   }
   return i;
}

int streq(const char * str, const char* str2)
{
    while (*str && *str2)
    {
	if(*(str++) != *(str2++))
	    return 0;	    
    }
    return *str == *str2;
}
