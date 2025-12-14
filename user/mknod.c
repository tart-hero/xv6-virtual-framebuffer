#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  if(argc != 4){
    printf("Usage: mknod file major minor\n");
    exit(1);
  }

  mknod(argv[1], atoi(argv[2]), atoi(argv[3]));
  exit(0);
}
