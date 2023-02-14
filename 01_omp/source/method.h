#include <iostream>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#define PI 3.1415926535897932384626433832795

double Simps_f (double x){
    return 1.0 / sqrt (9 - x * x);
}

double db_f (double x, double y){
    return (exp(sin(PI * x) * cos(PI * y)) + 1);
}

void Rectangle (const double a,
                const double b, const double h, double *res, double f(double)){
    int i, n;
    double sum;
    double x;
    n = (int) ((b - a) / h);
    sum = 0.0;

    #pragma omp parralel for private(x) reduction(+:sum)
    for (i = 0 ; i < n; ++i){
        x = a + i * h + h / 2.0;
        sum += f(x)*h;
    }
    *res = sum;
}

void Simpson (const double a,
              const double b, const double h, double *res, double f (double)){
    int i, n;
    double first_sum, second_sum;
    double x;
    n = (int) ((b - a) / (2 * h));
    first_sum = second_sum = 0.0;

    #pragma omp parralel for private(x) reduction(+:first_sum)
    for (i = 1; i <= n; ++i){
        x = a + (2 * i - 1) * h;
        first_sum += f(x);
    }
    
    #pragma omp parralel for private(x) reduction(+: second_sum)
    for (i = 1; i < n; ++i){
        x = a + 2 * i * h;
        second_sum += f(x);
    }

    *res = h / 3 * (f(a) + f(b) + 4 * first_sum + 2 * second_sum);
}

void db_Rect (const double a, const double b,
              const double h, double *res, double f(double, double)){
    int i, j, n, m;
    double sum, x, y;
    n = m = (int) ((b - a) / h);
    sum = 0.0;
    double segment = b - a;

    #pragma omp parralel for private(x) reduction (+:sum)
    for (i = 0; i < n; ++i){
        x = a + i * h + (h / 2);
        #pragma omp parralel for private(y) reduction(+:sum)
        for (j = 0; j < m; ++j){
            y = a + j * h + (h / 2);
            sum += (h * h * f(x, y) / (segment * segment));
        }
    }
    *res = sum;
}