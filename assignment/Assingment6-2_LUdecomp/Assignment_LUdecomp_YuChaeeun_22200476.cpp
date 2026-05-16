/*-------------------------------------------------------------------------------\
@ Numerical Programming by Young-Keun Kim - Handong Global University

Author           : Yu Chaeeun
Created          : 26-03-2018
Modified         : 30-10-2023
Language/ver     : C++ in MSVS2019

Description      : Tutorial code for using matrix structure
-------------------------------------------------------------------------------*/

#define ASGN		6		// enter your assignment number
#define EVAL		0		// [воик DO NOT EDIT !!!]


#include "../../include/myMatrix_22200476.h"
#include "../../include/myNP_22200476.h"


int main(int argc, char* argv[])
{

	/*	 [воик DO NOT EDIT !!!]   Resources file path setting for evaluation	*/
// #if _WIN64 | _WIN32
// 	std::string path = "C:/NP_Data/Assignment" + std::to_string(ASGN) + "/";

// #elif __APPLE__
// 	std::string path = "~/NP_Data/Assignment" + std::to_string(ASGN) + "/";
// #endif

	std::string path = "../../NP_Data/Assignment" + std::to_string(ASGN) + "/";
#if EVAL
	path += "eval/";
#endif

	/*==========================================================================*/
	/*					Variables declaration & initialization					*/
	/*--------------------------------------------------------------------------*/
	/*   - You can change the variable names									*/
	/*   - However, you must use the specified txt file name					*/
	/*==========================================================================*/


	/*==========================================================================*/
	/*					Apply your numerical method algorithm					*/
	/*==========================================================================*/


	// initialize
	Matrix matA = txt2Mat(path, "prob2_matK");  // prob2_matK
	Matrix vecb = txt2Mat(path, "prob2_vecf");  // prob2_vecf
	Matrix L = eye(matA.rows, matA.cols);
	Matrix U = zeros(matA.rows, matA.cols);
	Matrix P = eye(matA.rows, matA.cols);
	Matrix x = createMat(matA.rows, 1);
	Matrix Ainv = createMat(matA.rows, matA.cols);
	Matrix xinv = createMat(matA.rows, 1);
	

	// --- Q1. --- LUdecomp
	LUdecomp(&matA, &L, &U, &P);


	// --- Q2. --- solveLU
	solveLU(&L, &U, &P, &vecb, &x);


	// --- Q3. --- inverse matrix
	invMat(&matA, &Ainv);
	xinv = multMat(Ainv, vecb);




	/*==========================================================================*/
	/*							  Print your results							*/
	/*==========================================================================*/
	printf("========= Q1 (LU decomp) ========\n");
	// --- Q1. ---
	printf("final result: \n\n");
	printMat(matA, "A");
	printMat(L, "L");
	printMat(U, "U");
	printMat(P, "P");

	printf("========= Q2 (solve x) =========\n");

	// --- Q2. ---
	printMat(vecb, "b");
	printMat(x, "x");

	printf("========= Q3 (inverse) =========\n");
	// --- Q3. ----
	printMat(Ainv, "Ainv");
	printMat(xinv, "xinv");
	


	/*==========================================================================*/
	/*							  Deallocate memory 							*/
	/*==========================================================================*/
	freeMat(matA);		freeMat(vecb);

	// free other  created  matrices
	freeMat(L);			freeMat(U);			freeMat(P);		freeMat(x);

	freeMat(Ainv);		freeMat(xinv);

	system("pause");
	return 0;
}
