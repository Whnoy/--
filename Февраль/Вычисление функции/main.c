#include "headers.h"


int main(void) {
    double x, eps;
    
    char func, str[50];

    printf("Что посчитать? exp(), sin(), cos(), ln()\n");
    scanf("%s", str);

    func = str[0];
    if (str[2] == '(') {
        x = atof(str + 3);
    } else {x = atof(str + 4);}

    printf("выберете точность: ");
    scanf("%lf", &eps);

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