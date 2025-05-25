#include "headers.h"


int main(void) {
    printf("Метод простой итерации:\n");
    test(sloveSimle);
    printf("Метод скоренного спуска:\n");
    test(sloveFast);
    printf("Метод Зейделя:\n");
    test(sloveYeban);
    return 0;
}