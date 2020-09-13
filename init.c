// init: The initial user-level program

#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

char *argv[] = { "sh", 0 };

int
main(void)
{
  int pid, wpid;

  mknod("console0", 1, 1);
  mknod("console1", 1, 2);
  mknod("console2", 1, 3);
  open("console0", O_RDWR); // 0 stdin
  open("console1", O_RDWR); // 1 stdout
  open("console2", O_RDWR); // 2 stderr

  mknod("display", 2, 1); // the second argument is DISPLAY = 2
  open("display", O_RDWR); // 3

  for(;;){
    printf(1, "init: starting sh\n");
    pid = fork();
    if(pid < 0){
      printf(1, "init: fork failed\n");
      exit();
    }
    if(pid == 0){
      exec("sh", argv);
      printf(1, "init: exec sh failed\n");
      exit();
    }
    while((wpid=wait()) >= 0 && wpid != pid)
      printf(1, "zombie!\n");
  }
}
