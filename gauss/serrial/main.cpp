#include "src/src.h"
#include "../utils/test.h"


int main() {
    double* pMatrix; // The matrix of the linear system
    double* pVector; // The right parts of the linear system
    double* pResult; // The result vector
    int Size; // The sizes of the initial matrix and the vector
    double start, finish, duration;
    printf("Serial Gauss algorithm for solving linear systems\n");
    // Memory allocation and definition of objects' elements
    ProcessInitialization(pMatrix, pVector, pResult, Size);
    // The matrix and the vector output
    printf("Initial Matrix \n");
    PrintMatrix(pMatrix, Size, Size);
    printf("Initial Vector \n");
    PrintVector(pVector, Size);
    // Execution of Gauss algorithm
    start = clock();
    SerialResultCalculation(pMatrix, pVector, pResult, Size);
    finish = clock();
    duration = (finish-start) / CLOCKS_PER_SEC;
    // Printing the result vector
    printf ("\n Result Vector: \n");
    PrintVector(pResult, Size);
    // Printing the execution time of Gauss method
    printf("\n Time of execution: %f\n", duration);
    // Computational process termination
    ProcessTermination(pMatrix, pVector, pResult);
    return 0;
}