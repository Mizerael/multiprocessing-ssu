#include "source/source.h"
#include <chrono>

int main(int argc, char* argv[]){
    MPI_Init(&argc, &argv);
    int i;
    double time, res, min_time, max_time, avg_time, begin, end;
    int rank, size;
    int numbExp = 10;
    
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    for (i = 0; i < numbExp; i++){
        if (0 == rank){
            begin = MPI_Wtime();
        }
        experiment(&res, size, rank);
        if (0 == rank){
            end = MPI_Wtime();
            time = end - begin;
            avg_time += time;
            if (max_time < time) max_time = time;
            if (min_time > time) min_time = time;
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    if (rank == 0){
        std::cout << "result: " << res << '\n';
        std::cout << "exec time: " << avg_time / numbExp << "\nmin time: "; 
        std::cout << min_time << "\nmax time: " << max_time << "\n";
    }
    MPI_Finalize();
    return 0;
}