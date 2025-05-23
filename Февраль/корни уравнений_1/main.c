#include "headers.h"


int main(void) {

    double a, b, eps;
    double ans;

    int res;

    printf("введите границы отрезка: ");
    scanf("%lf %lf", &a, &b);
    printf("введите точность:");
    scanf("%lf", &eps);

    if (eps <= 0) {
        printf("Точность должна быть положительной!\n");
        return 1;
    }

    res = slov1(sin, a, b, eps, &ans);

    printf("Деление пополам:\n За %d итераций найден корень: %lf\n", res, ans);
    ans = 0;
    printf("Метод Ньютона:\n За %d итераций найден корень: %lf\n", slov2(sin, a, b, eps, &ans), ans);
    ans = 0;
    printf("Метод секущих:\n За %d итераций найден корень: %lf\n", slov3(sin, a, b, eps, &ans), ans);

    return 0;
}