#include "src.h"

int* pSerialPivotPos; 
int* pSerialPivotIter; 

void DummyDataInitialization (double* pMatrix, double* pVector, int Size){
    int i, j; // Loop variables
    for (i=0; i<Size; i++) {
        pVector[i] = i+1;
        for (j=0; j<Size; j++) {
            if (j <= i)
            pMatrix[i*Size+j] = 1;
            else
                pMatrix[i*Size+j] = 0;
        }
    }
}

void RandomDataInitialization (double* pMatrix, double* pVector, int Size) {
    int i, j; // Loop variables
    srand(unsigned(clock()));
       for (i=0; i<Size; i++) {
            pVector[i] = rand()/double(1000);
            for (j=0; j<Size; j++) {
                if (j <= i)
                    pMatrix[i*Size+j] = rand()/double(1000);
                else
                    pMatrix[i*Size+j] = 0;
                }
        }
}

void ProcessInitialization (double* &pMatrix, double* &pVector,
                            double* &pResult, int &Size) {
    // Setting the size of the matrix and the vector
    do {
        printf("\nEnter size of the matrix and the vector: ");
        scanf("%d", &Size);
        printf("\nChosen size = %d \n", Size);
        if (Size <= 0)
            printf("\nSize of objects must be greater than 0!\n");
    } while (Size <= 0);
    // Memory allocation
    pMatrix = new double [Size*Size];
    pVector = new double [Size];
    pResult = new double [Size];
    // Initialization of the matrix and the vector elements
    DummyDataInitialization(pMatrix, pVector, Size);
    //RandomDataInitialization(pMatrix, pVector, Size);
}

void PrintMatrix (double* pMatrix, int RowCount, int ColCount) {
    int i, j; // Loop variables
    for (i=0; i<RowCount; i++) {
        for (j=0; j<ColCount; j++)
            printf("%7.4f ", pMatrix[i*RowCount+j]);
        printf("\n");
    }
}

void PrintVector (double* pVector, int Size) {
    int i;
    for (i=0; i<Size; i++)
        printf("%7.4f ", pVector[i]);
}

int FindPivotRow(double* pMatrix, int Size, int Iter) {
    int PivotRow = -1; // The index of the pivot row
    int MaxValue = 0; // The value of the pivot element
    int i; // Loop variable
    // Choose the row, that stores the maximum element
    for (i=0; i<Size; i++) {
        if ((pSerialPivotIter[i] == -1) && 
            (fabs(pMatrix[i*Size+Iter]) > MaxValue)) {
            PivotRow = i;
            MaxValue = fabs(pMatrix[i*Size+Iter]);
        }
    }
    return PivotRow;
}

void SerialColumnElimination (double* pMatrix, double* pVector,
    int Pivot, int Iter, int Size) {
    double PivotValue, PivotFactor;
    PivotValue = pMatrix[Pivot*Size+Iter];
    for (int i=0; i<Size; i++) {
        if (pSerialPivotIter[i] == -1) {
            PivotFactor = pMatrix[i*Size+Iter] / PivotValue;
            for (int j=Iter; j<Size; j++) {
                pMatrix[i*Size + j] -= PivotFactor * pMatrix[Pivot*Size+j];
            }
            pVector[i] -= PivotFactor * pVector[Pivot];
        }
    }
}

void SerialGaussianElimination(double* pMatrix,double* pVector,int Size) {
    int Iter; // The number of the iteration of the Gaussian
    // elimination
    int PivotRow; // The number of the current pivot row
    for (Iter=0; Iter<Size; Iter++) {
        // Finding the pivot row
        PivotRow = FindPivotRow(pMatrix, Size, Iter);
        pSerialPivotPos[Iter] = PivotRow;
        pSerialPivotIter[PivotRow] = Iter;
        SerialColumnElimination(pMatrix, pVector, PivotRow, Iter, Size);
    }
}

void SerialBackSubstitution (double* pMatrix, double* pVector, double* pResult,
                             int Size) {
    int RowIndex, Row;
    for (int i=Size-1; i>=0; i--) {
        RowIndex = pSerialPivotPos[i];
        pResult[i] = pVector[RowIndex]/pMatrix[Size*RowIndex+i];
        for (int j=0; j<i; j++) {
            Row = pSerialPivotPos[j];
            pVector[Row] -= pMatrix[Row*Size+i]*pResult[i];
            pMatrix[Row*Size+i] = 0;
        }
    }
}

void SerialResultCalculation(double* pMatrix, double* pVector, double* pResult,
                             int Size) {
    // Memory allocation
    pSerialPivotPos = new int [Size];
    pSerialPivotIter = new int [Size];
    for (int i=0; i<Size; i++)
        pSerialPivotIter[i] = -1;
    
    // Gaussian elimination
    SerialGaussianElimination (pMatrix, pVector, Size);
    // Back substitution
    SerialBackSubstitution (pMatrix, pVector, pResult, Size);

    // Memory deallocation
    delete [] pSerialPivotPos;
    delete [] pSerialPivotIter;
}

void ProcessTermination (double* pMatrix, double* pVector, double* pResult) {
    delete [] pMatrix;
    delete [] pVector;
    delete [] pResult;
}