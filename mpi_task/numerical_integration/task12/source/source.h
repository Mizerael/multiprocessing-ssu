#include <iostream>
#include <math.h>

#include <mpi.h>

double f (double x);

void di_Monte_Karlo (const double a, const double b, const double c,
                     const double d, const int N, const int mpi_rank,
                     const int mpi_size, double *res, double f(double, double));

void experiment (double *res, const int mpi_size, const int mpi_rank);
