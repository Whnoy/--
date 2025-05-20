#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node{
    char *ch;
    struct Node *next;
} Node;


int printW(FILE *input, FILE *output);