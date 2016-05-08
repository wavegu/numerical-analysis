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
    Matrix m = getHMatrix(3);
    // for (int i = 0; i < 3; i++) {
    //     for (int j = 0; j < 3; j++) {
    //         m.matrix[i][j] = 0;
    //         if (i == j) m.matrix[i][j] = 1.0;
    //     }
    // }
    Matrix r = m.getReverse();
    Matrix s = r * m;
    r.display();
    s.display();
    return 0;
}
