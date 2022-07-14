#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "user/user.h"
#define MAX_ARG_LEN 1024


int main(int argc, char *argv[]){
    if(argc < 2){
        fprintf(2, "more than a argument\n");
    }
    
    int n, arg_index = 0;
    char buf,  * args[MAXARG], arg[MAX_ARG_LEN];
    for(int i = 1; i < argc; i++){
        args[i-1] = argv[i];
    }
    
    while((n = read(0, &buf, 1)) > 0){//｜前面的直接作为输入
        if(buf == '\n'){
            arg[arg_index] = '\0';

            int pid = fork();
            if(pid == 0){
                args[argc-1] = arg;
                args[argc] = 0;
                exec(args[0], args);
            }else if(pid > 0){
                wait(0);
                arg_index = 0;
            }else{
                fprintf(2, "fork error\n");
                exit(0);
            }
        }else{
            arg[arg_index++] = buf;
        }
    }
    exit(0);
}