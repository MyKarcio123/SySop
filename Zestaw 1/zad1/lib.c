#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

struct textArray* initTextArray(int _maxSize){
    if(_maxSize==0){printf("Struktura nie została stworzona (za mały rozmiar tablicy)\n");return NULL;}
    struct textArray* text = malloc(sizeof(struct textArray));
    text->maxSize=_maxSize;
    text->currentSize=0;
    text->text= (char **)calloc(_maxSize,sizeof(char *));
    printf("Została stworzona tablica o rozmiarze %d\n",_maxSize);
    return text;
}
void countInTextArray(char* textName,struct textArray* _textArray){
    if(_textArray->currentSize+1 > _textArray->maxSize){
        printf("Limit pamięci przeznaczony na sturkturę został osiągnięty\n");
        return;
    }
    char command[50] = "wc ";
    textName[strlen(textName)-1]='\0';
    char commandSecond[] =" >> /tmp/tmpBuffor";
    strcat(command,textName);
    strcat(command,commandSecond);
    system(command);
    FILE* file;
    file = fopen("/tmp/tmpBuffor","r");
    fseek(file,0,SEEK_END);
    long size = ftell(file);
    fseek(file,0,SEEK_SET);
    _textArray->text[_textArray->currentSize] = (char *)calloc(size,sizeof(char));
    char *c = calloc(1,sizeof(char));
    int i=0;
    do {
        *c = (char) fgetc(file);
        _textArray->text[_textArray->currentSize][i]=*c;
        i++;
    }while(*c!=EOF);
    _textArray->text[_textArray->currentSize][i-2]='\0';

    _textArray->currentSize++;
    remove("/tmp/tmpBuffor");
    fclose(file);
}
char* getTextFromTextArray(int index,struct textArray* _textArray){
    if(index+1>_textArray->currentSize){  return "Brak takiego elementu tablicy!";}
    return _textArray->text[index];
}
void removeTextFromTextArray(int index, struct textArray* _textArray){
    if(index+1>_textArray->currentSize){ printf("Brak takiego elementu tablicy!\n"); return;}
    while(index<_textArray->currentSize){
        _textArray->text[index]=_textArray->text[index+1];
        ++index;
    }
    free(_textArray->text[index]);
    _textArray->currentSize--;
    printf("Element tablicy zostały usunięte z pamięci\n");
}
void clearTextArray(struct textArray* _textArray){
    for(int i=0;i<_textArray->currentSize;++i){
        free(_textArray->text[i]);
    }
    _textArray->currentSize=0;
}
void deleteTextArray(struct textArray* _textArray){
    clearTextArray(_textArray);
    free(_textArray->text);
    _textArray->maxSize=0;
}
