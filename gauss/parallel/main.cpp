#include "src/src.h"
#include "../utils/test.h"
int main() {
    double* pMatrix; // The matrix of the linear system
    double* pVector; // The right parts of the linear system
    double* pResult; // The result vector
    int Size; // The size of the matrix and the vectors
    double start, finish, duration;
    // Data initialization
    ProcessInitialization(pMatrix, pVector, pResult, Size);
    // The matrix and the vector output
    printf ("Initial Matrix \n");
    PrintMatrix(pMatrix, Size, Size);
    printf("Initial Vector \n");
    PrintVector(pVector, Size);

    ParallelResultCalculation(pMatrix, pVector, pResult, Size);
    // The matrix and the vector output
    printf ("Recalculated Matrix \n");
    PrintMatrix(pMatrix, Size, Size);

    printf("Recalculated Vector \n");
    PrintVector(pVector, Size);
    
    printf("\nResult Vector \n");
    PrintVector(pResult, Size);
    // Program termination
    ProcessTermination(pMatrix, pVector, pResult);
    return 0;
}