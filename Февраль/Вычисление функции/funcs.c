#include "headers.h"


long double expcalc(double x, double eps) {
    long double result = 0;
    long double term = 1; // вместо double term = 1;

    for (unsigned long long i = 0;; i++) {
        result += term;

        if (fabsl(term) < eps) {break;}
        term *= x / (i + 1);
    }
    
    return result;
}


long double sincalc(double x, double eps) {
    long double result = 0;
    double term = x;

    for (unsigned long long i = 1;; i++) {
        result += term;

        if (fabsl(term) < eps) {break;}
        term *= -x * x / ((2 * i) * (2 * i + 1));
    }
    
    return result;
}

long double coscalc(double x, double eps) {
    long double result = 0;
    double term = 1;

    for (unsigned long i = 1;; i++) {
        result += term;

        if (fabsl(term) < eps) {break;}
        term *= -x * x / ((2 * i - 1) * (2 * i));
    }
    
    return result;
}


long double lncalc(double x, double eps) {
    if (x <= 0) return nan("");
    if (fabsl(x - 1) < eps) return 0;

    long double y = (x - 1) / (x + 1);
    long double y2 = y * y;
    long double term = 2 * y;
    long double result = term;
    unsigned long k = 1;

    while (fabsl(term) >= eps) {
        term *= y2;
        long double add = 2 * term / (2 * k + 1);
        result += add;
        if (fabsl(add) < eps) break;
        k++;
    }

    return result;
}




