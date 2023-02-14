#include "function.h"

#define PI 3.1415926535897932384626433832795

double experiment (double *res, int h){
    double start_time, end_time;
    double a = 0; 
    double b = PI;
    double dx = (b - a) / h;
    start_time = clock();
    integral (a,b, dx, res);
    end_time = clock();
    return (start_time - end_time) / CLOCKS_PER_SEC;
}