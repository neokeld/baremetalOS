#include "memory.h"
#define MEMSTART 0x70000000
#define MEMEND 0x40000000

struct memblock *firstfree;
void *freebase = (void *)MEMSTART-4;

void malloc_init(void){
  firstfree = NULL;
}


void *malloc(size_t size){
  void* addr;
  size_t tmpsize;
  struct memblock* tmpblck;

  console_print("\r\nEntering malloc\r\n");
  console_print("firstfree = ");
  console_print_hexa(firstfree);
  console_print("\r\n");


  if(firstfree == NULL){
    addr = freebase;
    *(((int *)addr)+1) = size;
    freebase -= (size + 4);
    return addr;
  }
  
  tmpblck = firstfree;
  addr = tmpblck->addr;
  console_print("addr = ");
  console_print_hexa(addr);
  console_print("\r\n");

  tmpsize = *(((int *)addr)+1);
  console_print("tmpsize = ");
  console_print_hexa(tmpsize);
  console_print("\r\n");
  console_print("size = ");
  console_print_hexa(size);
  console_print("\r\n");
  console_print("tmpblck->next = ");
  console_print_hexa(tmpblck->next);
  console_print("\r\n");
    
  if(tmpsize >= size){
    console_print("Made it!!!\r\n");
    if(tmpblck->next != NULL)
      tmpblck->next->prev = tmpblck->prev;
    *(((int *)addr)+1)=size;
    console_print("*(((int *)addr)+1) = ");
    console_print_hexa(*(((int *)addr)+1));
    console_print("\r\n");

    return addr;
  }
  while(tmpblck!=NULL ){
    tmpblck = tmpblck->next;
    addr = tmpblck->addr;
    tmpsize = *(((int *)addr)+1);
    if(tmpsize >= size){
      tmpblck->prev->next = tmpblck->next;
      if(tmpblck->next != NULL)
	tmpblck->next->prev = tmpblck->prev;
      *(((int *)addr)+1)=size;
      return addr;
    }
  }
  if(freebase >=(void *)  MEMEND + (size + 4)){
    addr = freebase;
    *(((int *)addr)-1) = size;
    freebase -= (size + 4);
    return addr;
  } 
  return NULL;
}

void free(void* ptr){
  size_t size = *(((int *)ptr)+1);
  struct memblock* newblck;
  struct memblock* tmpblck;
  struct memblock blck;

  /*console_print("\r\nEntering free\r\n");

  console_print("freebase = ");
  console_print_hexa(freebase);
  console_print("\r\n");

  console_print("ptr - size = ");
  console_print_hexa(ptr - size);
  console_print("\r\n");
  */
  if((ptr - size) == freebase){
    freebase += size;
  }
  else if(firstfree == NULL){
    blck.addr = ptr;
    blck.prev = NULL;
    blck.next = NULL;
    firstfree = &blck;
  }
  else{
    newblck = firstfree;
    do{
      tmpblck = newblck;
      newblck = newblck->next;
    }while(newblck != NULL);
    /*TODO : Merge si blocs consécutifs*/
    tmpblck->next = newblck;
    blck.prev = tmpblck;
    blck.addr = ptr;
    blck.next = NULL;
    newblck = &blck;
  }
  
}

    
  


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


    


/*void memtest(){
  volatile unsigned int* mem;

  REGISTRES
  console_print("ETAT DES REGISTRES\r\n");
  console_print_registers();
  console_print("\r\n");
  
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

*/
