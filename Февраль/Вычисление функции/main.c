#include "headers.h"

int main(void) {
    double x, eps;
    char func, str[50];

    printf("Что посчитать? exp(), sin(), cos(), ln()\n");
    scanf("%s", str);

    func = str[0];
    if (str[2] == '(') {
        x = atof(str + 3);
    } else {
        x = atof(str + 4);
    }

    printf("выберете точность: ");
    if (scanf("%lf", &eps) != 1) {
        printf("Ошибка ввода точности!\n");
        return 1;
    }

    if (eps <= 0) {
        printf("Ошибка: точность должна быть положительным числом\n");
        return 1;
    }

    if (func == 'l' && x <= 0) {
        printf("Ошибка: аргумент логарифма должен быть больше 0\n");
        return 1;
    }

    switch (func) {
    case 'e':
        printf("exp(%lf) = %Lf\n", x, expcalc(x, eps));
        break;
    case 's':
        printf("sin(%lf) = %Lf\n", x, sincalc(x, eps));
        break;
    case 'c':
        printf("cos(%lf) = %Lf\n", x, coscalc(x, eps));
        break;
    case 'l':
        printf("ln(%lf) = %Lf\n", x, lncalc(x, eps));
        break;
    default:
        printf("неизвестная функция\n");
        break;
    }
    return 0;
}