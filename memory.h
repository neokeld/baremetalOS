#ifndef CONSOLE_H
#define CONSOLE_H
#include "console.h"

#define NULL ((void *) 0)

typedef unsigned int size_t;

struct memblock{
  volatile void* addr;
  size_t size;
  struct memblock* next;
};

void memtest(void);
void *malloc(size_t size);

#endif
