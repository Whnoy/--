#include "testdet.h"


int testRand(FILE *output) {
    unsigned n = 2;

    clock_t start=0, end=0;
    long double det;

    Matrix matrix;

    for (unsigned i = 0; n <= 64 && ((double)(end - start)) / CLOCKS_PER_SEC <= 4; i++, n *= 2) {
        matrix.matrix = createMatrix(n, n);
        matrix.rows = n;
        matrix.cols = n;
        matrix.acts = (MatActs){0, 1, 1};

        for (unsigned k = 0; k < n; k++) {
            for (unsigned j = 0; j < n; j++) {
                matrix.matrix[k][j] = randomDouble(10);
            }
        }

        normiseMatrix(matrix.matrix, matrix.rows, matrix.cols, &matrix.acts);

        start = clock();
        det = findMatDet(matrix.matrix, matrix.rows, &matrix.acts);
        end = clock();
        fprintf(output, "%ux%u: %lf, %Lf\n", n, n, ((double)(end - start)) / CLOCKS_PER_SEC, det);


        for (int i = 0; i < n; i++) {
            free(matrix.matrix[i]);
        }
        free(matrix.matrix);
    }    

    fclose(output);
    return 0;
}

int testCorrect(FILE *output) {
    Matrix matrix;
    char filename[20] = "Determ/test5.txt";
    FILE *file;

    long double det;
    double ans;

    if (output == NULL) {
        printf("Error opening output file\n");
        return 0;
    }
    
    for (int i = 1; i <= 5; i++) {
        filename[11] = '0' + i;
        file = fopen(filename, "r");
        if (file == NULL) {
            printf("Error opening file %s\n", filename);
            continue;
        }
        matrix = readMatrix(file);
        if (matrix.matrix == NULL) {
            printf("%s: incorrect file\n", filename);
            continue;
        }

        fscanf(file, "%lf", &ans);

        normiseMatrix(matrix.matrix, matrix.rows, matrix.cols, &matrix.acts);
        
        det = findMatDet(matrix.matrix, matrix.rows, &matrix.acts);

        fprintf(output, "%s:\t det = %LF,\t ans = %lf\n", filename, det, ans);

        fclose(file);
        for (int j = 0; j < matrix.rows; j++) {
            free(matrix.matrix[j]);
        }
        free(matrix.matrix);
    }
    return 5;
}