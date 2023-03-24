#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Zła ilość argumentów!\n");
    }else{
        pid_t child_pid;
        for(int i=0;i<atoi(argv[1]);++i){
            child_pid = fork();
            if(child_pid==0){
                printf("Id macierzysty:%d Id własny:%d\n",(int)getppid(),(int)getpid());
                exit(0);
            }else{
                wait(NULL);
            }
        }
        printf("Macierzysty proces o Id %d wypisuje argv[1]: %s\n",(int)getpid(),argv[1]);
    }
    return 0;
}