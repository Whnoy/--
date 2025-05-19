#ifndef MATRIX_H
#define MATRIX_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-14

// Структура для хранения операций
typedef struct {
    unsigned swaps;
    double mults;
    double norm;
} MatActs;

// Структура для матрицы
typedef struct {
    double **matrix;
    unsigned rows;
    unsigned cols;
    MatActs acts;
} Matrix;

// Создание и освобождение памяти
double **createMatrix(unsigned n, unsigned m);
int freeMatrix(double **matrix, unsigned n, unsigned m);
int freeSMatrix(Matrix matrix);

// Генерация случайного числа с плавучей точкой в диапазоне [-max, max]
double randab(unsigned max);

//Создание матрицы
Matrix EMatrix(unsigned n);
Matrix createRow(unsigned n, const double *dub);
Matrix createCol(unsigned n, const double *dub);
Matrix copyMatrix(const Matrix matrix, Matrix *out);

//Чтение и вывод матрицы
Matrix readMatrix(FILE *file);
void drawMatrix(const double **A, unsigned n, unsigned m, FILE *output);

//Элементарные операции над матрицами
void swapRows(double **A, unsigned n, unsigned m, MatActs *acts);
void multiplyRow(double **A, unsigned row, double factor, unsigned m, MatActs *acts);
void multiplyMatrix(double **A, unsigned n, unsigned m, double factor, MatActs *acts);
void addRows(double **matrix, unsigned cols, double factor, unsigned in, unsigned out);

//Матричная арифметика
Matrix multMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm, Matrix *C);
Matrix addMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm, Matrix *C);
Matrix subMatrix(double **A, unsigned an, unsigned am, double **B, unsigned bn, unsigned bm, Matrix *C);

//Приведение матрицы к нормальному виду
void normiseMatrix(double **A, unsigned n, unsigned m, MatActs *acts);

//Приведение матрицы к треугольному виду
MatActs rungByGauss(double **A, unsigned n, unsigned m);
MatActs rungByantiGauss(double **A, unsigned n, unsigned m);

//Вспомогательные функции
int _findRowMax(double **A, unsigned n, unsigned m, unsigned row);
int _findRowAntiMax(double **A, unsigned n, unsigned m, unsigned row);

//Высокоуровневые функции
long double findMatDet(double **A, unsigned n, MatActs *acts);
int findMatRank(double **A, unsigned n, unsigned m, MatActs *acts);
int sloveSLE(double **A, double *B, unsigned n, double *x);
Matrix findInv(double **A, unsigned n, MatActs *acts);

#endif // MATRIX_H
