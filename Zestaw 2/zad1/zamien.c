#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Zła ilość argumentów!\n");
    }else{
        pid_t child_pid;
        printf("PID glownego programu: %d\n", (int)getpid());
        child_pid = fork();
        if(child_pid!=0) {
            printf("Proces rodzica: Proces rodzica ma pid:%d\n", (int)getpid());
            printf("Proces rodzica: Proces dziecka ma pid:%d\n", (int)child_pid);
        } else {
            printf("Identyfikator rodzica:%d Mój identyfikator:%d\n",(int)getppid(),(int)getpid());
        }
    }
    return 0;
}