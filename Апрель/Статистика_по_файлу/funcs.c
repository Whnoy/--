#include "headers.h"


int statistics(FILE *input, int *maxCount, int *minCount, double *strMed ,double *charMed) {
    int strN = 0;
    int chN = 0;
    int strL;
    int sum = 0;
    int i = 1;

    int charNum[256] = {0};


    *maxCount = 0;
    *minCount = 0;


    int in_word = 0;
    strL = 0;
    strN = 0;

    for (int ch;;) {
        ch = fgetc(input);
        if (ch == EOF) break;
        chN++;

        if (ch != ' ' && ch != '\n') {
            if (!in_word) {
                in_word = 1;
                strL = 0;
                strN++;
            }
            strL++;
        } else {
            if (in_word) {
                sum += strL;
                if (strL > *maxCount) *maxCount = strL;
                if (strL < *minCount || *minCount == 0) *minCount = strL;
                strL = 0;
                in_word = 0;
            }
        }
        charMed[(unsigned char)ch] += 1;
    }

    // Учитываем последнее слово, если файл не заканчивается пробелом/переводом строки
    if (in_word) {
        sum += strL;
        if (strL > *maxCount) *maxCount = strL;
        if (strL < *minCount || *minCount == 0) *minCount = strL;
    }

    // Считаем среднюю длину слова
    if (strN > 0)
        *strMed = (double)sum / strN;
    else
        *strMed = 0.0;

    for (int j = 0; j < 256; j++) {
        charMed[j] /= chN;
    }
}