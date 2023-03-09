#ifndef sSRC_H
#define sSRC_H
#include <stdio.h>
#include <stdlib.h>
#include <iterator>
#include <vector>
// #include <conio.h>
#include <time.h>
#include <math.h>
#include <chrono>

extern std::vector<char *> cfg;
extern int* pSerialPivotPos; // The Number of pivot rows selected at the
// iterations
extern int* pSerialPivotIter; // The Iterations, at which the rows were pivots
// Function for simple initialization of the matrix
// and the vector elements
void DummyDataInitialization (double* pMatrix, double* pVector, int Size);

// Function for random initialization of the matrix
// and the vector elements
void RandomDataInitialization (double* pMatrix, double* pVector, int Size);

// Function for memory allocation and definition of the objects elements
void ProcessInitialization (double* &pMatrix, double* &pVector,
                            double* &pResult, int &Size);

// Function for formatted matrix output
void PrintMatrix (double* pMatrix, int RowCount, int ColCount);

// Function for formatted vector output
void PrintVector (double* pVector, int Size);

// Finding the pivot row 
int FindPivotRow(double* pMatrix, int Size, int Iter);

// Column elimination
void SerialColumnElimination (double* pMatrix, double* pVector,
    int Pivot, int Iter, int Size);

// Function for the execution of Gauss algorithm
void SerialResultCalculation(double* pMatrix, double* pVector, double* pResult,
                             int Size);

// Gaussian elimination
void SerialGaussianElimination(double* pMatrix,double* pVector,int Size);

// Back substution
void SerialBackSubstitution (double* pMatrix, double* pVector, double* pResult,
                             int Size);
void ProcessTermination (double* pMatrix, double* pVector, double* pResult);

void Seidel_alghoritm(double* pMatrix, double* pVector, double* pResult,
                      int Size);
#endif