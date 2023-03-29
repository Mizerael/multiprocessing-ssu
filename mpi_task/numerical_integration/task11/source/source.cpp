#include "source.h"

double f (double x, double y){
    return (exp(sin(M_PI * x) * cos(M_PI * y)) + 1);
}

void di_Rect (const double a, const double b, const double h, 
                const int mpi_size, const int mpi_rank, 
                double *res){
    int i, j, n, m;
    double sum, x, y;
    double segment = b - a;
    double t_res;
    if (0 == mpi_rank)
       n = m = (int) ((b - a) / h);

    MPI_Bcast(&n, mpi_size, MPI_INT, 0, MPI_COMM_WORLD);

    for (int i = mpi_rank; i < n; i += mpi_size){
        x = a + i * h + (h / 2);
        for (int j = 0; j < m; ++j){
             y = a + j * h + (h / 2);
            sum += (h * h * f(x, y) / (segment * segment));
        }
    }

    MPI_Reduce(&sum, res, mpi_size, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
}

void experiment(double *res, const int mpi_size, const int mpi_rank){
        double a = -2.99; 
        double b = 2.99;
        double h = 0.01;
        di_Rect (a, b, h, mpi_size, mpi_rank, res);
}