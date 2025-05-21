#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node{
    int num;
    struct Node *next;
} Node;

void addNode(Node **list, int ch);

int findStrings(FILE *inputA, FILE *inputB, int *strs);