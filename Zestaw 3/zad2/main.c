#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
    if(argc!=2){
        printf("Zła ilość argumentów!\n");
    }else{
        printf("My name %s\n",argv[0]);
        if(execl("/bin/ls","ls",argv[1],NULL) == -1){
            perror("Can't do ls");
            exit(EXIT_FAILURE);
        }
    }
    return EXIT_SUCCESS;
}