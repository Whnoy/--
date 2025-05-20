#include "headers.h"


int main(void) {
    FILE *input, *output;
    char *input_file, *output_file;

    input_file = malloc(20 * sizeof(char));
    output_file = malloc(20 * sizeof(char));

    printf("Enter input file name: ");
    scanf("%s", input_file);
    input = fopen(input_file, "r");
    if (input == NULL) {
        printf("Error opening input file.\n");
        free(input_file);
        free(output_file);
        return 1;
    }

    printf("Enter output file name: ");
    scanf("%s", output_file);
    output = fopen(output_file, "w");
    if (output == NULL) {
        printf("Error opening output file.\n");
        fclose(input);
        free(input_file);
        free(output_file);
        return 1;
    }

    free(input_file);
    free(output_file);

    delLine(input, output);

    fclose(input);
    fclose(output);
    
    return 0;
}