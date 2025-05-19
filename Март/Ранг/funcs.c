#include "headers.h"


double randomDouble(double max) {
    return pow(-1, rand()%2)*((double)(rand() % 999)) + (1/(rand()+1));
}


int findMatRnak(double **A, unsigned n, unsigned m) {
    rungByGauss(A, n, m);

    int rank = 0;
    for (int i = 0; i < n; i++) {
        if (fabs(A[i][i]) > n*1e-15) {
            rank++;
         }
        
    }

    return rank;
}