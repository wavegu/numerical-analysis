#include "matrix.cpp"
#include <fstream>
#include <cstdlib>
#include <stdlib.h>
using namespace std;

int size = 7;
double x[7] = {-1.0, -0.5, 0.0, 0.5, 1.0, 1.5, 2.0};
double y[7] = {-4.447, -0.452, 0.551, 0.048, -0.447, 0.549, 4.552};
double w[7] = {1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};

// int size = 5;
// double x[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
// double y[5] = {4, 4.5, 6, 8, 8.5};
// double w[5] = {2, 1, 3, 1, 1};

double power(double x, int times) {
    if (times == 0)
        return 1.0;
    double answer = 1.0;
    for (int i = 0; i < times; i++) {
        answer *= x;
    }
    return answer;
}

double phi(int a, int b) {
    double answer = 0.0;
    for (int i = 0; i < size; i++) {
        answer += w[i] * power(x[i], a+b);
    }
    // cout << "phi(" << a << ',' << b << ") = " << answer << endl;
    return answer;
}

double phi_f(int a) {
    double answer = 0.0;
    for (int j = 0; j < size; j++) {
        answer += w[j] * power(x[j],a) * y[j];
    }
    // cout << "phi_f(" << a << ") = " << answer << endl;
    return answer;
}

Matrix getMatrix(int n) {
    int height = n + 1;
    vector< vector<double> > m;
    for (int i = 0; i < height; i++) {
        vector<double> v;
        for (int j = 0; j < height; j++) {
            v.push_back(phi(i,j));
        }
        v.push_back(phi_f(i));
        m.push_back(v);
    }
    return Matrix(m);
}


int main() {

    ofstream out("../result/raw.txt");
    for (int i = 0; i < 7; i++) {
        out << x[i] << ' ';
    }
    out << endl;
    for (int i = 0; i < 7; i++) {
        out << y[i] << ' ';
    }
    out << endl;

    for (int n = 1; n < 4; n++) {
        Matrix matrix = getMatrix(n);
        double *answer = matrix.solute();

        string filename = "../result/" + to_string(n) + ".txt";
        ofstream fout(filename);
        vector<double> nys;

        for (double nx = x[0]; nx <= x[6]; nx+=0.0001) {
            fout << nx << ' ';
            double ny = 0.0;
            for (int j = 0; j <= n; j++) {
                ny += answer[j] * power(nx, j);
            }
            nys.push_back(ny);
        }
        fout << endl;
        vector<double>::iterator it;
        for (it = nys.begin(); it != nys.end(); it++) {
            fout << *it << ' ';
        }
        fout << endl;

        string cmd = "python plot.py " + filename;
        system(cmd.c_str());

        cout << "n = " << endl;
        for (int i = 0; i <= n; i++) {
            cout << answer[i] << ' ' << endl;
        }
        cout << endl;
    }
    return 0;
}
