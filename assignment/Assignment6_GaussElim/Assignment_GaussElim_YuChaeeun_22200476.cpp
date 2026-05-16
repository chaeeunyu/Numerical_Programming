/*-------------------------------------------------------------------------------\
@ Numerical Programming by Young-Keun Kim - Handong Global University

Author           : Yu Chaeeun
Created          : 26-03-2018
Modified         : 19-10-2023
Language/ver     : C++ in MSVS2019

Description      : Tutorial code for using matrix structure
-------------------------------------------------------------------------------*/

#define ASGN		5		// enter your assignment number
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

		// --- Q1. ---
	Matrix matA = txt2Mat(path, "prob1_matA");
	Matrix vecb = txt2Mat(path, "prob1_vecb");
	Matrix mat_U = createMat(matA.rows, matA.cols);
	Matrix vecd = createMat(matA.rows, 1);
	Matrix vecx = createMat(mat_U.rows, 1);

	gaussElim(&matA, &vecb, &mat_U, &vecd);
	backsub(&mat_U, &vecd, &vecx);


	// --- Q2. ----
	Matrix matK = txt2Mat(path, "prob2_matK");
	Matrix vecf = txt2Mat(path, "prob2_vecf");
	Matrix matV = createMat(matK.rows, matK.cols);
	Matrix vece = createMat(vecf.rows, 1);
	Matrix vecu = createMat(vecf.rows, 1);

	gaussElim(&matK, &vecf, &matV, &vece);
	backsub(&matV, &vece, &vecu);


	// --- Extra-credit. (optional) ----
	Matrix testA = txt2Mat(path, "testA");
	Matrix testU = createMat(testA.rows, testA.cols);
	Matrix P = eye(testA.rows, testA.cols);
	//printMat(testA, "testA1");

	partialPvt(&testA, &vecb, &P);
	gaussElim(&testA, &vecb, &testU, &vecd);
	//backsub(&testU, &vecd, &vecx);




	/*==========================================================================*/
	/*							  Print your results							*/
	/*==========================================================================*/
	printf("------ Q1 -------\n");
	// --- Q1. ---
	printMat(matA, "matA");
	printMat(vecb, "vecb");
	printMat(mat_U, "U");
	printMat(vecd, "d");
	printMat(vecx, "x");

	printf("------- Q2 -------\n");

	// --- Q2. ---
	printMat(matK, "matK");
	printMat(vecf, "vecf");
	printMat(matV, "matV");
	printMat(vece, "vec_e");
	printMat(vecu, "vec_u");


	printf("------- partial pivoting -------\n");
	// --- Extra-credit. (optional) ----
	printMat(testA, "testA");
	printMat(testU, "testU");
	printMat(P, "P");


	/*==========================================================================*/
	/*							  Deallocate memory 							*/
	/*==========================================================================*/
	freeMat(matA);		freeMat(vecb);

	// free other  created  matrices
	freeMat(mat_U);		freeMat(vecd);		freeMat(vecx);

	freeMat(matK);		freeMat(vece);		
	freeMat(matV);		freeMat(vecu);		freeMat(vecu);

	freeMat(testA);		freeMat(testU);		freeMat(P);

	system("pause");
	return 0;
}
