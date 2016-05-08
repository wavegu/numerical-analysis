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

int main() {
    Matrix m3 = getHMatrix(3);
    Matrix m4 = getHMatrix(4);

    cout << m3.cond() << endl;
    cout << m4.cond() << endl;
    return 0;
}
