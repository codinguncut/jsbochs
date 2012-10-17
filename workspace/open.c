#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>

int main()
{
  char *path = "BIOS-bochs-latest";
  struct stat stat_buf;
  int fd, ret;
  unsigned long size;

  fd = open(path, O_RDONLY);
  ret = fstat(fd, &stat_buf);
  size = (unsigned long)stat_buf.st_size;
  printf("size %lu\n", size);
}
