#include <iostream>
#include <cstring>

struct Rtn{
    int n;
    double delta;
    double answer;
    std::string name;
};

class Integeral{
private:
    double up;
    double down;
    double mdelta;
    double target;
    double f(double x);
    double f_pi(double x);
    double offset(int a, int b);

public:
    Integeral(double up, double down, double mdelta);
    Rtn romberg();
    Rtn simpson(int n);
    Rtn trapezoid(int n);
    Rtn guass(int n);
    Rtn iterate(Rtn (Integeral::*func)(int));
    void display(Rtn rtn);
    void findall();
};
