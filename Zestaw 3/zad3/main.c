#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <string.h>

void search_dir(char* dir_path, char* pattern);
int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Zła ilość argumentów!\n");
        return EXIT_FAILURE;
    }else{
        search_dir(argv[0],argv[1]);
    }
    while(wait(NULL)>0)
    return EXIT_SUCCESS;
}
void search_dir(char* dir_path, char* pattern){
    DIR* dir;
    struct dirent* structdirent;
    struct stat stat_buf;
    char file_path[PATH_MAX];
    pid_t pid;
    if((dir = opendir(dir_path))==NULL){
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    while((structdirent = readdir(dir)) != NULL){
        if(strcmp(structdirent->d_name, ".") == 0 || strcmp(structdirent->d_name,"..") ==0){
            continue;
        }
        if(lstat(file_path,&stat_buf) ==-1){
            perror("lstat");
            exit(EXIT_FAILURE);
        }

        if(S_ISDIR(stat_buf.st_mode)){
            pid = fork();
            if (pid==-1) {
                perror("fork");
            }else if(pid == 0){
                search_dir(file_path, pattern);
                exit(EXIT_SUCCESS);
            }
        }
        else{
            FILE* file;
            char* line = NULL;
            size_t len =0;
            if((file= fopen(file_path,"r"))==NULL){
                perror("open");
                exit(EXIT_FAILURE);
            }

            getline(&line, &len, file);
            if(strncmp(line, pattern, strlen(pattern) == 0)){
                printf("PID %d, %s",getpid(), realpath(file_path,NULL));
            }

            fclose(file);
        }
    }
}