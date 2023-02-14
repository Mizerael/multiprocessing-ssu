#include <string>
#include "method.h"

#define eps 1e-4

double experiment (double *res, std::string arg){
    double start_time, end_time;
    if (arg == "rect"){
        double a = 0; 
        double b = PI;
        double h = 0.0001;
        start_time = clock();
        Rectangle (a,b, h, res, sin);
        end_time = clock();
    }
    else if (arg == "simps"){
        double a = -3; 
        double b = 3;
        double h = 0.0001;
        start_time = clock();
        Simpson (a + eps, b - eps, h, res, Simps_f);
        end_time = clock();
    }
    else if (arg == "db_rect"){
        double a1 = 0; 
        double b1 = 16;
        double h = 0.01;
        start_time = clock();
        db_Rect (a1, b1, h, res, db_f);
        end_time = clock();
    }
    return (end_time - start_time) / CLOCKS_PER_SEC;
}