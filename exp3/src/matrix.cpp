#include "matrix.h"
#include <cmath>
using namespace std;

#define MIN_DOUBLE 0.00000001

Matrix::Matrix(std::vector<std::vector<double> > m) {
    this->matrix = m;
    width = m[0].size();
    height = m.size();
    answer = new double[height];
}

void Matrix::display() {
    cout << height << " * " << width << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << matrix[i][j] << ' ';
        }
        cout << endl;
    }
}

void Matrix::findPivot(int line) {
    int pivotLine = line;
    if (matrix[line][line] < 0.0) {
        for (int j = line; j < width; j++) {
            matrix[line][j] = -matrix[line][j];
        }
    }
    for (int i = line + 1; i < height; i++) {
        if (matrix[i][line] < 0.0) {
            for (int j = line; j < width; j++) {
                matrix[i][j] = -matrix[i][j];
            }
        }
        if (matrix[i][line] > matrix[pivotLine][line]) {
            swap(matrix[pivotLine], matrix[i]);
            pivotLine = i;
        }
    }
}

void Matrix::normalize(int line) {
    if (line > height - 1)
        return;
    double first = matrix[line][line];
    if (fabs(first) < MIN_DOUBLE)
        return;
    for (int i = line; i < width; i++)
        matrix[line][i] /= first;
}

void Matrix::eliminate(int line) {
    for (int i = line + 1; i < height; i++) {
        double times = matrix[i][line];
        for (int col = line; col < width; col++) {
            matrix[i][col] -= times * matrix[line][col];
        }
    }
}

double *Matrix::solute() {
    for (int i = 0; i < height - 1; i++) {
        findPivot(i);
        normalize(i);
        eliminate(i);
    }
    normalize(height-1);

    answer[height-1] = matrix[height-1][width-1];
    for (int line = height - 2; line > -1; line--) {
        answer[line] = matrix[line][width-1];
        for (int col = width - 2; col > line; col--) {
            answer[line] -= ( matrix[line][col] * answer[col] );
        }
    }

    return answer;
}
