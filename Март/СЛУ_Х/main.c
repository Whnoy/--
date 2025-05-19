#include "headers.h"


int main(void) {
    printf("Метод простой итерации:\n");
    test(sloveSimle);
    printf("Метод скоренного спуска:\n");
    test(sloveFast);
    return 0;
}