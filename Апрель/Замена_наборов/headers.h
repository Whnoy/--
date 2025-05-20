#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
    char *in;
    int inLen;
    char *out;
    int outLen;
} Dict;


int swap(char *input_l, char *output_l, Dict *dict, int dict_size);
