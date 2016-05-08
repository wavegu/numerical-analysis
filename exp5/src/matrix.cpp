#include "matrix.h"
#include <iomanip>
using namespace std;

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
    if (!matrix)    return;
    for (int i = 0; i < scale; i++) {
        if (matrix[i])
            delete []matrix[i];
    }
    delete matrix;
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
    for (int i = 0; i < scale; i++) {
        delete []tem[i];
    }
    delete tem;

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
