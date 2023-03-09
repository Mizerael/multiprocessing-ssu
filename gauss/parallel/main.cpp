#include "src/src.h"
#include "../utils/test.h"

int main(int argc, char *argv[]) {
    std::vector<char *> cfg;
    for (int i = 1; i < argc; i++) 
        cfg.push_back(argv[i]);
    double* pMatrix; // The matrix of the linear system
    double* pVector; // The right parts of the linear system
    double* pResult; // The result vector
    int Size; // The size of the matrix and the vectors
    for (auto it = cfg.begin(); it != cfg.end(); it++) {
        if ((std::string)*it == "-sl") {
            Size = 5;
            ProcessInitialization(pMatrix, pVector, pResult, Size, true);
            printf ("solution SLAU\n");
            PrintMatrix(pMatrix, Size, Size);

            printf("Recalculated Vector \n");
            PrintVector(pVector, Size);
            
        } else {
            Size = atoi(*it);
            // Data initialization
            ProcessInitialization(pMatrix, pVector, pResult, Size);
            // The matrix and the vector output
            // printf ("Initial Matrix \n");
            // PrintMatrix(pMatrix, Size, Size);
            // printf("Initial Vector \n");
            // PrintVector(pVector, Size);

            // ParallelResultCalculation(pMatrix, pVector, pResult, Size);
            // // The matrix and the vector output
            // printf ("Recalculated Matrix \n");
            // PrintMatrix(pMatrix, Size, Size);

            // printf("Recalculated Vector \n");
            // PrintVector(pVector, Size);
            
            // printf("\nResult Vector \n");
            // PrintVector(pResult, Size);
        }
        double start, finish, duration;
        auto begin = std::chrono::steady_clock::now();
        Seidel_alghoritm(pMatrix, pVector, pResult, Size);
        // ParallelResultCalculation(pMatrix, pVector, pResult, Size);
        auto end = std::chrono::steady_clock::now();
        auto ms =
            std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        if ((std::string)*it == "-sl"){
            printf("\nResult Vector \n");
            PrintVector(pResult, Size);
            TestResult(pMatrix, pVector, pResult, Size);
        }
        // Testing the result
        //  TestResult(pMatrix, pVector, pResult, Size);
        // Printing the time spent by parallel Gauss algorithm
        printf("\n real time of execution for %d element: %f\n",
            Size ,ms.count() * 1e-3);
        // Program termination
        ProcessTermination(pMatrix, pVector, pResult);
    }
    return 0;
}