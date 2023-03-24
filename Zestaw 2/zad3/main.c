#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
int main(){
    DIR* dir = opendir("./");
    struct dirent* current_file;
    long long sumOfBytes = 0;
    struct stat stats;
    while((current_file = readdir(dir))){
        stat(current_file->d_name,&stats);
        if(!S_ISDIR(stats.st_mode)){
            printf("%s %ld\n", current_file->d_name,stats.st_size);
            sumOfBytes+= stats.st_size;
        }
    }
    printf("Pliki w tym folderze zajmują łacznie: %lld\n",sumOfBytes);
    return 0;
}