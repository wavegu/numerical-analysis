#ifndef LAGRANGE_H
#define LAGRANGE_H

#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

class Lagrange {

private:

    int n;
    double h;
    double *xs;
    double *ys;

    double lk(int k, double x);
    bool equal(double a, double b);

public:

    Lagrange(int n);

    ~Lagrange() {
        delete xs;
        delete ys;
    }

    double f(double x);
    double getValue(double x);
    void plot();
};


#endif
