#include "headers.h"


double linear(double x) {
    return 1-x;
}

double quadratic(double x) {
    return x * x;
}

double cubic(double x) {
    return x * x * x;
}

double hyperbolic(double x) {
    return 1 / x;
}

double constant(double x) {
    return 1;
}


int comp(const double a) {
    return (a < 0) ? -1 : 1;
}
    
//Метод прямоугольников
unsigned slov1(double (*func)(double x), double a, double b, double eps, double *ans) {
    unsigned n = 1;
    double width;
    double preAns = 0;

    *ans = 0;

    if (a > b) {
        double tmp = a;
        a = b;
        b = tmp;
    }

    for (; (n == 2 || n == 1 || fabs(preAns - *ans) > eps) && ((n << 1) != 0); n <<= 1) {
        *ans = preAns;

        width = (b - a) / n;

        preAns = 0;

        for (double x = a, y = func(x); x < b; x += width, y = func(x)) {
            preAns += width*y;
        }
        if (isnan(preAns)) return n;

        
    }

    *ans = preAns;
    return n;

}

//Метод трапеций
unsigned slov2(double (*func)(double x), double a, double b, double eps, double *ans) {
    unsigned n = 1;
    double width;
    double preAns = 0;
    double tmp;

    *ans = 0;

    if (a > b) {
        tmp = a;
        a = b;
        b = tmp;
    }

    for (; (n == 2 || n == 1 || fabs(preAns - *ans) > eps) && ((n << 1) != 0); n <<= 1) {
        *ans = preAns;

        width = (b - a) / n;

        preAns = 0;

        for (double x1 = a, x2 = x1 + width; x1 < b; x1 += width, x2 = x1 + width) {
            preAns += (func(x1) + func(x2)) * width / 2;
        }

        if (isnan(preAns)) return n;
    }

    *ans = preAns;
    return n;
}

//Метод Симпсона
unsigned slov3(double (*func)(double x), double a, double b, double eps, double *ans) {
    unsigned n = 1;
    double width;
    double preAns = 0;
    
    if (a > b) {
        double tmp = a;
        a = b;
        b = tmp;
    }

    for (; (n == 2 || n == 1 || fabs(preAns - *ans) > eps) && ((n << 1) != 0); n <<= 1){
        *ans = preAns;

        width = (b - a) / n;

        preAns = 0;

        for (double x1 = a, x2 = x1 + width; x1 < b; x1 += width, x2 = x1 + width) {
            preAns += (func(x1) + 4*func((x1+x2)/2) + func(x2)) * width / 6;
        }

        if (isnan(preAns)) return n;
    }
    *ans = preAns;
    return n;
}

//Метод Гаусса
unsigned slov4(double (*func)(double x), double a, double b, double eps, double *ans) {
    unsigned int n = 1; // Начальное количество разбиений
    double preAns = 0, curAns = 0;
    double width, x1, x2;

    // Узлы и веса для квадратуры Гаусса с двумя узлами
    const double sqrt3 = sqrt(3.0) / 3.0;
    const double w1 = 1.0, w2 = 1.0;

    do {
        preAns = curAns;
        curAns = 0;
        width = (b - a) / n;

        for (unsigned int i = 0; i < n; i++) {
            double left = a + i * width;
            double right = left + width;

            // Преобразование узлов на текущий подотрезок
            x1 = (left + right) / 2 - sqrt3 * (right - left) / 2;
            x2 = (left + right) / 2 + sqrt3 * (right - left) / 2;

            // Вычисление интеграла на подотрезке
            curAns += (right - left) / 2 * (w1 * func(x1) + w2 * func(x2));
        }

        n *= 2; // Увеличиваем количество разбиений
    } while (fabs(curAns - preAns) > eps); // Проверяем точность

    *ans = curAns; // Сохраняем результат
    return n / 2; // Возвращаем количество разбиений
}