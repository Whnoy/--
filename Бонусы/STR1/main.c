#include "headers.h"


int main(void) {
    FILE *input = fopen("input.txt", "r");
    if (input == NULL) {printf("Ошибка при открытии файла"); return -1;}
    
    printf("%d\n", count(input));

    fclose(input);
    return 0;
}