#include "headers.h"


int slov1(double (*func)(double x), double a, double b, double eps, double *ans) {
    double x1=a, x2=b;
    double f1, f2, f0;

    if (fabs(func(x1)) < eps) {
        *ans = x1;
        return 1; // Корень найден на границе
    }
    if (fabs(func(x2)) < eps) {
        *ans = x2;
        return 1; // Корень найден на границе
    }

    unsigned int i = 0;

    if (func(x1) * func(x2) > 0) {
        return -1; // No root in the interval can be found
    }

    while (fabs(x2-x1) > eps) {
        f1 = func(x1);
        f2 = func(x2);

        *ans = (x1 + x2) / 2;
        f0 = func(*ans);

        i++;

        if (fabs(f0) < eps) {
            return i;
        }

        if (f1 * f0 < 0) {
            x2 = *ans;
        } else if (f2 * f0 < 0) {
            x1 = *ans;
        }

        // Условие выхода, если x1 и x2 — соседние double
        if (nextafter(x1, x2) == x2 || nextafter(x2, x1) == x1) {
            *ans = (x1 + x2) / 2;
            return i;
        }
    }

    return i;
}


int slov2(double (*func)(double x), double a, double b, double eps, double *ans) {
    double x = (a + b) / 2;
    unsigned int i = 0;

    if (fabs(func(a)) < eps) { *ans = a; return 1; }
    if (fabs(func(b)) < eps) { *ans = b; return 1; }
    if (func(a) * func(b) > 0) return -1;

    double f, df, prev_x;
    double h = 1e-7;
    do {
        f = func(x);
        df = (func(x + h) - func(x - h)) / (2 * h);
        if (fabs(df) < 1e-12) return 0;
        prev_x = x;
        x = x - f / df;
        i++;
        if (x < a || x > b) return 0;
        if (fabs(func(x)) < eps) { *ans = x; return i; }
        if (fabs(x - prev_x) < eps) { *ans = x; return i; }
    } while (1);
}

int slov3(double (*func)(double x), double a, double b, double eps, double *ans) {
    double x1 = a, x2 = b;
    double f1, f2, f_ans;
    unsigned int i = 0;


    if (fabs(func(x1)) < eps) {
        *ans = x1;
        return 1; // Корень найден на границе
    }
    if (fabs(func(x2)) < eps) {
        *ans = x2;
        return 1; // Корень найден на границе
    }

    // Проверка, что на концах отрезка функция имеет разные знаки
    if (func(x1) * func(x2) > 0) {
        return -1; // Корень не может быть найден
    }

    do {
        i++;
        f1 = func(x1);
        f2 = func(x2);

        if (fabs(f2 - f1) < eps) { // защита от деления на очень малое число
            *ans = (x1 + x2) / 2;
            return i;
        }

        *ans = x1 - f1 * (x2 - x1) / (f2 - f1);
        f_ans = func(*ans);

        if (fabs(f_ans) < eps) return i;

        if (func(x1) * f_ans < 0) {
            x2 = *ans;
        } else {
            x1 = *ans;
        }

        if (fabs(x2 - x1) < eps) {
            *ans = (x1 + x2) / 2;
            return i;
        }

        if (fabs(x1 - *ans) < eps) {
            x1 = nextafter(x1, x2);
            continue;
        } else if (fabs(x2 - *ans) < eps) {
            x2 = nextafter(x2, x1);
            continue;
        }

    } while (1); // ограничение по итерациям

    return -1; // не сошлось
}