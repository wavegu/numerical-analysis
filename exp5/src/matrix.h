#ifndef MATRIX_H
#define MATRIX_H
#include <cstring>
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

    double cond();
    double norm(std::string name);
    Matrix getReverse();
    Matrix operator * (Matrix &m);
    double* operator * (double *x);
    void solveLU(double *b, double *ans);
    void solveCh(double *b, double *ans);
};

#endif
