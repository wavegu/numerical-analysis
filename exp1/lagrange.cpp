#include "lagrange.h"
using namespace std;

#define EPSILON 0.0000000001


bool Lagrange::equal(double a, double b) {
    double delta = a - b;
    delta = delta < 0 ? -delta : delta;
    if (delta < EPSILON)
        return true;
    return false;
}

double Lagrange::lk(int k, double x) {
    double numerator = 1.0;
    double denominator = 1.0;
    for (int i = 0; i <= n; i++) {
        if (i == k) continue;
        numerator *= (x - xs[i]);
        denominator *= (xs[k] - xs[i]);
    }
    return numerator / denominator;
}

Lagrange::Lagrange(int n) {
    this->n = n;
    xs = new double[n+1];
    ys = new double[n+1];
    h = 10.0 / n;
    for (int i = 0; i <= n; i++) {
        xs[i] = -5 + i * h;
        ys[i] = f(xs[i]);
    }
}

double Lagrange::f(double x) {
    return 1.0 / (1 + 16 * x * x);
}


double Lagrange::getValue(double x) {
    for (int i = 0; i <= n; i++) {
        if (equal(x, xs[i]))
        {
            return ys[i];
        }
    }
    double ans = 0.0;
    for (int i = 0; i <= n; i++) {
        ans += ys[i] * lk(i, x);
    }

    return ans;
}

void Lagrange::plot() {

    string f_data_filename = "runge.txt";
    string l_data_filename = "lagrange_" + to_string(n) + ".txt";
    ofstream l_out(l_data_filename.c_str());
    ofstream f_out(f_data_filename.c_str());

    for (double x = -5.0; x < 5.0; x += 0.001) {
        l_out << x << ' ';
        f_out << x << ' ';
    }
    l_out << endl;
    f_out << endl;

    for (double x = -5.0; x < 5.0; x += 0.001) {
        l_out << getValue(x) << ' ';
        f_out << f(x) << ' ';
    }
    l_out << endl;
    f_out << endl;

    string cmd = "python plot.py " + l_data_filename;
    system(cmd.c_str());
    cmd = "python plot.py " + f_data_filename;
    system(cmd.c_str());
}
