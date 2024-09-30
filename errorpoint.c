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
double lagrange_interpolation_at_x(int *x_vals, long long *y_vals, int k, int x) {
    double result = 0.0;
    for (int i = 0; i < k; i++) {
        result += y_vals[i] * basis_polynomial(i, x, x_vals, k);
    }
    return result;
}
void find_wrong_points(int *x_vals, long long *y_vals, int n, int k) {
    printf("Checking for wrong points:\n");
    for (int i = k; i < n; i++) {
        double interpolated_y = lagrange_interpolation_at_x(x_vals, y_vals, k, x_vals[i]);
        if (fabs(y_vals[i] - interpolated_y) > 1e-6) {
            printf("Wrong point found: (%d, %lld)\n", x_vals[i], y_vals[i]);
        }
    }
}

int main() {
    int n = 9;
    int k = 6;
    int x_vals[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int bases[] = {10, 16, 12, 11, 16, 10, 14, 9, 8};
    char values[][20] = {
        "28735619723837", "1A228867F0CA", "32811A4AA0B7B", "917978721331A",
        "1A22886782E1", "28735619654702", "71AB5070CC4B", "122662581541670", "642121030037605"
    };
    long long y_vals[9];
    for (int i = 0; i < n; i++) {
        y_vals[i] = decode_value(bases[i], values[i]);
        printf("Point %d: x = %d, y = %lld (decoded from base %d)\n", i + 1, x_vals[i], y_vals[i], bases[i]);
    }
    double secret = lagrange_interpolation_at_x(x_vals, y_vals, k, 0);
    printf("Secret (constant term) for test case 2: %lf\n", secret);
    find_wrong_points(x_vals, y_vals, n, k);

    return 0;
}
