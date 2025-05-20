#include "headers.h"


int main(void) {
    FILE *input;
    char *input_file;

    int naxCount, minCount;
    double *charMed, strMed;


    input_file = malloc(20 * sizeof(char));

    printf("Enter dictionary file name: ");
    scanf("%s", input_file);

    input = fopen(input_file, "r");

    charMed = malloc(sizeof(double) * 256);
    statistics(input, &naxCount, &minCount, &strMed, charMed);

    printf("Max count:\t %d\n", naxCount);
    printf("Min count:\t %d\n", minCount);
    printf("String median:\t %lf\n", strMed);
    for (int i = 0; i < 256; i++) {
        printf("Char %3d:\t%lf\n", i, charMed[i]);
    }

    free(input_file);
    fclose(input);


    return 0;
}