#ifndef CONSOLE_H
#define CONSOLE_H
#include "console.h"

#define NULL ((void *) 0)

typedef unsigned int size_t;

struct memblock{
  void* addr;
  struct memblock* prev;
  struct memblock* next;
};

void memtest(void);
void *malloc(size_t size);
void free(void *ptr);
int reg_func(const char * args[], int nb_args);

#endif
