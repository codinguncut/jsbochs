#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

typedef uint8_t  Bit8u;
typedef uint16_t Bit16u;
typedef uint32_t Bit32u;
typedef uint64_t Bit64u;

static inline
void ReadHostWordFromLittleEndian(Bit32u* hostPtr, Bit16u &nativeVar16) {
  nativeVar16 = (Bit16u)*((Bit8u*)hostPtr) | ((Bit16u)*(((Bit8u*)hostPtr)+1))<<8;
}

static inline
void ReadHostDWordFromLittleEndian(Bit32u* hostPtr, Bit32u &nativeVar32) {
  nativeVar32 = (Bit32u)*(Bit8u*)hostPtr | ((Bit32u)*(((Bit8u*)hostPtr)+1))<<8 | ((Bit32u)*(((Bit8u*)hostPtr)+2))<<16 | ((Bit32u)*(((Bit8u*)hostPtr)+3))<<24;
}

static inline
void WriteHostWordToLittleEndian(Bit32u* hostPtr, Bit16u nativeVar16) {
    ((Bit8u*)hostPtr)[0]  = (Bit8u)nativeVar16;
    ((Bit8u*)hostPtr)[1]  = (Bit8u)(nativeVar16>>8);
}

static inline
void WriteHostDWordToLittleEndian(Bit32u* hostPtr, Bit32u nativeVar32) {
    ((Bit8u*)hostPtr)[0]  = (Bit8u)nativeVar32;
    ((Bit8u*)hostPtr)[1]  = (Bit8u)(nativeVar32>>8);
    ((Bit8u*)hostPtr)[2]  = (Bit8u)(nativeVar32>>16);
    ((Bit8u*)hostPtr)[3]  = (Bit8u)(nativeVar32>>24);
}

int main()
{
  Bit8u data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09};
  long *ptr = (long*)(data+1);

  Bit8u bit8, bit8man;
  Bit16u bit16, bit16man;
  Bit32u bit32, bit32man;
  Bit64u bit64, bit64man;

  clock_t start, finish;
  long iterations = 40000000;

  start = clock() / (CLOCKS_PER_SEC / 1000);
  for (long i = 0; i < iterations; i++)
    memcpy((void*)&(bit16), (void*)(ptr), sizeof(Bit16u));
  finish = clock() / (CLOCKS_PER_SEC / 1000);
  printf("memcpy16 - %ld\n", finish - start);
  
  start = clock() / (CLOCKS_PER_SEC / 1000);
  for (long i = 0; i < iterations; i++)
    ReadHostWordFromLittleEndian((Bit32u*)ptr, bit16man);
  finish = clock() / (CLOCKS_PER_SEC / 1000);
  printf("inline16 - %ld\n", finish - start);
  
  start = clock() / (CLOCKS_PER_SEC / 1000);
  for (long i = 0; i < iterations; i++)
    memcpy((void*)&(bit32), (void*)(ptr), sizeof(Bit32u));
  finish = clock() / (CLOCKS_PER_SEC / 1000);
  printf("memcpy32 - %ld\n", finish - start);
  
  start = clock() / (CLOCKS_PER_SEC / 1000);
  for (long i = 0; i < iterations; i++)
    ReadHostDWordFromLittleEndian((Bit32u*)ptr, bit32man);
  finish = clock() / (CLOCKS_PER_SEC / 1000);
  printf("inline32 - %ld\n", finish - start);
  
  start = clock() / (CLOCKS_PER_SEC / 1000);
  for (long i = 0; i < iterations; i++)
    memcpy((void*)ptr, (void*)(&bit16man), sizeof(Bit16u));
  finish = clock() / (CLOCKS_PER_SEC / 1000);
  printf("memcpy write16 - %ld\n", finish - start);

  start = clock() / (CLOCKS_PER_SEC / 1000);
  for (long i = 0; i < iterations; i++)
    WriteHostWordToLittleEndian((Bit32u*)ptr, bit16man);
  finish = clock() / (CLOCKS_PER_SEC / 1000);
  printf("inline write16 - %ld\n", finish - start);
  
  start = clock() / (CLOCKS_PER_SEC / 1000);
  for (long i = 0; i < iterations; i++)
    memcpy((void*)ptr, (void*)(&bit32man), sizeof(Bit32u));
  finish = clock() / (CLOCKS_PER_SEC / 1000);
  printf("memcpy write32 - %ld\n", finish - start);

  start = clock() / (CLOCKS_PER_SEC / 1000);
  for (long i = 0; i < iterations; i++)
    WriteHostDWordToLittleEndian((Bit32u*)ptr, bit32man);
  finish = clock() / (CLOCKS_PER_SEC / 1000);
  printf("inline write32 - %ld\n", finish - start);
/*
  memcpy((void*)&(bit32), (void*)(ptr), sizeof(Bit32u));
  memcpy((void*)&(bit64), (void*)(ptr), sizeof(Bit64u));
  
  ReadHostDWordFromLittleEndian((Bit32u*)ptr, bit32man);

  printf("bit8    %02x\n", bit8);
  printf("bit16    %04x\n", bit16);
  printf("bit16man %04x\n", bit16man);
  printf("bit32    %08x\n", bit32);
  printf("bit32man %08x\n", bit32man);
  printf("bit64    %016llx\n", bit64);

  Bit32u source = 0x12345678;
  Bit32u empty[10] = {0};
  Bit32u *emptyPtr = (Bit32u*)(((Bit8u*)empty)+1);
  printf("empty: %08x\n", *(Bit32u*)emptyPtr);
  WriteHostDWordToLittleEndian(emptyPtr, source);
  printf("empty: %08x\n", *(Bit32u*)emptyPtr);
  printf("data: %016llx\n", *(Bit64u*)empty);

  Bit32u emptycpy[10] = {0};
  Bit32u* cpyptr = (Bit32u*)(((Bit8u*)emptycpy)+1);
  memcpy((void*)cpyptr, (void*)(&source), sizeof(Bit32u));
  printf("emptycpy: %08x\n", *(Bit32u*)cpyptr);
  printf("data: %016llx\n", *(Bit64u*)cpyptr);
*/
}
