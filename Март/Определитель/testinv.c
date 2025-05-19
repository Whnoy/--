#include "testinv.h"


int testCorrect(FILE *output) {
    Matrix matrix, invMat;
    char filename[20] = "Inc/test1.txt";
    FILE *file;

    long double det;
    double ans;

    if (output == NULL) {
        printf("Error opening output file\n");
        return 0;
    }
    
    for (int i = 1; i <= 5; i++) {
        filename[8] = '0' + i;
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening file %s\n", filename);
            continue;
        }
        matrix = readMatrix(file);
        if (matrix.matrix == NULL) {
            printf("%s: incorrect file data\n", filename);
            continue;
        }

        fscanf(file, "%lf", &ans);

        normiseMatrix(matrix.matrix, matrix.rows, matrix.cols, &matrix.acts);
        
        invMat = findInv(matrix.matrix, matrix.rows, &matrix.acts);

        drawMatrix(invMat.matrix, matrix.rows, matrix.cols, output);

        fclose(file);
        for (int j = 0; j < matrix.rows; j++) {
            free(matrix.matrix[j]);
        }
        free(matrix.matrix);
    }
    return 5;
}