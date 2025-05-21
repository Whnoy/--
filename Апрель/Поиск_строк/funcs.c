#include "headers.h"


void addNode(Node **list, int ch) {
    Node *newNode = malloc(sizeof(Node));
    newNode->num = ch;
    newNode->next = NULL;

    if (*list == NULL) {
        *list = newNode;
    } else {
        Node *cur = *list;
        while (cur->next != NULL)
            cur = cur->next;
        cur->next = newNode;
    }
}

int countLines(FILE *file) {
    int count = 0;
    int ch;
    while ((ch = fgetc(file)) != EOF) {
        if (ch == '\n')
            count++;
    }
    rewind(file); // возвращаем указатель файла в начало
    return count;
}

int findStrings(FILE *inputA, FILE *inputB, int *strs) {
    char **lineA, **lineB, chA, chB;
    size_t lenA = countLines(inputA), lenB = countLines(inputB);
    Node *list = NULL;
    int tell;
    int k;

        
    lineA = malloc(sizeof(char*) * lenA);
    for (int i = 0; i < lenA; i++) {
        k = 0;
        tell = ftell(inputA);
        for (char ch = getc(inputA); ch != EOF && ch != '\n'; ch = getc(inputA), k++);
        fseek(inputA, tell, SEEK_SET);
        lineA[i] = malloc(sizeof(char) * (k+1));
        for (int j = 0; j < i; j++) {
            lineA[i][j] = getc(inputA);
        }
        lineA[i][k] = '\0';
        fseek(inputA, 1, SEEK_CUR);
    }

    lineB = malloc(sizeof(char*) * lenB);
    for (int i = 0; i < lenB; i++) {
        k = 0;
        tell = ftell(inputB);
        for (char ch = getc(inputB); ch != EOF && ch != '\n'; ch = getc(inputB), k++);
        fseek(inputB, tell, SEEK_SET);
        lineB[i] = malloc(sizeof(char) * (k+1));
        for (int j = 0; j < i; j++) {
            lineB[i][j] = getc(inputB);
        }
        lineB[i][k] = '\0';
        fseek(inputB, 1, SEEK_CUR);
    }

    for (int i = 0, k = 0, kn = 0, n = 0; i < lenA-1; i++, k++, kn++) {
        if (strcmp(lineA[i], lineB[k]) != 0 && strcmp(lineA[i+1], lineB[k]) == 0) {
            k++;
            strs[n] = kn;
            n++;
        }
        else if (strcmp(lineA[i], lineB[k]) != 0 && strcmp(lineA[i+1], lineB[k]) != 0) {
            k--;
            --kn;
            strs[n] = -i;
            n++;
        }
    }
}
    