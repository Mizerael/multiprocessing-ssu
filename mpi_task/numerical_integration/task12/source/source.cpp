#include "source.h"

double f (double x, double y){
    return (exp(sin(M_PI * x) * cos(M_PI * y)) + 1);
}

void di_Monte_Karlo (const double a, const double b, const double c,
                     const double d, const int N, const int mpi_rank,
                     const int mpi_size, double *res, double f(double, double)){   
    srand(time(NULL));
    int i;
    double sum = 0.0;
    double x_i, y_i;
    double segment_x = b - a;
    double segment_y = d - c;

    for (int i = mpi_rank; i < N; i += mpi_size){
        x_i = (double) (rand()) / RAND_MAX * (segment_x + 1) + a;
        y_i = (double) (rand()) / RAND_MAX * (segment_y + 1) + c;
        sum += f (x_i, y_i);
    }

    MPI_Reduce(&sum, res, mpi_size, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if (0 == mpi_rank)
        *res /= N;
}

void experiment(double *res, const int mpi_size, const int mpi_rank){
        double a = 0; 
        double b = 16;
        double c = 0; 
        double d = 16;
        double n = 100000;
        di_Monte_Karlo(a, b, c, d, n, mpi_rank, mpi_size, res, f);
}