#include <iostream>
#include <cmath>
#include <map>
using namespace std;

#define PI 3.14159265
typedef double (*rawFunc)(double);

double h(int k) {
    return 1.0 / pow(2, k);
}

double f(double x) {
    return exp(-x) * 2 / pow(PI, 0.5);
}

double offset(int a, int b) {
    return a * 10000 + b;
}

double romberg(double up, double down, double mdelta){
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
        cout << "k = " << k;
        cout << " next = " << next;
        cout << "  answer = " << table[offset(k,k)] << endl;
    }

    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= i; j++) {
            cout << table[offset(i,j)] << '\t';
        }
        cout << endl;
    }

    return 1.0;
}

int main() {
    romberg(1, 0, 0.00001);
}
