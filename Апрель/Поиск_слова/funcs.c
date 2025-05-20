#include "headers.h"


void shift_left(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        str[i] = str[i+1];
        i++;
    }
    // '\0' автоматически окажется на месте
}


int *findStr(FILE *input, const char *str) {
    char *buff;
    int rows, num, len, *ans;

    for (len = 0; str[len] != '\0'; len++);

    buff = malloc((len + 1) * sizeof(char));

    for (int i = 0; i < len; i++) {
        buff[i] = getc(input);
        if (buff[i] == EOF) {
            break;
        }
    }
    buff[len] = '\0';

    for (rows = 1, num = 1;;) {
        if (strcmp(buff, str) == 0) {
            break;
        }
        if (buff[len-1] == '\n') {
            rows++;
            num = -len + 1;
        }
        shift_left(buff);
        buff[len-1] = getc(input);
        num++;
        if (buff[len-1] == EOF) {
            return NULL;
        }
    }

    ans = malloc(2 * sizeof(int));
    ans[0] = rows;
    ans[1] = num;

    free(buff);
    
    return ans;
        
}