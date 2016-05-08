#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

class Matrix{
public:
    int scale;
    double **matrix;
    Matrix(int scale);
    Matrix(int scale, double **m);
    ~Matrix();
    void display();
    void display(double **m, int width, int height);
    Matrix getReverse();
    Matrix operator * (Matrix &m);
};

#endif
