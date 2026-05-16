/*-------------------------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author           : Yu Chaeeun
Created          : 17-05-2021
Modified         : 12-10-2025
Language/ver     : C++ in MSVS2019

Description      : [Tutorial] Integration_student.cpp
-------------------------------------------------------------------------------*/

#include "stdio.h"
#include "stdlib.h"

#include "../../include/myNP_22200476.h"

// Sample Code: Integration rectangular method 
double IntegrateRect(double x[], double y[], int m);

// You need to create myFunc() in this main source file
double myFunc(const double x);
double myFunc2(const double x);


int main(int argc, char* argv[])
{

	printf("\n**************************************************");
	printf("\n		tutorial        ");
	printf("\n**************************************************\n");

	/************      Variables declaration & initialization      ************/
	double x[] = { 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60 };
	double y[] = { 0, 3, 8, 20, 33, 42, 40, 48, 60, 12, 8, 4, 3 };
	int M = sizeof(x) / sizeof(x[0]);



	/************      Solve  &	Show Output	   ************/
	double I_rect = IntegrateRect(x, y, M);
	printf("I_rect  = %f\n", I_rect);

	// Exercise 0. Trapezoid
	double I_trapz = 0;
	I_trapz = trapz(x, y, M);
	printf("I_trapz = %f\n\n", I_trapz);


	
	printf("\n**************************************************");
	printf("\n		 Problem 1.       ");
	printf("\n**************************************************\n");
	
	// Exercise 1. Simpson13
	double I_simpson13 = 0;
	I_simpson13 = simpson13(x, y, M);
	printf("I_simpson13  = %f\n\n", I_simpson13);


	// Exercise 2. Simpson38
	double I_simpson38 = 0;
	I_simpson38 = simpson38(x, y, M);
	printf("I_simpson38  = %f\n\n", I_simpson38);


	// Exercise 3. Integral - from a function
	double I_function = 0;
	double a = -1;
	double b = 1;
	int N = 13;

	I_function = integral(myFunc, a, b, N);
	printf("N = %d\n", N);
	printf("I_function  = %f\n\n", I_function);


	printf("\n**************************************************");
	printf("\n		 Problem 2.       ");
	printf("\n**************************************************\n");

	// engineering problem
	double I_prob2 = 0;
	double a2 = 0;
	double b2 = 30;
	double h = 0.05;
	int N2 = (b2 - a2) / h;
	
	I_prob2 = integral(myFunc2, a2, b2, N2);
	printf("N2 = %d\n", N2);
	printf("I_prob2  = %f\n\n", I_prob2);

	system("pause");
	return 0;
}



// Sample Code: Integration rectangular method 
double IntegrateRect(double x[], double y[], int m) {
	int N = m - 1;
	double I = 0;
	for (int i = 0; i < N; i++)
		I += y[i] * (x[i + 1] - x[i]);
	return I;
}


double myFunc(const double x)
{
	double f = sqrt(1 - pow(x, 2));

	return f;
}

double myFunc2(const double x)
{
	double f = 200 * x / (5 + x) * exp(-2 * x / 30);

	return f;
}



