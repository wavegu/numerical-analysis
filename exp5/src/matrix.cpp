#include "matrix.h"
#include <cmath>
#include <iomanip>
using namespace std;

void freeMatrix(double **m, int width, int height) {
    if (!m)    return;
    for (int i = 0; i < height; i++) {
        if (m[i])
            delete []m[i];
    }
    delete m;
}

Matrix::Matrix(int scale) {
    this->scale = scale;
    matrix = new double*[scale];
    for (int i = 0; i < scale; i++) {
        matrix[i] = new double[scale];
    }
    for (int i = 0; i < scale; i++) {
        for (int j = 0; j < scale; j++) {
            matrix[i][j] = 0.0;
        }
    }
}

Matrix::Matrix(int scale, double **m) {
    this->scale = scale;
    matrix = new double*[scale];
    for (int i = 0; i < scale; i++) {
        matrix[i] = new double[scale];
    }
    for (int i = 0; i < scale; i++) {
        for (int j = 0; j < scale; j++) {
            matrix[i][j] = m[i][j];
        }
    }
}

Matrix::~Matrix() {
    freeMatrix(matrix, scale, scale);
}

void Matrix::display(double **m, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << setiosflags(ios::left)
                << setw(10)
                << setfill(' ')
                <<m[i][j] << ' ';
        }
        cout << endl;
    }
    cout << "-------------------" << endl;
}

void Matrix::display() {
    display(matrix, scale, scale);
}

Matrix Matrix::getReverse() {
    Matrix reverse = Matrix(scale);
    // init tem matrix
    double **tem = new double*[scale];
    for (int i = 0; i < scale; i++) {
        tem[i] = new double[2*scale];
        for (int j = 0; j < scale; j++) {
            tem[i][j] = matrix[i][j];
        }
        for (int j = scale; j < 2*scale; j++) {
            tem[i][j] = 0.0;
            if (j - scale == i) {
                tem[i][j] = 1.0;
            }
        }
    }

    // transform
    for (int i = 0; i < scale; i++) {
        double factor = tem[i][i];
        // normalize the line i
        for (int j = i; j < 2*scale; j++){
            tem[i][j] /= factor;
        }
        // clear the ith element for the lines below, and normalize
        for (int k = i+1; k < scale; k++) {
            double dfactor = tem[k][i];
            for (int j = i; j < 2*scale; j++) {
                tem[k][j] -= dfactor * tem[i][j];
            }
            dfactor = tem[k][i+1];
            for (int j = i+1; j < 2*scale; j++) {
                tem[k][j] /= dfactor;
            }
        }
        // clear lines above
        if (i != scale-1) {
            int baseline = i + 1;
            for (int k = 0; k < baseline; k++) {
                double factor = tem[k][baseline];
                for (int j = 0; j < 2*scale; j++) {
                    tem[k][j] -= factor * tem[baseline][j];
                }
            }
        }
    }
    // set reverse
    for (int i = 0; i < scale; i++) {
        for (int j = 0; j < scale; j++) {
            reverse.matrix[i][j] = tem[i][scale+j];
        }
    }
    // delete tem matrix
    freeMatrix(tem, scale*2, scale);

    return reverse;
}

Matrix Matrix::operator * (Matrix &m) {
    Matrix result = Matrix(scale);
    for (int i = 0; i < scale; i++) {
        for (int j = 0; j < scale; j++) {
            result.matrix[i][j] = 0.0;
            for (int k = 0; k < scale; k++) {
                result.matrix[i][j] += matrix[i][k] * m.matrix[k][j];
            }
        }
    }
    return result;
}

double* Matrix::operator * (double *x) {
    double *ans = new double[scale];
    for (int i = 0; i < scale; i++) {
        ans[i] = 0;
        for (int k = 0; k < scale; k++) {
            ans[i] += matrix[i][k] * x[k];
        }
    }
    return ans;
}

double Matrix::norm(string name) {
    double ans = -99999999;
    if (name == "line") {
        for (int i = 0; i < scale; i++) {
            double sum = 0.0;
            for (int j = 0; j < scale; j++) {
                sum += fabs(matrix[i][j]);
            }
            if (sum > ans)  ans = sum;
        }
    }
    return ans;
}

double Matrix::cond() {
    return getReverse().norm("line") * norm("line");
}

void Matrix::solveLU(double *b, double *ans){
    double **L;
    double **U;
    L = new double*[scale];
    U = new double*[scale];
    for (int i = 0; i < scale; i++) {
        L[i] = new double[scale];
        U[i] = new double[scale];
    }

    for (int i = 0; i < scale; i++) {
        U[0][i] = matrix[0][i];
        L[i][0] = matrix[i][0] / U[0][0];
    }
    for (int r = 1; r < scale; r++) {
        for (int i = r; i < scale; i++) {
            U[r][i] = matrix[r][i];
            for (int k = 0; k < r; k++) {
                U[r][i] -= L[r][k] * U[k][i];
            }
        }
        for (int i = r+1; i < scale; i++) {
            L[i][r] = matrix[i][r];
            for (int k = 0; k < r; k++) {
                L[i][r] -= L[i][k] * U[k][r];
            }
            L[i][r] /= U[r][r];
        }
    }
    // display(L, scale, scale);
    // display(U, scale, scale);

    double y[scale];
    y[0] = b[0];
    for (int i = 1; i < scale; i++) {
        y[i] = b[i];
        for (int k = 0; k < i; k++) {
            y[i] -= L[i][k] * y[k];
        }
    }
    ans[scale-1] = y[scale-1] / U[scale-1][scale-1];
    for (int i = scale-2; i >= 0; i--) {
        ans[i] = y[i];
        for (int k = i+1; k < scale; k++) {
            ans[i] -= U[i][k] * ans[k];
        }
        ans[i] /= U[i][i];
    }

    freeMatrix(L, scale, scale);
    freeMatrix(U, scale, scale);
}

void Matrix::solveCh(double *b, double *ans) {
    // create L
    double **L = new double*[scale];
    for (int i = 0; i < scale; i++) {
        L[i] = new double[scale];
        for (int j = 0; j < scale; j++)
            L[i][j] = 0;
    }

    // calculate L
    for (int j = 0; j < scale; j++) {
        L[j][j] = matrix[j][j];
        for (int k = 0; k < j; k++) {
            L[j][j] -= L[j][k] * L[j][k];
        }
        L[j][j] = sqrt(L[j][j]);
    }
    for (int j = 0; j < scale; j++) {
        for (int i = j+1; i < scale; i++){
            L[i][j] = matrix[i][j];
            for (int k = 0; k < j; k++) {
                L[i][j] -= L[i][k] * L[j][k];
            }
            L[i][j] /= L[j][j];
        }
    }

    double y[scale];
    for (int i = 0; i < scale; i++) {
        y[i] = b[i];
        for (int k = 0; k < i; k++) {
            y[i] -= L[i][k] * y[k];
        }
        y[i] /= L[i][i];
    }

    for (int i = scale-1; i >= 0; i--) {
        ans[i] = b[i];
        for (int k = i; k < scale; k++) {
            ans[i] -= L[k][k] * ans[k];
        }
        ans[i] /= L[i][i];
    }

    // free L
    for (int i = 0; i < scale; i++) {
        delete []L[i];
    }
    delete L;
}
