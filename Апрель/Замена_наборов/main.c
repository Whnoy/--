#include "headers.h"


int main(void) {
    char *input_file, *output_file;

    Dict dict[2] = {{"Most gracious", 13, "Ebeyshiy", 6}, {"Khan", 4, "huesos", 8}};

    input_file = malloc(20 * sizeof(char));
    output_file = malloc(20 * sizeof(char));

    printf("Enter dictionary file name: ");
    scanf("%s", input_file);

    printf("Enter output file name: ");
    scanf("%s", output_file);

    swap(input_file, output_file, dict, 2);

    free(input_file);
    free(output_file);

    return 0;
}