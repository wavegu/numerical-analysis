#include "spline.h"
using namespace std;

#define EPSILON 0.0000000001

Spline::Spline(int n) {
    this->n = n;
    h = 10.0 / n;
    xs = new double[n+1];
    ys = new double[n+1];
    ms = new double[n+1];
    ds = new double[n+1];
    lam = new double[n+1];
    miu = new double[n+1];
    setXs();
    setYs();
    setDs();
    setLamMiu();
    calculateMs();
}

double Spline::f(double x) {
    return 1.0 / (x * x * 16 + 1);
}

double Spline::pf(double x) {
    return (-32.0 * x) / ((x * x * 16 + 1) * (x * x * 16 + 1));
}

double Spline::ddf(double x1, double x2) {
    return (f(x2) - f(x1)) / (x2 - x1);
}

double Spline::triple(double x) {
    double ans = x;
    ans *= x * x;
    return ans;
}

void Spline::setXs() {
    for (int i = 0; i <= n; i++) {
        xs[i] = -5.0 + i * h;
    }
}

void Spline::setYs() {
    for (int i = 0; i <= n; i++) {
        ys[i] = f(xs[i]);
    }
}

void Spline::setDs() {
    ds[0] = 6.0 * (+ ddf(xs[0]  , xs[1]) - pf(xs[0])) / h;
    ds[n] = 6.0 * (- ddf(xs[n-1], xs[n]) + pf(xs[n])) / h;
    for (int i = 1; i < n; i++) {
        ds[i] = 3.0 * (ddf(xs[i], xs[i+1]) - ddf(xs[i-1], xs[i])) / h;
    }
}

void Spline::setLamMiu() {
    for (int i = 0; i <= n; i++) {
        lam[i] = miu[i] = 0.5;
    }
    lam[0] = miu[n] = 1.0;
}

void Spline::calculateMs() {
    double *y = new double[n+1];
    double *beta = new double[n];

    beta[0] = lam[0] / 2.0;
    for (int i = 1; i < n; i++) {
        beta[i] = lam[i] / (2 - miu[i] * beta[i-1]);
    }

    y[0] = ds[0] / 2.0;
    for (int i = 1; i <= n; i++) {
        y[i] = (ds[i] - miu[i] * y[i-1]) / (2.0 - miu[i] * beta[i-1]);
    }

    ms[n] = y[n];
    for (int i = n - 1; i > -1; i--) {
        ms[i] = y[i] - beta[i] * ms[i+1];
    }

    cout << "M:" << endl;
    for (int i = 0; i <= n; i++)
        cout << ms[i] << ' ';
    cout << endl;

    delete []y;
    delete []beta;
}

bool Spline::equal(double a, double b) {
    double delta = a - b;
    delta = delta < 0 ? -delta : delta;
    if (delta < EPSILON)
        return true;
    return false;
}

double Spline::getValue(double x) {
    if (x < -5.0 || x > 5.0) {
        return 0.0;
    }

    for (int i = 0; i <= n; i++) {
        if (equal(x, xs[i]))    return ys[i];
        if (x < xs[i]) {
            int j = i - 1;
            double ans = 0.0;
            ans += ms[j] * triple(xs[j+1] - x) / (6.0 * h);
            ans += ms[j+1] * triple(x - xs[j]) / (6.0 * h);
            ans += (ys[j] - ms[j] * h * h / 6.0) * (xs[j+1] - x) / h;
            ans += (ys[j+1] - ms[j+1] * h * h / 6.0) * (x - xs[j]) / h;
            return ans;
        }
    }

    return 0.0;
}


void Spline::plot() {

    string f_data_filename = "runge.txt";
    string l_data_filename = "spline_" + to_string(n) + ".txt";
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
