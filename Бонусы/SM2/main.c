#include "headers.h"


int main(void) {
    FILE *input, *output;
    char *word;

    input = fopen("input.txt", "r");
    if (input == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return -1;
    }
    output = fopen("output.txt", "w");
    if (output == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        fclose(input);
        return -1;
    }

    fscanf(input, "%ms", &word);

    if (delete_line(input, output, word) != 0) {
        fprintf(stderr, "Error deleting line containing the word '%s'.\n", word);
        fclose(input);
        fclose(output);
        free(word);
        return -1;
    }
}