#include "headers.h"


int main(void)
{
    double a, b, eps, ans;
    unsigned long n;
    printf("Введите концы отрезка: ");
    scanf("%lf %lf", &a, &b);
    printf("Введите погрешность: ");
    scanf("%lf", &eps);

    printf("Метод прямоугольников:\n Разбиение на %u отрезков, ответ: %lf\n", slov1(quadratic, a, b, eps, &ans), ans);
    ans = 0;
    printf("Метод трапеций:\n Разбиение на %u отрезков, ответ: %lf\n", slov2(quadratic, a, b, eps, &ans), ans);
    ans = 0;
    printf("Метод Симпсона:\n Разбиение на %u отрезков, ответ: %lf\n", slov3(quadratic, a, b, eps, &ans), ans);
    ans = 0;
    printf("Метод Гауса:\n Разбиение на %u отрезков, ответ: %lf\n", slov4(quadratic, a, b, eps, &ans), ans);

    return 0;
}