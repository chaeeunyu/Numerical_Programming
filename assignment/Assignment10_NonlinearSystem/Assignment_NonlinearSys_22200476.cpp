/*------------------------------------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author          : Yu Chaeeun
Created         : 01-04-2019
Modified        : 11-27-2023
Language/ver	: C in MSVS2017
Course			: Numerical Programming

Description     : Assignment System of NonLinear
/------------------------------------------------------------------------------------------*/


#include "stdio.h"
#include "stdlib.h"
#include <math.h>

#include "../../include/myNP_22200476.h"
#include "../../include/myMatrix_22200476.h"



// Defined in main code
Matrix myFuncEx1(Matrix X);
Matrix myJacobEx1(Matrix X);
Matrix myFuncEx2(Matrix X);
Matrix myJacobEx2(Matrix X);



void main() {

	/*==========================================================================*/
	/*					Variables declaration & initialization					*/
	/*--------------------------------------------------------------------------*/
	/*   - You can change the variable names									*/
	/*   - However, you must use the specified file name						*/
	/*	   : For each assignment, the file name will be notified on HISNET		*/
	/*==========================================================================*/

	/************      Variables declaration & initialization      ************/
	// problem 1. - n=2
	double tol = 0.001;
	int n = 2;
	Matrix Z = zeros(n, 1);
	double z0[2] = { 2.5, 2 };
	Z = arr2Mat(z0, n, 1);

	// problem 2. - n>2
	int n2 = 3;
	Matrix Z2 = zeros(n, 1);
	double z20[3] = { 25 / 180 * PI, 90, 90 };
	Z2 = arr2Mat(z20, n2, 1); 


	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/
	printf("----------------------------------------------------------------------------------------------\n");
	printf("			            System of NonLinear													  \n");
	printf("----------------------------------------------------------------------------------------------\n\r");
	printf("problem 1.\n\n");
	
	Z = nonlinearSys(myFuncEx1, myJacobEx1, Z, tol);
	printMat(Z, "Z");

	printf("-------------------------------------------------------------------------------\n");
	printf("problem 2.\n\n");

	Z2 = nonlinearSys2(myFuncEx2, myJacobEx2, Z2, tol);
	printMat(Z2, "Z2");
	double th = Z2.at[0][0];
	th = th * 180 / PI;
	printf("theta = %.2f[deg]\n\n", th);



	/*==========================================================================*/
	/*							  Deallocate memory 							*/
	/*==========================================================================*/
	//freeMat(J);	freeMat(H);	freeMat(F); 	
	freeMat(Z);		freeMat(Z2);

	system("pause");
}




/*==========================================================================*/
/*						Function Definitions								*/
/*==========================================================================*/

Matrix myFuncEx1(Matrix X)
{
	int n = X.rows;
	Matrix F = zeros(n, 1);
	double x1 = X.at[0][0]; // x1 = x
	double x2 = X.at[1][0]; // x2 = y

	// [TO-DO] YOUR CODE GOES HERE
	F.at[0][0] = x2 - 0.5 * (exp(x1 / 2) + exp(-x1 / 2));
	F.at[1][0] = 9 * pow(x1, 2) + 25 * pow(x2, 2) - 225;

	return F;
}


Matrix myJacobEx1(Matrix X)
{
	int n = X.rows;
	Matrix J = zeros(n, n);
	double x1 = X.at[0][0];  // x1 = x
	double x2 = X.at[1][0];  // x2 = y

	// [TO-DO] YOUR CODE GOES HERE
	J.at[0][0] = -0.25 * (exp(x1 / 2) - exp(-x1 / 2));
	J.at[0][1] = 1;
	J.at[1][0] = 18 * x1;
	J.at[1][1] = 50 * x2;


	return J;
}



Matrix myFuncEx2(Matrix X)
{
	int n = X.rows;
	Matrix F = zeros(n, 1);
	double th = X.at[0][0];
	double dx = X.at[1][0];
	double dy = X.at[2][0]; 

	// initial value
	double x0 = 0;
	double y0 = 100;
	double x1 = 0;
	double y1 = -100;
	/*double x2 = 0;
	double y2 = 0; */  // choose 3 out of these

	// final value
	double xf0 = 50;
	double yf0 = 186.6025;
	double xf1 = 150;
	/*double yf1 = 13.3975;
	double xf2 = 100;
	double yf2 = 100;*/  // choose 3 out of these

	// [TO-DO] YOUR CODE GOES HERE
	F.at[0][0] = x0 * cos(th) - y0 * sin(th) + dx - xf0;
	F.at[1][0] = x0 * sin(th) + y0 * cos(th) + dy - yf0;
	F.at[2][0] = x1 * cos(th) - y1 * sin(th) + dx - xf1;

	return F;
}

Matrix myJacobEx2(Matrix X)
{
	// J = F를 [th, dx, dy]로 미분
	int n = X.rows;
	Matrix J = zeros(n, n);
	double th = X.at[0][0];
	double dx = X.at[1][0]; 
	double dy = X.at[2][0];  

	// initial value
	double x0 = 0;
	double y0 = 100;
	double x1 = 0;
	double y1 = -100;
	/*double x2 = 0;
	double y2 = 0; */  // choose 3 out of these

	// final value
	double xf0 = 50;
	double yf0 = 186.6025;
	double xf1 = 150;
	/*double yf1 = 13.3975;
	double xf2 = 100;
	double yf2 = 100; */ // choose 3 out of these


	J.at[0][0] = -x0 * sin(th) - y0 * cos(th);  // dF[0]/d(th)
	J.at[0][1] = 1;								// dF[0]/d(x)
	J.at[0][2] = 0;								// dF[0]/d(y)
	
	J.at[1][0] = x0 * cos(th) - y0 * sin(th);	// dF[1]/d(th)
	J.at[1][1] = 0;								// dF[1]/d(x)
	J.at[1][2] = 1;								// dF[1]/d(y)

	J.at[2][0] = -x1 * sin(th) - y1 * cos(th);	// dF[2]/d(th)
	J.at[2][1] = 1;								// dF[2]/d(x)
	J.at[2][2] = 0;								// dF[2]/d(y)


	return J;
}


