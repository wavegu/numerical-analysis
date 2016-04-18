#include <fstream>
#include <iostream>
#include <stdlib.h>
#include "spline.cpp"
#include "lagrange.cpp"

using namespace std;

int main() {
    Spline s10 = Spline(10);
    Spline s20 = Spline(20);
    Spline s50 = Spline(50);
    Lagrange l10 = Lagrange(10);
    Lagrange l20 = Lagrange(20);
    Lagrange l50 = Lagrange(50);
    // l10.plot();
    // l20.plot();
    // l50.plot();
    // s10.plot();
    // s20.plot();
    // s50.plot();
    double x = 4.8;
    cout << l10.f(x) << endl;
    cout << l10.getValue(x) << ' ' << l20.getValue(x) << ' ' << l50.getValue(x) << endl;
    cout << s10.getValue(x) << ' ' << s20.getValue(x) << ' ' << s50.getValue(x) << endl;
}
