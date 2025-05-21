#include "headers.h"


int main(void) {
    char *input_file, *output_file;
    FILE *input, *output;

    int *strs;

    input_file = malloc(20 * sizeof(char));
    output_file = malloc(20 * sizeof(char));

    printf("Enter dictionary file name: ");
    scanf("%s", input_file);
    input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Error opening file %s\n", input_file);
        free(input_file);
        return 1;
    }

    printf("Enter output file name: ");
    scanf("%s", output_file);
    output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Error opening file %s\n", output_file);
        fclose(input);
        free(input_file);
        return 1;
    }

    strs = malloc(10 * sizeof(int));
    findStrings(input, output, strs);

    for (int i = 0; i < 3; i++) {
        printf("%d ", strs[i]);
    }

    free(input_file);
    free(output_file);

    return 0;
}