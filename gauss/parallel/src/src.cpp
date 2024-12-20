#include "src.h"

int* pPivotPos; // The number of pivot rows selected at the iterations
int* pPivotIter;

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
            pVector[i] = rand() / (double)(1000);
            for (j=0; j<Size; j++) {
                    pMatrix[i*Size+j] = rand() / (double)(1000);
            }
        }
}

void ProcessInitialization (double* &pMatrix, double* &pVector,
                            double* &pResult, int &Size, bool fl) {
    // Setting the size of the matrix and the vector
    // do {
    //     printf("\nEnter size of the matrix and the vector: ");
    //     scanf("%d", &Size);
    //     printf("\nChosen size = %d \n", Size);
    //     if (Size <= 0)
    //         printf("\nSize of objects must be greater than 0!\n");
    // } while (Size <= 0);
    // // Memory allocation
    pMatrix = new double [Size*Size];
    pVector = new double [Size];
    pResult = new double [Size];
    // Initialization of the matrix and the vector elements
    // DummyDataInitialization(pMatrix, pVector, Size);
    switch (fl){
        case false:
            RandomDataInitialization(pMatrix, pVector, Size);
            break;
        case true:
            AssignmentDataInitialization(pMatrix, pVector, 5);
            break;
    }
}

// Function for formatted matrix output
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

int ParallelFindPivotRow(double* pMatrix, int Size, int Iter) {
    int PivotRow = -1; // The index of the pivot row
    double MaxValue = 0; // The value of the pivot element
    int i; // Loop variable
    // Choose the row, that stores the maximum element
    #pragma omp parallel 
    {
        TThreadPivotRow ThreadPivotRow;
        ThreadPivotRow.MaxValue = 0;
        ThreadPivotRow.PivotRow = -1;
        #pragma omp for
        for (i=0; i<Size; i++) {
            if ((pPivotIter[i] == -1) &&
            (fabs(pMatrix[i*Size+Iter]) > ThreadPivotRow.MaxValue)) {
                ThreadPivotRow.PivotRow = i;
                ThreadPivotRow.MaxValue = fabs(pMatrix[i*Size+Iter]);
            }
        }
        // printf("\n Local thread (id = %i) pivot row : %i ", 
        //     omp_get_thread_num(), ThreadPivotRow.PivotRow);
        #pragma omp critical
        {
            if (ThreadPivotRow.MaxValue > MaxValue){
                MaxValue = ThreadPivotRow.MaxValue;
                PivotRow = ThreadPivotRow.PivotRow;
            }
        } // pragma omp critical
    } // pragma omp parallel
 return PivotRow;
}

// Column elimination
void ParallelColumnElimination (double* pMatrix, double* pVector,
                                int Pivot, int Iter, int Size) {
    double PivotValue, PivotFactor;
    PivotValue = pMatrix[Pivot*Size+Iter];
    #pragma omp parallel for private(PivotFactor) schedule(dynamic,1)
    for (int i=0; i<Size; i++) {
        if (pPivotIter[i] == -1) {
            PivotFactor = pMatrix[i*Size+Iter] / PivotValue;
            for (int j=Iter; j<Size; j++)
            pMatrix[i*Size + j] -= PivotFactor * pMatrix[Pivot*Size+j];
            pVector[i] -= PivotFactor * pVector[Pivot];
        }
    }
}

void ParallelGaussianElimination(double* pMatrix,double* pVector,
                                 int Size) {
    int Iter;       // The number of the iteration of the Gaussian
                    // elimination
    int PivotRow;   // The number of the current pivot row
    for (Iter=0; Iter<Size; Iter++) {
        // Finding the pivot row
        PivotRow = ParallelFindPivotRow(pMatrix, Size, Iter);
        pPivotPos[Iter] = PivotRow;
        pPivotIter[PivotRow] = Iter;
        ParallelColumnElimination(pMatrix, pVector, PivotRow, Iter, Size);
    }
}

// Back substation
void ParallelBackSubstitution (double* pMatrix, double* pVector,
                               double* pResult, int Size) {
    int RowIndex, Row;
    for (int i=Size-1; i>=0; i--) {
        RowIndex = pPivotPos[i];
        pResult[i] = pVector[RowIndex]/pMatrix[Size*RowIndex+i];
        #pragma omp parallel for private (Row)
        for (int j=0; j<i; j++) {
            Row = pPivotPos[j];
            pVector[Row] -= pMatrix[Row*Size+i]*pResult[i];
            pMatrix[Row*Size+i] = 0;
        }
    }
}

void ParallelResultCalculation(double* pMatrix, double* pVector,
                               double* pResult, int Size) {
    // Memory allocation
    pPivotPos = new int [Size];
    pPivotIter = new int [Size];
    for (int i=0; i<Size; i++)
        pPivotIter[i] = -1;
    
    ParallelGaussianElimination(pMatrix, pVector, Size);
    ParallelBackSubstitution(pMatrix, pVector, pResult, Size);
    // Memory deallocation
    delete [] pPivotPos;
    delete [] pPivotIter;
}

void ProcessTermination (double* pMatrix, double* pVector, double* pResult) {
    delete [] pMatrix;
    delete [] pVector;
    delete [] pResult;
} 
// CRINGE DATA INITIALIZATION
void AssignmentDataInitialization (double* pMatrix, double* pVector, int Size){
    pMatrix[0] = 1;
    pMatrix[1] = 1;
    pMatrix[2] = 1;
    pMatrix[3] = 1;
    pMatrix[4] = 1;
//  KILL ME PLEASE
    pMatrix[5] = 1;
    pMatrix[6] = 2;
    pMatrix[7] = 3;
    pMatrix[8] = 4;
    pMatrix[9] = 5;

    pMatrix[10] = 1;
    pMatrix[11] = 3;
    pMatrix[12] = 6;
    pMatrix[13] = 10;
    pMatrix[14] = 15;

    pMatrix[15] = 1;
    pMatrix[16] = 4;
    pMatrix[17] = 10;
    pMatrix[18] = 20;
    pMatrix[19] = 35;

    pMatrix[20] = 1;
    pMatrix[21] = 5;
    pMatrix[22] = 15;
    pMatrix[23] = 35;
    pMatrix[24] = 70;

    pVector[0] = 15;
    pVector[1] = 35;
    pVector[2] = 70;
    pVector[3] = 126;
    pVector[4] = 210;
}

// need to add a check that the slough has a solution
void Seidel_alghoritm(double* pMatrix, double* pVector,
                               double* pResult, int Size){

    
    for(int i = 0; i < Size; ++i){
        pResult[i] = 0.0;
    }
    for (int k = 0 ; k < Size; k++)
    {
        double delta = 0;
        double *pNewResult = new double [Size];

        for (int i = 0; i < Size; ++i){
            double firstSum = 0;
            double secondSum = 0;
            
            pNewResult[i] = pVector[i];

            #pragma omp parallel for reduction(+:firstSum)
            for (int j = 0; j < i; ++j)
                firstSum += pMatrix[i * Size + j] * pNewResult[j];
            
            #pragma omp parallel for reduction(+:secondSum)
            for (int j = i + 1; j < Size; ++j)
                secondSum += pMatrix[i * Size + j] * pResult[j];

            pNewResult[i] -= (firstSum + secondSum);
            pNewResult[i] /= pMatrix[i * Size + i];
        }

        #pragma omp parallel for reduction(+:delta)
        for (int i = 0; i < Size; ++i){
            delta += std::abs(pResult[i] - pNewResult[i]);
            pResult[i] = pNewResult[i];
        }

        // printf("\ndelta: %f \n", delta);
        if (delta < 1e-5) break;
    }
}