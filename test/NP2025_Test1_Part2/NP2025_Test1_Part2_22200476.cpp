/*----------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author           : Yu Chaeeun
Created          : 10-17-2025
Modified         : 10-17-2025
Language/ver     : C++ in MSVS2022

Description      : MidTerm2025 - Part 2
---------------------------------------------------------------*/

// Include your library "myNP.h"
#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#include "../../../include/myNP_22200476.h"  // Need to change the path


double func_Q1(double x);
double func_Q2(double x);
double func_Q3(double x);
double dfunc_Q3(double x);



int main(int argc, char* argv[])
{
	printf("\n**************************************************");
	printf("\n|                 Question 1.		               ");
	printf("\n**************************************************\n");


	double ansQ1 = 0.0;

	// [TO-DO] Add your code here
	double a = -1;
	double b = 1;
	int N = 13;

	ansQ1 = integral(func_Q1, a, b, N);
	printf("N = %d\n", N);

	printf("\n Answer of Q1 = %f \n\n", ansQ1);




	printf("\n**************************************************");
	printf("\n|                 Question 2.						 ");
	printf("\n**************************************************\n");

	double ansQ2 = 0;

	// [TO-DO] Add your code here

	int x_in = 1;

	int p = 21;
	double y3[21] = { 0 };
	double x3[21] = { 0 };
	for (int j = 0; j < p; j++) {
		x3[j] = j;
	}

	for (int k = 0; k < 21; k++) {
		y3[k] = func_Q2(x3[k]);
	}

	double dy2dx2[21] = { 0 };
	acceleration(x3, y3, dy2dx2, p);

	ansQ2 = dy2dx2[x_in];

	printf("\n Answer of Q2 = %0.4f \n\n", ansQ2);




	printf("\n**************************************************");
	printf("\n|                 Question 3					    ");
	printf("\n**************************************************\n");


	double ansQ3_x = 0;
	double ansQ3_y = 0;


	// [TO-DO] Add your code here
	double x0 = 1;
	double x1 = 1.1;
	double tol = 1e-5;
	printf("Newton-Raphson Method Result:\n");
	ansQ3_x = secantfzero(func_Q3, x0, x1, tol);

	printf("\n Answer of Q3 x= %0.4f \t y= %0.4f \n\n", ansQ3_x, ansQ3_y);



	system("pause");
	return 0;
}



/*==========================================================================*/
/*						Function Definitions								*/
/*==========================================================================*/

double func_Q1(double x)
{
	double out = 0.0;

	out = 2 / (1 + pow(x, 2));

	return out;
}

double func_Q2(double x)
{
	double out = 0.0;

	out = (1 / sqrt(2 * PI)) * exp(-pow(x, 2) / 18);

	return out;
}

double func_Q3(double x)
{
	double out = 0.0;

	out = (-15 / (120 * 3 * 70 * 52.9 * 1e-6)) * (-pow(3, 4) + 6 * pow(3, 2) * x - 5 * pow(x, 4));

	return out;
}

double dfunc_Q3(double x)
{
	double out = 0.0;

	// [TO-DO] Add your code here
	// [TO-DO] Add your code here

	return out;
}


