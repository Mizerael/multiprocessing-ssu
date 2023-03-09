#ifndef pSRC_H
#define pSRC_H
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <vector>
// #include <conio.h>
#include <time.h>
#include <math.h>
#include <chrono>

#ifdef _OPENMP
#include <omp.h>
#endif

typedef struct {
    int PivotRow;
    double MaxValue;
} TThreadPivotRow;

extern std::vector<char *> cfg;
extern int* pPivotPos; // The number of pivot rows selected at the iterations
extern int* pPivotIter; // The iterations, at which the rows were pivots

void DummyDataInitialization (double* pMatrix, double* pVector, int Size);

// Function for random initialization of the matrix
// and the vector elements
void RandomDataInitialization (double* pMatrix, double* pVector, int Size);

// Function for memory allocation and definition of the objects elements
void ProcessInitialization (double* &pMatrix, double* &pVector,
                            double* &pResult, int &Size, bool fl = false);

// Function for formatted matrix output
void PrintMatrix (double* pMatrix, int RowCount, int ColCount);

// Function for formatted vector output
void PrintVector (double* pVector, int Size);

// Finding the pivot row
int ParallelFindPivotRow(double* pMatrix, int Size, int Iter);

// Column elimination
void ParallelColumnElimination (double* pMatrix, double* pVector,
                                int Pivot, int Iter, int Size);

// Gaussian elimination
void ParallelGaussianElimination(double* pMatrix,double* pVector,
                                 int Size);

// Function for the execution of Gauss algorithm
void ParallelResultCalculation(double* pMatrix, double* pVector,
                               double* pResult, int Size);

// Function for computational process termination
void ProcessTermination (double* pMatrix, double* pVector, double* pResult);

// Function for initialization matrix in accordance with the assignment
void AssignmentDataInitialization (double* pMatrix, double* pVector, int Size);

void Seidel_alghoritm (double* pMatrix, double* pVector,
                       double* pResult, int Size);
#endif