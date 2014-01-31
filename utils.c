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

