#ifndef SPLINE_H
#define SPLINE_H

#include <fstream>
#include <iostream>

class Spline{
private:
    int n;
    double h;
    double *xs;
    double *ys;
    double *ms;
    double *ds;
    double *lam;
    double *miu;

    double pf(double x);
    double ddf(double, double);
    double triple(double x);

    void setXs();
    void setYs();
    void setDs();
    void setLamMiu();
    void calculateMs();

    bool equal(double x, double y);

public:
    Spline(int n);

    ~Spline() {
        delete []xs;
        delete []ys;
        delete []ms;
        delete []ds;
        delete []lam;
        delete []miu;
    }

    void plot();
    double f(double x);
    double getValue(double x);
};

#endif
