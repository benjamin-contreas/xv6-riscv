#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  if(argc != 3){
    fprintf(2, "usage: chmod <mode> <file>\n");
    exit(1);
  }

  int mode = atoi(argv[1]);
  if(chmod(argv[2], mode) < 0){
    fprintf(2, "chmod: cannot change mode of %s\n", argv[2]);
    exit(1);
  }

  exit(0);
}
