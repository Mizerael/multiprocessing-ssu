#include <iostream>
#include <math.h>

#ifdef _OPENMP
    #include <omp.h>
#endif

#define PI 3.1415926535897932384626433832795

double Simps_f (double x){
    return 1.0 / sqrt (9 - x * x);
}

double di_f (double x, double y){
    return (exp(sin(PI * x) * cos(PI * y)) + 1);
}

void Rectangle (const double a, const double b, const double h, 
                double *res, double f(double)){
    int n;
    double sum = 0.0;
    double x;
    n = (int) ((b - a) / h);
    #pragma omp parallel for private(x) reduction(+:sum)
    for (int i = 0 ; i < n; ++i){
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

    #pragma omp parallel for private(x) reduction(+:first_sum)
    for (i = 1; i <= n; ++i){
        x = a + (2 * i - 1) * h;
        first_sum += f(x);
    }
    
    #pragma omp parallel for private(x) reduction(+: second_sum)
    for (i = 1; i < n; ++i){
        x = a + 2 * i * h;
        second_sum += f(x);
    }

    *res = h / 3 * (f(a) + f(b) + 4 * first_sum + 2 * second_sum);
}

void di_Rect (const double a, const double b,
              const double h, double *res, double f(double, double)){
    int i, j, n, m;
    double sum, x, y;
    n = m = (int) ((b - a) / h);
    sum = 0.0;
    double segment = b - a;

    #pragma omp parallel for private(x) reduction (+:sum)
    for (i = 0; i < n; ++i){
        x = a + i * h + (h / 2);
        // #pragma omp parallel for private(y) reduction(+:sum)
        for (j = 0; j < m; ++j){
            y = a + j * h + (h / 2);
            sum += (h * h * f(x, y) / (segment * segment));
        }
    }
    *res = sum;
}

// realization method Monte-Karlo for rectangular areas
void di_Monte_Karlo (const double a, const double b, const double c,
                     const double d, const int N, double *res,
                     double f(double, double)){   
    srand(time(NULL));
    int i;
    double sum = 0.0;
    double x_i, y_i;
    double segment_x = b - a;
    double segment_y = d - c;

    #pragma omp parallel for private(x_i, y_i) reduction (+:sum)
    for (i = 0; i < N; ++i){
        x_i = (double) (rand()) / RAND_MAX * (segment_x + 1) + a;
        y_i = (double) (rand()) / RAND_MAX * (segment_y + 1) + c;
        sum += f (x_i, y_i);
    }
    *res = sum / N;
}