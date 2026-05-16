/*------------------------------------------------------------------------------------------\
@ Numerical Methods by Young-Keun Kim - Handong Global University

Author          : Yu Chaeeun
Created         : 07-03-2019
Modified        : 09-12-2025
Language/ver    : C-Program(C11, MSVS2017)
Course          : Numerical Programming
Description     : Tutorial of Bisection Method
/------------------------------------------------------------------------------------------*/


#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#include "../../include/myNP_22200476.h"



void main() {

	/*==========================================================================*/
	/*               Tutorial -     Bisection Method                            */
	/*==========================================================================*/

	/************      Variables declaration & initialization      ************/
	double tol = 0.00001;
	double a0 = 2;			//need to change initial value
	double b0 = 3;			//need to change initial value
	double sol_bm = 0;

	/************      Solve  &		Show Output			           ************/
	printf("------------------------------------------------------------------------------------\n");
	printf("         Bisection Method Results             \n");
	printf("------------------------------------------------------------------------------------\n");

	printf("Bisection Method:\n");
	sol_bm = bisection(a0, b0, tol);

	printf("Final Solution: %f \t", sol_bm);
	printf("\n");



	/*==========================================================================*/
	/*               Assignment -     Newton Rhapson                            */
	/*==========================================================================*/

	/************      Variables declaration & initialization      ************/
	double sol_nr = 0;
	double x0 = 3;

	printf("------------------------------------------------------------------------------------\n");
	printf("         Newton-Raphson Method Results             \n");
	printf("------------------------------------------------------------------------------------\n");

	/************      Solve  &		Show Output			           ************/
	printf("Newton-Raphson Method Result:\n");
	sol_nr = newtonRaphson(func, dfunc, x0, tol);

	printf("Final Solution: %f \t", sol_nr);
	printf("\n");


	system("pause");
}




/*------------------------------------------------------------------------------------------------------------------------*/
/*                                                       FUNCTION                                                         */
/*------------------------------------------------------------------------------------------------------------------------*/
 
/* function f(x) of the problem */ // ------------> 근데 func은 사용자가 입력해야하기 때문에 여기 정의하면 안됨 , 사용자는 헤더에 접근x -> 숙제로
double func(double x)
{
	double F = 0;
	F = 8 - 4.5 * (x - sinTaylor(x));

	return F;
}

/* first derivative of function f(x) of the problem */
double dfunc(double x)
{
	double dF = 0;
	dF =  -4.5 * (1 - cosTaylor(x));

	return dF;
}