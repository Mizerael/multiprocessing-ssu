#include "source.h"

double f (double x){
    return 1.0 / sqrt (9.0 - x * x);
}

void Simpson (const double a, const double b, const double h, 
                const int mpi_size, const int mpi_rank, 
                double *res){
    int n;
    double x;
    double first_sum, second_sum;
    double proc_first = 0.0;
    double proc_second = 0.0;
    if (0 == mpi_rank){
        first_sum = 0.0;
        second_sum = 0.0;
        n = (int) ((b - a) / (2 * h));
    }

    MPI_Bcast(&n, mpi_size, MPI_INT, 0, MPI_COMM_WORLD);
   
    for (int i = mpi_rank; i < n;  i += mpi_size){
        x = a + (2 * i - 1) * h;
        proc_first += f(x);
    }

    MPI_Reduce(&proc_first, &first_sum, mpi_size, MPI_DOUBLE, MPI_SUM, 0,
                MPI_COMM_WORLD);
    
    for (int i = mpi_rank; i < n;  i += mpi_size){
        x = a + 2 * i * h;
        proc_second += f(x);
    }

    MPI_Reduce(&proc_second, &second_sum, mpi_size, MPI_DOUBLE, MPI_SUM, 0,
                MPI_COMM_WORLD);

    if (0 == mpi_rank){
        *res = h / 3 * (f(a) + f(b) + 4 * first_sum + 2 * second_sum);
        return;
    }
}

void experiment(double *res, const int mpi_size, const int mpi_rank){
        double a = -2.99; 
        double b = 2.99;
        double h = 0.001;
        Simpson (a, b, h, mpi_size, mpi_rank, res);
}