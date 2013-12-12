#include <iostream>
#include <cstdlib>
using namespace std;

double fx(double x, int n) {
    return x*x - n;
}

double fxDifferential(double x) {
    return 2*x;
}

int main(int argc, char**argv) {
    for (int i; i < argc; ++i) {
        cout << argv[i] << endl;
    }
    int n = atoi(argv[1]);
    cout << n << endl;
    int iterNum = atoi(argv[2]);
    cout << iterNum << endl;
    double x = 0.0;
    for (int i=0; i<iterNum; ++i) {
        x = x - fx(x, n)/fxDifferential(x);
    }
    cout <<"the square root of "<< n << " is:" << x << endl;
}
