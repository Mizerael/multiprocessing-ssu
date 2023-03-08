#include "src/src.h"
#include "../utils/test.h"


int main(int argc, char *argv[]) {
    std::vector<char *> cfg;
    for (int i = 1; i < argc; i++) 
        cfg.push_back(argv[i]);
    double* pMatrix; // The matrix of the linear system
    double* pVector; // The right parts of the linear system
    double* pResult; // The result vector
    int Size; // The sizes of the initial matrix and the vector
    double start, finish, duration;
    for (auto it = cfg.begin(); it != cfg.end(); it++){
        Size = atoi(*it);
        // Memory allocation and definition of objects' elements
        ProcessInitialization(pMatrix, pVector, pResult, Size);
        // The matrix and the vector output
        // printf("Initial Matrix \n");
        // PrintMatrix(pMatrix, Size, Size);
        // printf("Initial Vector \n");
        // PrintVector(pVector, Size);
        // Execution of Gauss algorithm
        auto begin = std::chrono::steady_clock::now();
        start = clock();
        SerialResultCalculation(pMatrix, pVector, pResult, Size);
        finish = clock();
        auto end = std::chrono::steady_clock::now();
        duration = (finish-start) / CLOCKS_PER_SEC;
        auto ms =
             std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        // Printing the result vector
        // printf ("\n Result Vector: \n");
        // PrintVector(pResult, Size);
        // Testing the result
        // TestResult(pMatrix, pVector, pResult, Size);
        // Printing the execution time of Gauss method
        printf("\n processor time of execution for %d elements: %f\n",
               Size, duration);
        printf("\n real time of execution for %d elements: %f\n",
               Size, ms.count() * 1e-3);
        // Computational process termination
        ProcessTermination(pMatrix, pVector, pResult);
    }
    return 0;
}