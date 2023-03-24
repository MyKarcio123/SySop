//
// Created by karol on 04.03.23.
//

#ifndef ZAD1_LIB_H
#define ZAD1_LIB_H

typedef struct textArray{
    char **text;
    int maxSize;
    int currentSize;
}textArray;
struct textArray* initTextArray(int _maxSize);
void countInTextArray(char* textName,struct textArray* _textArray);
char* getTextFromTextArray(int index,struct textArray* _textArray);
void removeTextFromTextArray(int index, struct textArray* _textArray);
void clearTextArray(struct textArray* _textArray);
void deleteTextArray(struct textArray* _textArray);
#endif //ZAD1_LIB_H
