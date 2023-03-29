#include "source.h"

double f (double x){
    return 1.0 / sqrt (9 - x * x);
}

void Rectangle (const double a, const double b, const double h, 
                const int mpi_size, const int mpi_rank, 
                double *res){
    int n;
    double sum = 0.0;
    double x;
    if (0 == mpi_rank)
        n = (int) ((b - a) / h);

    MPI_Bcast(&n, mpi_size, MPI_INT, 0, MPI_COMM_WORLD);
    
    for (int i = mpi_rank; i < n;  i += mpi_size){
        x = a + i * h + h / 2.0;
        sum += f(x)*h;
    }
    
    MPI_Reduce(&sum, res, mpi_size, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
}

void experiment(double *res, const int mpi_size, const int mpi_rank){
        double a = -3 + 1e-5; 
        double b = 3 - 1e-5;
        double h = 0.0001;
        Rectangle (a, b, h, mpi_size, mpi_rank, res);

}