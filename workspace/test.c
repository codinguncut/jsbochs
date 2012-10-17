#include <stdio.h>
#include <string.h>

typedef unsigned char   Bit8u;
typedef unsigned short  Bit16u;
typedef unsigned int    Bit32u;

int main()
{
  Bit8u data[6] = {0x01,0x23,0x45,0x67,0x89, 0x01};
  Bit32u* ptr = (Bit32u*)(data+1);
  Bit32u target;
  memcpy((void*)&(target), (void*)ptr, sizeof(target));

  printf("target: %x\n", target);
  printf("data[1,2] 16bit: %x\n", *(ptr));
}
