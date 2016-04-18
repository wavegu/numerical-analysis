#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <vector>

class Matrix{
private:
    int width;
    int height;
    double *answer;
    void findPivot(int line);
    void normalize(int line);
    void eliminate(int line);
    std::vector< std::vector<double> > matrix;

public:
    Matrix(std::vector< std::vector<double> > m);
    ~Matrix() { delete []answer; }
    int getHeight() { return height; }
    
    void display();
    double *solute();
};

#endif
