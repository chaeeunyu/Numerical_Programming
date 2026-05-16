/*----------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author           : Yu Chaeeun
Created          : 9-12-2025

Description      : Quiz 4 2025
----------------------------------------------------------------*/

#include "stdio.h"
#include "stdlib.h"
#include <math.h>
// DO NOT Include your library "myNP.h" and "myMatrix.h"
#include "myMatrixQuiz_22200476.h"

Matrix linearRegression_1D(Matrix _vecX, Matrix _vecY);
Matrix linearRegression(Matrix _vecX, Matrix _vecY);

Matrix myFuncQ2(Matrix _vecZ);
Matrix myJacobQ2(Matrix _vecZ);
Matrix nonlinearSys(Matrix myFuncs(Matrix _vecZ), Matrix Jacob(Matrix _vecZ), Matrix _vecZ_init, double tol);

int main(int argc, char* argv[]) {
    /*------------------------------------------------------------------------------------------*/
    /*==========================================================================*/
    /*					    Part 1-a:  Linear Regression  	        	        */
    /*--------------------------------------------------------------------------*/
    /*   - 1D linearFit	                                                        */
    /*   - You can change the variable names									*/
    /*   - You can create additional functions									*/
    /*==========================================================================*/

    /*==========================================================================*/
    /*						Initialization										*/
    /*==========================================================================*/
    // Initial Conditions
    double L[] = { 30, 40, 50, 60, 70, 80 };    // xdata[]
    double V[] = { 1.05, 1.07, 1.09, 1.14, 1.17, 1.21 }; // ydata[]
    double Z_Q1[2] = { 0 };
    int m_Q1 = 6;  // length of dataset

    Matrix vecL = arr2Mat(L, m_Q1, 1);
    Matrix vecV = arr2Mat(V, m_Q1, 1);
    Matrix vecZ_Q1_a = zeros(2, 1);

    /*==========================================================================*/
    /*					Apply your numerical method algorithm					*/
    /*==========================================================================*/

    vecZ_Q1_a = linearRegression_1D(vecL, vecV);

    /*==========================================================================*/
    /*							  Print your results							*/
    /*==========================================================================*/

    printf("----------------------------------------------------------------\n");
    printf("\t\t Part 1-a:  Linear Regression								\n");
    printf("----------------------------------------------------------------\n");
    printMat(vecZ_Q1_a, "Z_Q1_a");

    /*==========================================================================*/
    /*					Part 1-b:  2D_Linear Regression 						*/
    /*--------------------------------------------------------------------------*/
    /*   - n-dimension model										            */
    /*   - You can change the variable names									*/
    /*   - You can create additional functions									*/
    /*==========================================================================*/

    /*==========================================================================*/
    /*						Initialization										*/
    /*==========================================================================*/

    // Initial Conditions
    int m_Q2 = 10;  // data length
    int dim = 2;
    double X1[] = { 3504, 3761, 2375, 2255, 2035, 2155, 3755, 2025, 2945, 2625 };
    double X2[] = { 307, 400, 104, 98, 85, 97, 318, 91, 181, 120 };
    double Y[] = { 18, 15, 25, 26, 29, 28, 13, 37, 25, 28 };

    Matrix X_mat = createMat(m_Q2, dim);

    for (int i = 0; i < m_Q2; i++) {
        X_mat.at[i][0] = X1[i];
        X_mat.at[i][1] = X2[i];
    }
    Matrix Y_vec = arr2Mat(Y, m_Q2, 1);

    /*==========================================================================*/
    /*					Apply your numerical method algorithm					*/
    /*==========================================================================*/
    Matrix vecZ_Q1_b = zeros(3, 1);
    vecZ_Q1_b = linearRegression(X_mat, Y_vec);

    /*==========================================================================*/
    /*							  Print your results							*/
    /*==========================================================================*/
    printf("----------------------------------------------------------------\n");
    printf("\t\t Part 1-b:  2D - Linear Regression							\n");
    printf("----------------------------------------------------------------\n");
    printMat(vecZ_Q1_b, "Z_Q1_b");

    /*------------------------------------------------------------------------------------------*/

    /*==========================================================================*/
    /*			    Part 2:  System of Non-linear equations						*/
    /*--------------------------------------------------------------------------*/
    /*   - System of Non-linear equations					                    */
    /*   - You can change the variable names									*/
    /*   - You can create additional functions									*/
    /*==========================================================================*/

    /*==========================================================================*/
    /*						Initialization										*/
    /*==========================================================================*/
    // Initial Conditions
    double tol = 0.0001;
    double Zinit[2] = { 2.5, 2.0 };
    Matrix vecZinit = arr2Mat(Zinit, 2, 1);

    ///*==========================================================================*/
    ///*					Apply your numerical method algorithm					*/
    ///*==========================================================================*/

    Matrix vecZ_Q2 = zeros(2, 1);
    vecZ_Q2 = nonlinearSys(myFuncQ2, myJacobQ2, vecZinit, tol);


    ///*==========================================================================*/
    ///*							  Print your results							*/
    ///*==========================================================================*/

    // Print outputs
    printf("----------------------------------------------------------------\n");
    printf("\t\t Part 2:  System of Non-linear equations					\n");
    printf("----------------------------------------------------------------\n");
    printMat(vecZ_Q2, "Z_Q2");

    system("pause");
    return 0;
}

/*==========================================================================*/
/*						MODIFY HERE  										*/
/*==========================================================================*/

/*==========================================================================*/
/*					        Part 1:  Linear Regression 			            */
/*--------------------------------------------------------------------------*/

Matrix linearRegression_1D(Matrix _vecX, Matrix _vecY) { // xdata[], ydata[], dataN
    int m = _vecX.rows; // m = dataN
    int d = _vecX.cols;  // d = dimension of X

    //Matrix A = ones(m, d + 1);
    Matrix Z = zeros(d + 1, 1);

    double Sx = 0;
    double Sy = 0;
    double Sxx = 0;
    double Sxy = 0;
    //double a0, a1 = 0;

    // solve for Sx,...
    for (int k = 0; k < m; k++) {
        Sx += _vecX.at[k][0];
        Sy += _vecY.at[k][0];
        Sxx += pow(_vecX.at[k][0], 2);
        Sxy += _vecX.at[k][0] * _vecY.at[k][0];
    }

    // solve for a0, a1
    Z.at[0][0] = (Sxx * Sy - Sx * Sxy) / (m * Sxx - Sx * Sx);
    Z.at[1][0] = (m * Sxy - Sx * Sy) / (m * Sxx - Sx * Sx);

    return Z;
}


Matrix linearRegression(Matrix _vecX, Matrix _vecY) { ///*********************************
    int m = _vecX.rows;
    int d = _vecX.cols;  // d = 2
    Matrix A = ones(m, d + 1);
    Matrix Z = zeros(d + 1, 1);

    // z = (ATA)^-1ATy

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < d + 1; j++) {
            A.at[i][j] = pow(_vecX.at[j][i], j);
        }
    }

    Matrix AT = transpose(A);
    Matrix ATA = multMat(AT, A);
    Matrix ATA_inv = zeros(ATA.rows, ATA.cols);
    invMat(&ATA, &ATA_inv);

    Matrix ATy = multMat(AT, _vecY);
    Z = multMat(ATA_inv, ATy);

    return Z;
}

/*==========================================================================*/
/*				    Part 2:  System of Non-linear equations					*/
/*--------------------------------------------------------------------------*/
Matrix myFuncQ2(Matrix _vecZ) {
    Matrix F = createMat(2, 1);
    double x = _vecZ.at[0][0];
    double y = _vecZ.at[1][0];

    F.at[0][0] = y - (exp(x / 2) + exp(-x / 2)) / 2;
    F.at[1][0] = 9 * pow(x, 2) + 25 * pow(y, 2) - 225;

    return F;
}
Matrix myJacobQ2(Matrix _vecZ) {
    Matrix J = createMat(2, 2);
    double x = _vecZ.at[0][0];
    double y = _vecZ.at[1][0];

    J.at[0][0] = -(exp(x / 2) - exp(-x / 2)) / 4;
    J.at[0][1] = 1;
    J.at[1][0] = 18 * x;
    J.at[1][1] = 50 * y;

    return J;
}

Matrix nonlinearSys(Matrix myFuncs(Matrix _vecZ), Matrix Jacob(Matrix _vecZ), Matrix _vecZ_init, double tol) {
    
    // initialize
    int n = _vecZ_init.rows;
    Matrix Z = copyMat(_vecZ_init);
    Matrix F = zeros(n, 1);
    Matrix J = zeros(n, n);
    Matrix H = zeros(n, 1);
    
    Matrix L = eye(n, n);
    Matrix U = zeros(n, n);
    Matrix P = eye(n, n);

    int Nmax = 500;
    double ep = 1000;
    for (int i = 0; i < Nmax && ep > tol; i++) {
        F = myFuncs(Z);
        J = Jacob(Z);

        // F -> -F
        F = smultMat(F, (-1));

        // solve for JH = -F,  H = J\(-F)
        LUdecomp(&J, &L, &U, &P);
        solveLU(&L, &U, &P, &F, &H);

        // update Z and F
        Z = addMat(Z, H);
        F = myFuncs(Z);
    }

    return Z;
}
