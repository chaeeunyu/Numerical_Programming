/*------------------------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author          : Yu Chaeeun
Created         : 01-04-2019
Modified        : 09-19-2025
Language/ver	: C in MSVS2017
Course		: Numerical Programming

Description      : [Assignment] Differentiation.cpp
-------------------------------------------------------------------------------*/

#include "stdio.h"
#include "stdlib.h"

#include "../../include/myNP_22200476.h"


double myFunc(const double x);



int main(int argc, char* argv[])
{

	/*==========================================================================*/
	/*   Part 1 -     Differentiation from discrete dataset points              */
	/*==========================================================================*/

	printf("\n**************************************************");
	printf("\n|                     PART 1.                    |");
	printf("\n**************************************************\n");

	/************      Variables declaration & initialization      ************/
	int m = 12;
	double x1[] = { -1, -0.5, 0, 0.5, 1, 1.5, 2, 2.5, 3, 3.5, 4, 4.5 };

	double y1[] = { -3.632, - 0.3935, 1, 0.6487, - 1.282, - 4.518, - 8.611, - 12.82, - 15.91, - 15.88, - 9.402, 9.017 };
	double  dydx1[12] = { 0 };

	/************      Solve  &	Show Output	   ************/
	// Differentiation from discrete dataset points


	gradient1D(x1, y1, dydx1, m);
	printVec(dydx1, m);



	/*==========================================================================*/
	/*   Part 2 -     Differentiation from a function                           */
	/*==========================================================================*/


	printf("\n**************************************************");
	printf("\n|                     PART 2.                    |");
	printf("\n**************************************************\n");

	/************      Variables declaration & initialization      ************/

	int n = 21;
	double x2[21] = { 0 };
	for (int i = 0; i < n; i++) {
		x2[i] = 0.2 * i;
	}
	double dydx2[21] = { 0 };  // m=21 points

	// User defined function F(x)
	double xin = 2.5;
	double y = myFunc(xin);
	printf("\n y=myFun(xin) = %f \n\n", y);
	printf("- - - - - - - - - - - - - - - - - - - - - -\n\n");


	/************      Solve  &	Show Output	   ************/
	// Estimate differentiation from the user defined function 


	gradientFunc(myFunc, x2, dydx2, n);
	printVec(dydx2, n);



	/*==========================================================================*/
	/*   Part 3 -     2nd order differentiation                           */
	/*==========================================================================*/

	printf("\n**************************************************");
	printf("\n|                     PART 3.                    |");
	printf("\n**************************************************\n");

	/************      Variables declaration & initialization      ************/

	int p = 21;
	double y3[21] = { 0 };
	double x3[21] = { 0 };
	for (int j = 0; j < p; j++) {
		x3[j] = 0.2 * j;
	}
	
	for (int k = 0; k < 21; k++) {
		y3[k] = myFunc(x3[k]);
	}

	double dy2dx2[21] = { 0 };

	//for (int z = 0; z < 21; z++) {
	//	printf("y3[%d] = %f\n", z, y3[z]);
	//}

	acceleration(x3, y3, dy2dx2, p);
	printVec(dy2dx2, p);


	system("pause");
	return 0;
}


/*--------------------------------------------------------------------------------------------------------*/

// User defined function:  example  y=x*x
// Modify to User Function
double myFunc(const double x) {
	return  power(x, 3);
}
