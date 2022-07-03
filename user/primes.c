#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void
prime(int pleft[2])
{
  int rec;
  if(read(pleft[0], &rec, sizeof(rec)) != 0)
  {
    printf("prime %d\n", rec);

    int pright[2];
    pipe(pright);

    int pid = fork();
    if(pid == 0)
    {
      // printf("%d\n", rec);
      close(pright[1]);
      close(pleft[0]);  //要加
      prime(pright);
    }
    else
    {
      close(pright[0]);
      int buf;
      while(read(pleft[0], &buf, sizeof(buf)))
      {
        // printf("%d\n", buf);

        if(buf % rec != 0)
        {
          // printf("%d\n", buf);
          write(pright[1], &buf, sizeof(buf));
        }
      }
      close(pright[1]);
      wait(0);
    }
  }
  exit(0);
}

int
main(int argc, char *argv[])
{
  int p1[2];
  pipe(p1);

  int pid = fork();

  if(pid!=0){
    close(p1[0]);
    for(int i = 2; i <= 60; i++)
    {
      // printf("%d\n", i);
      write(p1[1], &i, sizeof(i));
    }
    close(p1[1]);
    wait(0);
  }else{
    close(p1[1]);
    prime(p1);
    close(p1[0]);//感觉没必要，因为退出后会自动close?

  }

  exit(0);
}

