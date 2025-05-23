#include "testRank.h"


int testCorrect(FILE *output) {
    Matrix matrix;
    char filename[20] = "Rank/test@.txt";
    FILE *file;

    int rank;
    int ans;

    if (output == NULL) {
        printf("Error opening output file\n");
        return -1;
    }
    
    for (int i = 1; i <= 5; i++) {
        filename[9] = '0' + i;
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

        fscanf(file, "%d", &ans);

        normiseMatrix(matrix.matrix, matrix.rows, matrix.cols, &matrix.acts);
        
        rank = findMatRank(matrix.matrix, matrix.rows, matrix.cols,&matrix.acts);

        fprintf(output, "%s:\t det = %d,\t ans = %d\n", filename, rank, ans);

        fclose(file);
        for (int j = 0; j < matrix.rows; j++) {
            free(matrix.matrix[j]);
        }
        free(matrix.matrix);
    }
    return 5;
}


int testReplace(FILE *output, int n) {
    Matrix matrix = {createMatrix(n, n), n, n, {0, 1, 1}}, tmp;
    int rank;
    int k=-1, p=-1;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix.matrix[i][j] = 1;
        }
    }

    if (output == NULL) {
        printf("Error opening output file\n");
        return -1;
    }

    for (int i = 0; i < n; i++) {
        tmp = copyMatrix(matrix);
        rank = findMatRank(tmp.matrix, tmp.rows, tmp.cols, &tmp.acts);
        fprintf(output, "%d:\t rank = %d\t%d,%d replaced to 0\n", i, rank, k, p);
        k = rand() % n;
        p = rand() % n;
        matrix.matrix[k][p] = 0;
    }
    return n;
}
