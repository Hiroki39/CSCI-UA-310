#include <iostream>

using namespace std;

// credit GeeksForGeeks for initial code

void multiply(long long F[2][2], long long M[2][2], long long MOD) {
    long long x = (F[0][0] * M[0][0] + F[0][1] * M[1][0]) % MOD;
    long long y = (F[0][0] * M[0][1] + F[0][1] * M[1][1]) % MOD;
    long long z = (F[1][0] * M[0][0] + F[1][1] * M[1][0]) % MOD;
    long long w = (F[1][0] * M[0][1] + F[1][1] * M[1][1]) % MOD;

    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void power(long long F[2][2], long long n, long long MOD) {
    if (n == 0 || n == 1) return;
    long long M[2][2] = {{1, 1}, {1, 0}};

    power(F, n / 2, MOD);
    multiply(F, F, MOD);

    if (n % 2 != 0) multiply(F, M, MOD);
}

long long fib(long long n, long long MOD) {
    long long F[2][2] = {{1, 1}, {1, 0}};
    if (n == 0) return 0;
    power(F, n - 1, MOD);

    return F[0][0];
}

int main() {
    long long n, m;
    cin >> n >> m;
    cout << fib(n, m) << endl;
}
