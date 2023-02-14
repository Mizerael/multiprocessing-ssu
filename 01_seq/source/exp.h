#include "function.h"

#define PI 3.1415926535897932384626433832795

double experiment (double *res){
    double start_time, end_time;
    double a = 0; 
    double b = PI;
    double h = 0.001;
    start_time = clock();
    integral (a,b, h, res);
    end_time = clock();
    return (start_time - end_time) / CLOCKS_PER_SEC;
}