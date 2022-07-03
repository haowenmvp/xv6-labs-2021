#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

  if(argc != 1){
    fprintf(2, "Usage: pingpong\n");
    exit(1);
  }

  int pc2p[2];
  int pp2c[2];

  pipe(pc2p);
  pipe(pp2c);

  int pid;

  pid = fork();
  if(pid == 0){
    char buf;
    read(pp2c[0], &buf, 1);
  	printf("%d: received ping\n", pid);
  	write(pc2p[1], &buf, 1);
  }else{
  	write(pp2c[1], "d", 1);
  	wait(0);
  	char buf;
  	read(pc2p[0], &buf, 1);
  	printf("%d: received pong\n", pid);

  }
//什么时候要关闭管道
//防止read一直等，把p[1]关闭

  exit(0);
}