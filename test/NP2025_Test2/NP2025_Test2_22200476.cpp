/*----------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author           : Yu Chaeeun
Created          : 12-15-2025

Description      : Final Test 2025
----------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


// Include your library "myNP_yourID.h" and "myMatrix_yourID.h"
#include "../../../include/myMatrix_22200476.h"
#include "../../../include/myNP_22200476.h"


double myFunc_Q1(const double t, const double y);
Matrix myFunc_Q2(Matrix X);
Matrix myJacob_Q2(Matrix X);
Matrix nonlinearSystemGN(Matrix Funcs(Matrix _Z), Matrix Jacob(Matrix _Z), Matrix _Z0, double tol);


int main(int argc, char* argv[])
{
	//std::string path = "./";

	/*==========================================================================*/
	/*						    Question 1. 									*/
	/*==========================================================================*/

	printf("\n**************************************************");
	printf("\n|                   Question 1.                  |");
	printf("\n**************************************************\n");

	/*==========================================================================*/
	/*						Initialization										*/
	/*==========================================================================*/
	double t0 = 0.0;
	double tf = 2;
	double h = 0.1;
	double y_Q1[201] = { 0 };
	double y0_Q1 = 1;

	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/
	odeRK2(y_Q1, myFunc_Q1, t0, tf, h, y0_Q1);


	printf("y[x=%.2f]= %.2f\n\r", t0 + h * 10, y_Q1[10]);





	/*==========================================================================*/
	/*						    Question 2. 									*/
	/*==========================================================================*/

	printf("\n**************************************************");
	printf("\n|                 Question 2.						 ");
	printf("\n**************************************************\n");

	/*==========================================================================*/
	/*						Initialization										*/
	/*==========================================================================*/

	double loss = 0;
	double tol = 0.00001;
	int M = 3;
	int dim = 1;

	double z0_Q2[3] = { 25.0 / 180.0 * PI, 90, 90 };		// Z=[theta(rad),dX,dY];
	Matrix Z_Q2 = arr2Mat(z0_Q2, M, dim);
	Matrix Z2 = zeros(M, 1);

	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/

	//Z2 = nonlinearSystemGN(myFunc_Q2, myJacob_Q2, Z_Q2, tol);



	printf("Z theta:%.2f\tdx:%.2f\tdy:%.2f\n", Z_Q2.at[0][0] * 180 / PI, Z_Q2.at[1][0], Z_Q2.at[2][0]);
	printf("Z theta:%.2f\tdx:%.2f\tdy:%.2f\n", Z2.at[0][0] * 180 / PI, Z2.at[1][0], Z2.at[2][0]);

	freeMat(Z_Q2);		freeMat(Z2);

	system("pause");
	return 0;
}






/*==========================================================================*/
/*						Function Definitions	MODIFY FROM HERE  				*/
/*==========================================================================*/

double myFunc_Q1(const double t, const double y) {

	double out = 0.0;

	out = (-t + sqrt(pow(t, 2) + pow(y, 2))) / y;


	return out;
}


Matrix myFunc_Q2(Matrix Z)
{
	int n = 4;

	Matrix F = zeros(n, 1);
	double th = Z.at[0][0];
	double dx = Z.at[1][0];
	double dy = Z.at[2][0];

	// P positions
	double x0 = 0; double y0 = 100; double x1 = 0; double y1 = -100; double x2 = 0; double y2 = 0;
	// P_new positions
	double x0_new = 50; double y0_new = 186.6025; double x1_new = 150; double y1_new = 13.3975; double x2_new = 100; double y2_new = 100;

	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/
	
	F.at[0][0] = x0 * cos(th) - y0 * sin(th) + dx - x0_new;
	F.at[1][0] = x0 * sin(th) + y0 * cos(th) + dy - y0_new;
	F.at[2][0] = x1 * cos(th) - y1 * sin(th) + dx - x1_new;
	F.at[3][0] = x1 * sin(th) + y1 * cos(th) + dy - y1_new;

	return F;
}


Matrix myJacob_Q2(Matrix Z)
{
	int n = 4;
	Matrix J = zeros(n, 3);
	double th = Z.at[0][0];
	double dx = Z.at[1][0];
	double dy = Z.at[2][0];

	// P positions
	double x0 = 0; double y0 = 100; double x1 = 0; double y1 = -100; double x2 = 0; double y2 = 0;
	// P_new positions
	double x0_new = 50; double y0_new = 186.6025; double x1_new = 150; double y1_new = 13.3975; double x2_new = 100; double y2_new = 100;


	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/

	// [TO-DO] YOUR CODE GOES HERE
	J.at[0][0] = -x0 * sin(th) - y0 * cos(th);
	J.at[0][1] = 1;
	J.at[0][2] = 0;

	J.at[1][0] = x0 * cos(th) - y0 * sin(th);
	J.at[1][1] = 0;
	J.at[1][2] = 1;
	
	J.at[2][0] = -x1 * sin(th) - y1 * cos(th);
	J.at[2][1] = 1;
	J.at[2][2] = 0;

	J.at[3][0] = x1 * cos(th) - y1 * sin(th);
	J.at[3][1] = 0;
	J.at[3][2] = 1;


	return J;
}


Matrix nonlinearSystemGN(Matrix Funcs(Matrix _Z), Matrix Jacob(Matrix _Z), Matrix _Z0, double tol) {

	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/


	// Initial condition
	double loss = 100;
	int n = _Z0.rows;

	
	Matrix Z = zeros(n, 1);
	Matrix H = zeros(n, 1);
	Matrix J = zeros(4, 3);
	Matrix F = zeros(4, 1);

	Matrix L = eye(n, n);
	Matrix U = zeros(n, n);
	Matrix P = eye(n, n);

	Z = copyMat(_Z0);


	for (int k = 0; k < 20; k++) {
		F = Funcs(Z);

		F = smultMat(F, (-1));
		Matrix JT = transpose(J);
		Matrix JTJ = multMat(JT, J);
		JTJ = Jacob(Z);

		// Solve for H in  JH = (-F) -> obtain 'H'
		LUdecomp(&JTJ, &L, &U, &P); 
		solveLU(&L, &U, &P, &F, &H); 
		

		Z = addMat(Z, H);

		F = Funcs(Z);


		// Calculate Loss e.g.  loss = norm2(F);   // sqrt((F.at[0][0])^2+(F.at[1][0])^2+...)
		Matrix FT = transpose(F);
		loss = sqrt(vTv(FT, F));


		if (loss < tol) {
			printf("Early Termination\n\r");
			return Z;
		}
		freeMat(FT);
	}


	// Free MAT
	freeMat(J);		freeMat(F);		freeMat(H);


	return Z;
}

