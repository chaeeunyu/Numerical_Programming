/*----------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author           : Yu Chaeeun
Created          : 11-11-2025

Description      : Quiz 2 2025
----------------------------------------------------------------*/

#include "myMatrix_Quiz.h"
// DO NOT Include your library "myNP.h"

void LUdecomp(Matrix* A, Matrix* L, Matrix* U);
Matrix fwdsub(Matrix* L, Matrix* b);
Matrix backsub(Matrix* U, Matrix* y);
Matrix solveLinear(Matrix A, Matrix b);
Matrix invMatrix(Matrix A);

int main(int argc, char* argv[])
{
    //std::string path = "./";
    /*==========================================================================*/
    /*						    Question 1. 									*/
    /*==========================================================================*/

    printf("\n**************************************************");
    printf("\n|                   Question 1.                  |");
    printf("\n**************************************************\n");


    /************      Variables declaration & initialization      ************/
    double arrayA[9] = { 75, -20, 0.0, -20, 35, -15, 0, -15, 15 };
    double arrayb[3] = { 19.62, 29.43, 14.715 };
    Matrix matrixA = arr2Mat(arrayA, 3, 3);
    Matrix vectorb = arr2Mat(arrayb, 3, 1);



    /************      Solve  &		Show Output			           ************/
    Matrix vectorx = solveLinear(matrixA, vectorb);

    printMat(matrixA, "matrix A");
    printMat(vectorb, "vector b");
    printMat(vectorx, "vector x");


    /*==========================================================================*/
    /*						    Question 2. 									*/
    /*==========================================================================*/

    printf("\n**************************************************");
    printf("\n|                 Question 2.						 ");
    printf("\n**************************************************\n");


    /************      Solve  &		Show Output			           ************/
    Matrix matrixAinv = invMatrix(matrixA);
    printMat(matrixAinv, "matrix inverse A");





    freeMat(matrixA);
    freeMat(vectorb);
    freeMat(vectorx);
    freeMat(matrixAinv);

    system("pause");
    return 0;
}


/*==========================================================================*/
/*						Function Definitions	MODIFY HERE  				*/
/*==========================================================================*/


// LU decomposition
void LUdecomp(Matrix* A, Matrix* L, Matrix* U)
{
    // initialize
    int m = A->rows;
    int n = A->cols;
    if (m != n) {
        printf("m != n\n\n");
    }
    *L = eye(m, n);
    *U = copyMat(*A);
    double mult = 0;

    for (int k = 0; k < m - 1; k++) {

        for (int i = k + 1; i < m; i++) {
            mult = U->at[i][k] / U->at[k][k];
            L->at[i][k] = mult;

            for (int j = k; j < n; j++) {
                U->at[i][j] -= mult * U->at[k][j];
            }
        }
    }


}


Matrix fwdsub(Matrix* L, Matrix* b) {
    Matrix	y = createMat(L->rows, 1);

    // initialize
    int m = L->rows;
    int n = L->cols;
    double sum;

    for (int i = 0; i < m; i++) {
        sum = 0;

        for (int j = 0; j < i; j++) {
            sum += L->at[i][j] * y.at[j][0];
        }
        y.at[i][0] = b->at[i][0] - sum;
    }

    return y;
}


Matrix backsub(Matrix* U, Matrix* y) {
    Matrix	x = createMat(U->rows, 1);

    // initialize
    int m = U->rows;
    int n = U->cols;
    double sum;

    for (int i = m - 1; i >= 0; i--) {
        sum = 0;

        for (int j = i + 1; j < n; j++) {
            sum += U->at[i][j] * x.at[j][0];
        }
        x.at[i][0] = (y->at[i][0] - sum) / U->at[i][i];
    }

    return x;
}


Matrix solveLinear(Matrix A, Matrix b) {
    Matrix U = copyMat(A);
    Matrix L = eye(A.rows, A.cols);
    Matrix y = createMat(b.rows, b.cols);
    Matrix x = createMat(b.rows, b.cols);


    // step 1. [L, U] = LUdecomp(A)
    LUdecomp(&A, &L, &U);

    // step 2. fwdsub (Ly=b)
    y = fwdsub(&L, &b);

    // step 3. backsub (Ux=y)
    x = backsub(&U, &y);

    return x;
}



Matrix invMatrix(Matrix A) {
    Matrix	Ainv = createMat(A.rows, A.rows);

    // initialize
    int m = A.rows;
    int n = A.cols;
    if (m != n) {   // A is supposed to be a square matrix
        printf("dimension error!!\n");
        return A;
    }
    Matrix L = eye(n, n);
    Matrix U = copyMat(A);
    Matrix y = createMat(m, 1);
    Matrix e = createMat(m, 1);
    Matrix v = createMat(m, 1);
    
    // step 1. LU decomposition
    LUdecomp(&A, &L, &U);

    // step 2. fwdsub (Ly=e)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            e.at[j][0] = 0;
        }
        e.at[i][0] = 1;

        y = fwdsub(&L, &e);

        // step 3. backsub (Ux=y)
        v = backsub(&U, &y);

        for (int j = 0; j < n; j++) {
            Ainv.at[j][i] = v.at[j][0];
        }

    } // end i

    return Ainv;
}
