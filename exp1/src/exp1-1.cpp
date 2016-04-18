#include <cmath>
#include <iostream>
using namespace std;

double xn(int k) {
    double ans = 1.0 / k;
    ans = k % 2 == 0 ? -ans : ans;
    return ans;
}

int main() {
    int n = 1;
    double temSum = 0.0;
    double target = 0.693147190546;
    double threshold = 0.5 * 1e-4;
    while (true) {
        temSum += xn(n);
        double delta = temSum - target;
        if (fabs(delta) < threshold) {
            cout << "n = " << n << endl;
            break;
        }
        ++n;
    }
}
