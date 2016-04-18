#include "integeral.h"
#include <iomanip>
#include <cmath>
#include <map>
using namespace std;

#define PI 3.1415926535

Integeral::Integeral(double up, double down, double mdelta) {
    this->up = up;
    this->down = down;
    this->mdelta = mdelta;
    target = exp(1) - 1;
}

double Integeral::f(double x) {
    return exp(x);
}

double Integeral::f_pi(double x) {
    return 4.0 / (1 + x * x);
}

double Integeral::offset(int a, int b) {
    return a * 10000 + b;
}

Rtn Integeral::romberg(){

    map<int, double> table;
    int k = 0;
    double h = up - down;
    table[offset(-1,-1)] = 9999999;
    table[offset(0,0)] = h * (f(up) + f(down)) / 2;
    while (fabs(table[offset(k,k)] - table[offset(k-1,k-1)]) > mdelta) {
        k++;
        double next = table[offset(k-1,0)] / 2;
        for (int i = 0; i < pow(2,k-1); i++) {
            next += h / 2 * f(down + (i+0.5)*h);
        }
        table[offset(k,0)] = next;
        for (int i = 1; i <= k; i++) {
            double tup = table[offset(k-1,i-1)];
            double tdown = table[offset(k,i-1)];
            table[offset(k,i)] = (pow(4,i) * tdown - tup) / (pow(4,i) - 1);
        }
        h /= 2;
        // cout << "k = " << k;
        // cout << " next = " << next;
        // cout << "  answer = " << table[offset(k,k)] << endl;
    }

    // for (int i = 0; i <= k; i++) {
    //     for (int j = 0; j <= i; j++) {
    //         cout << table[offset(i,j)] << '\t';
    //     }
    //     cout << endl;
    // }

    double answer = table[offset(k,k)];
    Rtn rtn;
    rtn.n = k;
    rtn.name = "Romberg";
    rtn.delta = answer - target;
    rtn.answer = answer;
    return rtn;
}

Rtn Integeral::simpson(int n) {

    double h = 1.0 / n;
    double *x = new double[n+1];
    for (int i = 0; i <= n; i++) {
        x[i] = down + h * i;
    }

    double answer = 0.0;
    for (int i = 0; i < n; i++) {
        answer += f(x[i]) + f(x[i+1]) + 4 * f(x[i] + 0.5 * h);
    }
    answer *= h / 6;

    Rtn rtn;
    rtn.n = n;
    rtn.name = "Simpson";
    rtn.delta = answer - target;
    rtn.answer = answer;

    return rtn;
}

Rtn Integeral::trapezoid(int n) {

    double h = 1.0 / n;
    double *x = new double[n+1];
    for (int i = 0; i <= n; i++) {
        x[i] = down + h * i;
    }
    double answer = 0.0;
    for (int i = 0; i < n; i++) {
        answer += f(x[i]) + f(x[i+1]);
    }
    answer *= h / 2;

    Rtn rtn;
    rtn.n = n;
    rtn.name = "Trapezoid";
    rtn.delta = answer - target;
    rtn.answer = answer;

    return rtn;
}

Rtn Integeral::guass(int n) {

    double h = 1.0 / n;
    double *x = new double[n+1];
    for (int i = 0; i <= n; i++) {
        x[i] = down + h * i;
    }
    double answer = 0.0;
    for (int i = 0; i < n; i++) {
        answer += f_pi(x[i] + h * (0.5 - pow(3,0.5)/6)) + f_pi(x[i] + h * (0.5 + pow(3,0.5)/6));
    }
    answer *= h / 2;

    Rtn rtn;
    rtn.n = n;
    rtn.name = "Guass";
    rtn.delta = answer - PI;
    rtn.answer = answer;

    return rtn;
}

Rtn Integeral::iterate(Rtn (Integeral::*func)(int)) {
    Rtn rtn;
    for (int i = 0;;i++) {
        rtn = (this->*func)(i);
        if (rtn.delta < mdelta) {
            break;
        }
    }
    display(rtn);
    return rtn;
}

void Integeral::display(Rtn rtn) {
    cout << rtn.name << endl;
    cout << "n = " << rtn.n << endl;
    cout << setprecision(10) << "delta = " << rtn.delta << endl;
    cout << setprecision(10) << "answer = " << rtn.answer << endl;
    cout << "-----------------------" << endl;
}

void Integeral::findall() {
    Rtn rtn;
    rtn = iterate(&Integeral::simpson);
    rtn = iterate(&Integeral::trapezoid);
    rtn = iterate(&Integeral::guass);
}

int main() {
    Integeral integeral = Integeral(1, 0, 0.0000005);
    int ns = int(pow(2000000*exp(1)/180/16, 0.25));
    int nt = int(pow(exp(1)*1000000/6, 0.5));
    int ng = int(pow(4 * 48000000.0/4320, 0.25));
    Rtn rtn;
    rtn = integeral.simpson(ns);
    integeral.display(rtn);
    rtn = integeral.trapezoid(nt);
    integeral.display(rtn);
    rtn = integeral.guass(ng);
    integeral.display(rtn);
    rtn = integeral.romberg();
    integeral.display(rtn);
    cout << endl << "***************************" << endl << endl;
    integeral.findall();
}
