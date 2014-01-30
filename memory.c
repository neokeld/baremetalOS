#include "memory.h"
#define MEMSTART 0x7AAAAAAA

struct memblock *firstfree = NULL;
volatile void *freebase = MEMSTART;

void *malloc(size_t size){
  void* ret;

  if(firstfree == NULL){

    console_print("freebase = ");
    console_print_hexa(freebase);

    console_print("\r\n");

    ret = freebase;
    freebase -= size;
    console_print("ret = ");
    console_print_hexa(ret);
    console_print("\r\n");
    console_print("\r\n");

    return ret;
  }
    
}
    
  /*if(size < firstfree->size){
    firstfree->size=*/



/*int memprobe(void){
  volatile unsigned int *mem;
  unsigned int memkb;
  unsigned int mem_count, a;
  
  mem_count = 0;
  memkb = 0;

  do{
    memkb++;
    mem_count += 1024*1024;
    console_print_hexa((char) mem_count);
    mem = (unsigned int*)mem_count;

    a = *mem;
    *mem = 0x55AA55AA;
    console_print_hexa((char) mem);
    console_print("\r\n");
    console_print_hexa((char) *mem);
    console_print("\r\n");
    if(*mem != 0x55AA55AA)
      mem_count = 0;
    else{
      *mem=0xAA55AA55;
      if(*mem != 0xAA55AA55)
	mem_count = 0;
    }

    *mem=a;
  }while(memkb<4096 && mem_count !=0);

  if(memkb>=4096)
    console_print("Not found\r\n");
  else
    console_print_hexa((char) mem);

  return 0;
}
*/


    


void memtest(){
  volatile unsigned int* mem;

  /*REGISTRES
  console_print("ETAT DES REGISTRES\r\n");
  console_print_registers();
  console_print("\r\n");
  */
  //Vérifie les zones mémoires accesibles
  console_print(">mem = MEMSTART;\r\n");
  mem = MEMSTART;
  
  console_print(">*mem = 3;\r\n");
  *mem = 3;
  console_print("mem = ");
  console_print_hexa(mem);
  console_print("\r\n");

  console_print("*mem = ");
  console_print_hexa(*mem);
  console_print("\r\n");
  console_print("\r\n");

  console_print(">(*mem) ++;\r\n");
  (*mem) ++;
  console_print("mem = ");
  console_print_hexa(mem);
  console_print("\r\n");

  console_print("*mem = ");
  console_print_hexa(*mem);
  console_print("\r\n");
  console_print("\r\n");

  console_print(">*mem *= 2;\r\n");
  *mem *=2;
  console_print("mem = ");
  console_print_hexa(mem);
  console_print("\r\n");

  console_print("*mem = ");
  console_print_hexa(*mem);
  console_print("\r\n");
  console_print("\r\n");


  console_print(">mem += 0x80000400;\r\n");
  mem = 0x80000400;
  console_print(">*mem = 17;\r\n");
  *mem = 17;
  console_print(">(*mem) ++;\r\n");
  (*mem) ++;
  console_print("mem = ");
  console_print_hexa(mem);
  console_print("\r\n");

  console_print("*mem = ");
  console_print_hexa(*mem);
  console_print("\r\n");
  console_print("\r\n");

  console_print(">mem += 1024;\r\n");

  mem += 1024;

  console_print("mem = ");
  console_print_hexa(mem);
  console_print("\r\n");

  console_print("*mem = ");
  console_print_hexa(*mem);
  console_print("\r\n");
  console_print("\r\n");

  //REGISTRES
  console_print("ETAT DES REGISTRES\r\n");
  console_print_registers();
}

