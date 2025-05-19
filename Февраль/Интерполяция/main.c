#include "headers.h"


void closeMain(FILE *output, double *pointsKn, double *pointsUnk) {

    fclose(output);
    free(pointsKn);
    free(pointsUnk);
}


int main(void) {
    FILE *inputKn, *inputUnk, *output;
    double *pointsKn, *pointsUnk;
    size_t n=0, m=0;
    char func;


    inputKn = fopen("inputKn.txt", "r");
    if (inputKn == NULL) {
        fprintf(stderr, "Error opening inputKn.txt\n");
        return 1;
    }

    inputUnk = fopen("inputUnk.txt", "r");
    if (inputUnk == NULL) {
        fprintf(stderr, "Error opening inputUnk.txt\n");
        fclose(inputKn);
        return 1;
    }

    output = fopen("output.txt", "w");
    if (output == NULL) {
        fprintf(stderr, "Error opening output.txt\n");
        fclose(inputKn);
        fclose(inputUnk);
        return 1;
    }

    // Read the number of points in the first file
    for (double num; fscanf(inputKn, "%lf", &num) == 1; n++);
    rewind(inputKn);

    // Allocate memory for the points in the first file
    pointsKn = (double *)malloc(n * sizeof(double));

    // Read the number of points in the second file
    for (double num; fscanf(inputUnk, "%lf", &num) == 1; m++);
    m = m * 2;
    rewind(inputUnk);

    // Allocate memory for the points in the second file
    pointsUnk = (double *)malloc(m * sizeof(double));

    // Read the points from the first file
    for (size_t i = 0; fscanf(inputKn, "%lf", pointsKn + i) == 1; i++);
    fclose(inputKn);

    // Read the points from the first file
    for (size_t i = 0; fscanf(inputUnk, "%lf", pointsUnk + i) == 1; i += 2);
    fclose(inputUnk);

    for (size_t i = i; i < m; i += 2) {
        pointsUnk[i+1] = 0;
    }

    scanf(" %c", &func);

    switch (func) {
    case '1':
        // Call the Lagrange function
        if (Lagrange(pointsKn, n, pointsUnk, m) == NULL) {
            fprintf(stderr, "Error in Lagrange function\n");
            closeMain(output, pointsKn, pointsUnk);
            return 1;
        }

        // Write the results to the output file 
        for (size_t i = 0; i < m; i += 2) {
            fprintf(output, "%lf %lf\n", pointsUnk[i], pointsUnk[i+1]);
        }
        break;

        case '2':
        // Call the linear function
        if (linear(pointsKn, n, pointsUnk, m) == NULL) {
            fprintf(stderr, "Error in linear function\n");
            closeMain(output, pointsKn, pointsUnk);
            return 1;
        }

        // Write the results to the output file
        for (size_t i = 0; i < m; i += 2) {
            fprintf(output, "%lf %lf\n", pointsUnk[i], pointsUnk[i+1]);
        }
        break;

    case '3':
        // Call the Hermite function
        if (Hermite(pointsKn, n, pointsUnk, m) == NULL) {
            fprintf(stderr, "Error in Hermite function\n");
            closeMain(output, pointsKn, pointsUnk);
            return 1;
        }

        // Write the results to the output file
        for (size_t i = 0; i < m; i += 2) {
            fprintf(output, "%lf %lf\n", pointsUnk[i], pointsUnk[i+1]);
        }
        break;
    
    case '4':
        // Call the Quadratic function
        if (Quadratic(pointsKn, n, pointsUnk, m) == NULL) {
            fprintf(stderr, "Error in Quadratic function\n");
            closeMain(output, pointsKn, pointsUnk);
            return 1;
        }

        // Write the results to the output file
        for (size_t i = 0; i < m; i += 2) {
            fprintf(output, "%lf %lf\n", pointsUnk[i], pointsUnk[i+1]);
        }
        break;

    
    default:
    fprintf(stderr, "Invalid function choice\n");
    break;
    }

    closeMain(output, pointsKn, pointsUnk);
    return 0;
}