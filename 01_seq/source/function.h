#include <iostream>
#include <math.h>

void integral (const double a, const double b, const double h, double * res){
    int i, n;
    double sum;
    double x;
    n = (int) ((b - a) / h);
    sum = 0.0;
    for ( i = 0 ; i < n; ++i){
        x = a + i * h + h / 2.0;
        sum += sin(x)*h;
    }
    *res = sum;
}