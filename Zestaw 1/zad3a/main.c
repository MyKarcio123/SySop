#include <dlfcn.h>
#include "lib.h"
#include <unistd.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/times.h"
int errorode=0;
double timeElapsedInSeconds(clock_t clockStart, clock_t clockEnd) {
    clock_t clockDiff = clockEnd - clockStart;
    return (double) clockDiff / sysconf(_SC_CLK_TCK);
}

void printTimes(clock_t clockStart, clock_t clockEnd, struct tms tmsStart, struct tms tmsEnd) {
    printf("czas rzeczywisty: %f, czas uzytkownika %f, czas systemu %f \n",
           timeElapsedInSeconds(clockStart, clockEnd), timeElapsedInSeconds(tmsStart.tms_utime, tmsEnd.tms_utime),
           timeElapsedInSeconds(tmsStart.tms_stime, tmsEnd.tms_stime));

}

int checkForNumValue(char* value){
    if(strcmp("0\n",value)==0) return 1;
    if(value == NULL || atoi(value)==0){
        printf("Zła wartość!\n");
        return 0;
    }
    return 1;
}
int checkForValue(char* value){
    if(value == NULL){
        printf("Zła wartość!\n");
        return 0;
    }
    return 1;
}
int checkForInstance(textArray* textArr){
    if(textArr==NULL || textArr->text==NULL){
        printf("Brak lub zła instancja struktury!\n");
        errorode=1;
        return 0;
    }
    return 1;
}
int main(){
#ifdef DLL
    void* libraryHandle = dlopen("./liblib.so", RTLD_LAZY);

    if (libraryHandle==NULL){
        printf("NIe wczyta library.so");
        return -1;
    }
    textArray *(*initTextArray)(int) = dlsym(libraryHandle, "initTextArray");
    void (*countInTextArray)(char*, textArray*) = dlsym(libraryHandle, "countInTextArray");
    char *(*getTextFromTextArray)(int, textArray*) = dlsym(libraryHandle, "getTextFromTextArray");
    void (*removeTextFromTextArray)(int, textArray*) = dlsym(libraryHandle, "removeTextFromTextArray");
    void (*deleteTextArray)(textArray*) = dlsym(libraryHandle, "deleteTextArray");

#endif
    clock_t clockStart, clockEnd;
    struct tms tmsStart, tmsEnd;

    struct textArray* textArr;
    char text[50];
    printf("Dostępne komendy:\ninit size\ncount file\nshow index\ndelete index\ndestroy\n-------------\n");
    while( fgets(text,50,stdin)){
        char * type = strtok(text," ");
        char * value = strtok(NULL," ");
        if(strcmp("init",type)==0 && checkForNumValue(value)==1){
            clockStart = times(&tmsStart);
            textArr = initTextArray(atoi(value));
            clockEnd = times(&tmsEnd);
            printTimes(clockStart,clockEnd, tmsStart, tmsEnd);
        }
        else if(strcmp("destroy\n",type)==0 && checkForInstance(textArr)){
            clockStart = times(&tmsStart);
            deleteTextArray(textArr);
            clockEnd = times(&tmsEnd);
            printf("Tablica została usunięta z pamięci\n");
            printTimes(clockStart,clockEnd, tmsStart, tmsEnd);
        }
        else if (strcmp("count", type) == 0 && checkForInstance(textArr)) {
            clockStart = times(&tmsStart);
            countInTextArray(value, textArr);
            clockEnd = times(&tmsEnd);
            printf("Zostały zliczone słowa i linie\n");
            printTimes(clockStart,clockEnd, tmsStart, tmsEnd);
        }
        else if (strcmp("show", type) == 0  && checkForInstance(textArr)) {
            clockStart = times(&tmsStart);
            printf("%s\n", getTextFromTextArray(atoi(value), textArr));
            clockEnd = times(&tmsEnd);
            printTimes(clockStart,clockEnd, tmsStart, tmsEnd);
        } else if (strcmp("delete", type) == 0 && checkForInstance(textArr)) {
            clockStart = times(&tmsStart);
            removeTextFromTextArray(atoi(value), textArr);
            clockEnd = times(&tmsEnd);
            printTimes(clockStart,clockEnd, tmsStart, tmsEnd);
        } else {
            if(errorode==0) {
                printf("Komenda nie istnieje!\n");
            }
            errorode=0;
        }
    }
    #ifdef DLL
        dlclose(libraryHandle);
    #endif
    return 0;
}