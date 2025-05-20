#include "headers.h"


int main(void) {
    FILE *input;
    char *input_file, word[20] = " ok";
    int *i;

    input_file = malloc(20 * sizeof(char));

    printf("Enter input file name: ");
    scanf("%s", input_file);
    input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }
    

    free(input_file);

    i = findStr(input, word);

    printf("Row: %d\n", i[0]);
    printf("Num: %d\n", i[1]);

    fclose(input);
    
    return 0;
}