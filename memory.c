#include "memory.h"

#define BASE_ADDR 0

int memprobe(void){
  volatile unsigned int *mem;
  unsigned int memkb;
  unsigned int mem_count, a;
  unsigned int mem_start=0, mem_end=0;


  mem_count = BASE_ADDR;
  memkb = 0;

  do{
    memkb++;
    mem_count = memkb*1024*1024;
    console_print("mem_count :");
    console_print_hexa(mem_count);
    console_print("\r\n");
    mem = (unsigned int*)mem_count;

    a = *mem;
    *mem = 0x55AA55AA;

    //Test
    console_print("mem :");
    console_print_hexa((unsigned int)mem);
    console_print("\r\n");
    console_print("mem* :");
    console_print_hexa(*mem);
    console_print("\r\n");



    if(*mem != 0x55AA55AA)
      mem_count = 0;
    else{
      *mem=0xAA55AA55;
      if(*mem != 0xAA55AA55)
	mem_count = 0;
    }

    if(mem_count != 0 && mem_start == 0)
      mem_start = mem_count;
    if(mem_count == 0 && mem_start != 0)
      mem_end = memkb*1024*1024;

    *mem=a;
  }while(memkb<4096);

  
    console_print("mem_start :");
    console_print_hexa((unsigned int)mem_start);
    console_print("mem_end :");
    console_print_hexa((unsigned int)mem_end);
    console_print("\r\n");
  

  return 0;
}
