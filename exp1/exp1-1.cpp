#include <cmath>
#include <iostream>
using namespace std;

float xn(int k) {
    float ans = 1.0 / k;
    ans = k % 2 == 0 ? -ans : ans;
    return ans;
}

int main() {
    int n = 1;
    float temSum = 0.0;
    float target = 0.693147190546;
    float threshold = 0.5 * 1e-4;
    while (true) {
        temSum += xn(n);
        float delta = temSum - target;
        if (fabs(delta) < threshold) {
            cout << "n = " << n << endl;
            break;
        }
        ++n;
    }
}
