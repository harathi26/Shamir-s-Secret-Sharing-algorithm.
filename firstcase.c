#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long long decode_value(int base, const char* value) {
    return strtoll(value, NULL, base);
}
double basis_polynomial(int i, int x, int *x_vals, int k) {
    double result = 1.0;
    for (int j = 0; j < k; j++) {
        if (j != i) {
            result *= (double)(x - x_vals[j]) / (x_vals[i] - x_vals[j]);
        }
    }
    return result;
}

double lagrange_interpolation(int *x_vals, long long *y_vals, int k) {
    double secret = 0.0;
    for (int i = 0; i < k; i++) {
        secret += y_vals[i] * basis_polynomial(i, 0, x_vals, k);
    }
    return secret;
}

int main() {
    int n = 4;
    int k = 3;
    int x_vals[] = {1, 2, 3, 6};
    int bases[] = {10, 2, 10, 4};
    char values[][10] = {"4", "111", "12", "213"};
    long long y_vals[4];
    for (int i = 0; i < n; i++) {
        y_vals[i] = decode_value(bases[i], values[i]);
        printf("Point %d: x = %d, y = %lld (decoded from base %d)\n", i + 1, x_vals[i], y_vals[i], bases[i]);
    }

    double secret = lagrange_interpolation(x_vals, y_vals, k);
    printf("Secret (constant term) for test case 1: %lf\n", secret);

    return 0;
}
