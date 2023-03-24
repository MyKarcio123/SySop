#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <malloc.h>
char *reverse_string(char *string){
    int length = strlen(string);
    char *buffer = malloc(length);
    for (int i=0;i<length;++i){
        buffer[i]=string[length-1-i];
    }
    for(int i=0;i<length;++i){
        string[i] = buffer[i];
    }
    return buffer;
}
int main(int argc, char *argv[]){
    if(argc!=3){
        printf("Zła ilość argumentów!\n");
    }else{
        char *inputFile = argv[1];
        char *outputFile = argv[2];
        clock_t startS,endS;
        clock_t startL,endL;
        FILE* file = fopen(inputFile,"r");
        if(file){
            //odwracanie znak po znaku
            char *fileReport = "pomiar_zad_2.txt";
            FILE* report = fopen(fileReport,"wa");
            FILE* endFile = fopen(outputFile,"w");
            fseek(file,0,SEEK_END);
            int sizeFile = (int)ftell(file);
            startS = clock();
            char buffer[1];
            for(int i=2;i<=sizeFile;++i){
                fseek(file,-i,SEEK_END);
                fread(buffer,sizeof(char),1,file);
                fwrite(buffer,sizeof(char),1,endFile);
            }
            endS = clock();
            fwrite("\n",sizeof(char),1,endFile);
            fprintf(report,"Czas odwracania znak po znaku %f\n",(double)(endS-startS)/CLOCKS_PER_SEC);
            //odwracanie blokami
            startL = clock();
            char newBuffer[1024];
            int blockCount = sizeFile / 1024;
            int lastBlockSize = sizeFile % 1024;
            for(int i=0; i<=blockCount;++i){
                fseek(file,-1024*i,SEEK_END);
                size_t char_count = fread(newBuffer,sizeof(char),1024,file);
                fwrite(reverse_string(newBuffer),sizeof(char),char_count,endFile);
            }

            fseek(file,0,SEEK_SET);
            size_t char_count = fread(newBuffer,sizeof(char),lastBlockSize,file);
            fwrite(reverse_string(newBuffer),sizeof(char),char_count,endFile);
            endL = clock();
            fprintf(report,"Czas odwracania blokami %f\n",(double)(endL-startL)/CLOCKS_PER_SEC);
            fclose(file);
            fclose(endFile);
            fclose(report);
        }
        else{
            printf("Nie znaleziono pliku wejściowego!\n");
        }
    }
    return 0;
}