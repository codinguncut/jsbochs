#include <stdio.h>
#include <stdint.h>

int main()
{
  void* pointer         = (void*) 0xb525c008;
  unsigned long iulong  = (unsigned long) pointer;
  long ilong            = (long)          pointer;
  intptr_t intptr       = (intptr_t)      pointer;

  printf("pointer      : %llx\n", (uint64_t)pointer);
  printf("unsigned long: %llx\n", (uint64_t) iulong);
  printf("signed   long: %llx\n", (uint64_t) ilong);
  printf("intptr_t     : %llx\n", (uint64_t) intptr);
  printf("pointer == unsigned long? %s\n", ((uint64_t)pointer) == ((uint64_t)iulong) ? "yes" : "no");
  printf("pointer == signed long? %s\n", ((uint64_t)pointer) == ((uint64_t)ilong) ? "yes" : "no");
  printf("sizeof(unsigned long): %d, sizeof(long): %d, sizeof(void*): %d\n", sizeof(iulong), sizeof(ilong), sizeof(void*));
}
