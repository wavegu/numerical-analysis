#include "matrix.cpp"
using namespace std;

Matrix getHMatrix(int scale) {
    Matrix m = Matrix(scale);
    for (int i = 0; i < scale; i++) {
        for (int j = 0; j < scale; j++) {
            m.matrix[i][j] = 1.0 / (double)(i+j+1);
        }
    }
    return m;
}

double norm(double *x, int n) {
    double ans = -99999;
    for (int i = 0; i < n; i++)
        if (fabs(x[i]) > ans)
            ans = fabs(x[i]);
    return ans;
}

double solve(int n, double dis=0) {
    // cout << "------------ solve " << n << " ----------------" << endl;
    // cout << "dis = " << dis << endl;
    Matrix m10 = getHMatrix(10);
    double x[n];
    double x_hat[n];
    double x_del[n];
    double *b = NULL;
    double *b_hat = NULL;
    double r[n];
    for (int i = 0; i < n; i++)
        x[i] = 1;
    b = m10 * x;
    for (int i = 0; i < n; i++)
        b[i] += dis;
    m10.solveLU(b, x_hat);
    for (int i = 0; i < n; i++)
        b[i] -= dis;
    b_hat = m10 * x_hat;
    for (int i = 0; i < n; i++) {
        r[i] = b[i] - b_hat[i];
        x_del[i] = x_hat[i] - x[i];
    }

    double norm_r = norm(r, n);
    double norm_x = norm(x_del, n);
    // cout << "Norm(r) = " << norm_r << endl;
    // cout << "Norm(x) = " << norm_x << endl;

    return norm_x;
}

int main() {
    /* 1 */
    Matrix m3 = getHMatrix(3);
    Matrix m4 = getHMatrix(4);
    cout << "cond(" << 3 << ") = " << m3.cond() << endl;
    cout << "cond(" << 4 << ") = " << m4.cond() << endl;


    /* 2 */
    for (int i = 5; i < 20; i++) {
        cout << i << '\t' << solve(i) << endl;
    }

    return 0;
}
