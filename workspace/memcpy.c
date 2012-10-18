#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>

typedef uint8_t  Bit8u;
typedef uint16_t Bit16u;
typedef uint32_t Bit32u;
typedef uint64_t Bit64u;

static inline
Bit16u ReadHostWordFromLittleEndianF(Bit8u* hostPtr) {
  return( (Bit16u)*hostPtr | ((Bit16u)*(hostPtr+1))<<8 );
}

static inline
Bit32u ReadHostDWordFromLittleEndianF(Bit8u* hostPtr) {
  return( (Bit32u)*hostPtr | ((Bit32u)hostPtr[1])<<8 | ((Bit32u)hostPtr[2])<<16 | ((Bit32u)hostPtr[3])<<24 );
}

static inline
Bit64u ReadHostQWordFromLittleEndianF(Bit8u* hostPtr) {
  return( (Bit64u)*hostPtr | ((Bit64u)hostPtr[1])<<8 | ((Bit64u)hostPtr[2])<<16 | ((Bit64u)hostPtr[3])<<24 | ((Bit64u)hostPtr[4])<<32 | ((Bit64u)hostPtr[5])<<40 | ((Bit64u)hostPtr[6])<<48 | ((Bit64u)hostPtr[7])<<56 );
}

static inline
void WriteHostWordToLittleEndianF(Bit8u* hostPtr, Bit16u nativeVar16) {
    (hostPtr)[0]  = (Bit8u)nativeVar16;
    (hostPtr)[1]  = (Bit8u)(nativeVar16>>8);
}

static inline
void WriteHostDWordToLittleEndianF(Bit8u* hostPtr, Bit32u nativeVar32) {
    (hostPtr)[0]  = (Bit8u)nativeVar32;
    (hostPtr)[1]  = (Bit8u)(nativeVar32>>8);
    (hostPtr)[2]  = (Bit8u)(nativeVar32>>16);
    (hostPtr)[3]  = (Bit8u)(nativeVar32>>24);
}

static inline
void WriteHostQWordToLittleEndianF(Bit8u* hostPtr, Bit64u nativeVar64) {
    (hostPtr)[0]  = (Bit8u)nativeVar64;
    (hostPtr)[1]  = (Bit8u)(nativeVar64>>8);
    (hostPtr)[2]  = (Bit8u)(nativeVar64>>16);
    (hostPtr)[3]  = (Bit8u)(nativeVar64>>24);
    (hostPtr)[4]  = (Bit8u)(nativeVar64>>32);
    (hostPtr)[5]  = (Bit8u)(nativeVar64>>40);
    (hostPtr)[6]  = (Bit8u)(nativeVar64>>48);
    (hostPtr)[7]  = (Bit8u)(nativeVar64>>56);
}

clock_t start, finish;
void time_start()
{
  start = clock() / (CLOCKS_PER_SEC / 1000);
}

void time_end(char *desc)
{
  finish = clock() / (CLOCKS_PER_SEC / 1000);
  printf("%s - %ld\n", desc, finish - start);
}

int main()
{
  Bit8u data[30] = {0};
  long *ptr = (long*)(data+1);
  long iterations = 10000000;
  long i;

  Bit16u bit16 = 0x12;
  Bit32u bit32 = 0x1234;
  Bit64u bit64 = 0x12345678;

  WriteHostWordToLittleEndianF((Bit8u*)ptr, bit16);
  assert(bit16 == ReadHostWordFromLittleEndianF((Bit8u*)ptr));
  
  WriteHostDWordToLittleEndianF((Bit8u*)ptr, bit32);
  assert(bit32 == ReadHostDWordFromLittleEndianF((Bit8u*)ptr));
  
  WriteHostQWordToLittleEndianF((Bit8u*)ptr, bit64);
  assert(bit64 == ReadHostQWordFromLittleEndianF((Bit8u*)ptr));

  time_start();
  for (i = 0; i < iterations; i++)
    memcpy((void*)&(bit16), (void*)(ptr), sizeof(Bit16u));
  time_end("memcpy16");
  
  time_start();
  for (i = 0; i < iterations; i++)
    memcpy((void*)&(bit32), (void*)(ptr), sizeof(Bit32u));
  time_end("memcpy32");
  
  time_start();
  for (i = 0; i < iterations; i++)
    memcpy((void*)&(bit64), (void*)(ptr), sizeof(Bit64u));
  time_end("memcpy64");
  
  time_start();
  for (i = 0; i < iterations; i++)
    bit16 = ReadHostWordFromLittleEndianF((Bit8u*)ptr);
  time_end("read16");
  
  time_start();
  for (i = 0; i < iterations; i++)
    bit32 = ReadHostDWordFromLittleEndianF((Bit8u*)ptr);
  time_end("read32");
  
  time_start();
  for (i = 0; i < iterations; i++)
    bit64 = ReadHostQWordFromLittleEndianF((Bit8u*)ptr);
  time_end("read64");
  
  time_start();
  for (i = 0; i < iterations; i++)
    WriteHostWordToLittleEndianF((Bit8u*)ptr, bit16);
  time_end("write16");
  
  time_start();
  for (i = 0; i < iterations; i++)
    WriteHostDWordToLittleEndianF((Bit8u*)ptr, bit32);
  time_end("write32");
  
  time_start();
  for (i = 0; i < iterations; i++)
    WriteHostQWordToLittleEndianF((Bit8u*)ptr, bit64);
  time_end("write32");
/*
  memcpy((void*)&(bit32), (void*)(ptr), sizeof(Bit32u));
  memcpy((void*)&(bit64), (void*)(ptr), sizeof(Bit64u));
  
  ReadHostDWordFromLittleEndianF((Bit32u*)ptr, bit32man);

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
  WriteHostDWordToLittleEndianF(emptyPtr, source);
  printf("empty: %08x\n", *(Bit32u*)emptyPtr);
  printf("data: %016llx\n", *(Bit64u*)empty);

  Bit32u emptycpy[10] = {0};
  Bit32u* cpyptr = (Bit32u*)(((Bit8u*)emptycpy)+1);
  memcpy((void*)cpyptr, (void*)(&source), sizeof(Bit32u));
  printf("emptycpy: %08x\n", *(Bit32u*)cpyptr);
  printf("data: %016llx\n", *(Bit64u*)cpyptr);
*/
}
