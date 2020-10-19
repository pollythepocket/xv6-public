#include "types.h"
#include "stat.h"
#include "user.h"

int
main(int argc, char * argv[])
{
  printf(1, "Freepages before malloc: %d\n", freepages());
  char * x = malloc(500000);
  memset(x, '?', 500000);
  printf(1, "Freepages after malloc: %d     data: %c\n", freepages(), x[100000]);

  if (fork() == 0) {
    printf(1, "Child: freepages before memset: %d\n", freepages());
    memset(x, 'C', 500000);
    printf(1, "Child: freepages after  memset: %d     data: %c\n", freepages(), x[100000]);
  } else {
    sleep(30);
    printf(1, "Parent: freepages before memset: %d\n", freepages());
    memset(x, 'P', 500000);
    printf(1, "Parent: freepages after  memset: %d     data: %c\n", freepages(), x[100000]);
    wait();
    printf(1, "Parent: freepages after wait(child): %d\n", freepages());
  }
  exit();
}
