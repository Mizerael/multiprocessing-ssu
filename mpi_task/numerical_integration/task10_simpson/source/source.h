#include <iostream>
#include <math.h>

#include <mpi.h>

double f (double x);

void Simpson (const double a, const double b, const double h,
                const int mpi_size, const int mpi_rank, 
                double *res);

void experiment (double *res, const int mpi_size, const int mpi_rank);
