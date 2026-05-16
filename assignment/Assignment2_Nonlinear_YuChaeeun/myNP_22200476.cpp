/* myNP_tutorial.cpp */

#include "myNP_22200476.h"

void printVec(double* vec, int size)
{
	for (int i = 0; i < size; i++)
		printf("Vector[%d] = %.1f \n", i, vec[i]);
	printf("\n");
}


// factorial function
double factorial(int N)
{
	double y = 1;
	for (int k = 2; k <= N; k++) {
		y = y * k;
	}
	return y;
}

// power function
double power(double _x, int N)
{
	double y = 1.0;

	for (int i = 1; i <= N; i++) {
		y = y * _x;
	}

	return y;
}

/*==========================================================================*/
/*                                  sinTaylor                    	   		*/
/*==========================================================================*/

//  Taylor series approximation for sin(x) using pre-defined functions (input unit: [rad])
double sinTaylor(double _x)
{
	int N_max = 20;
	double S_N = 0;

	for (int k = 0; k <= N_max; k++) {
		S_N = S_N + power(-1, k) * power(_x, 2 * k + 1) / factorial(2 * k + 1);
	}

	return S_N;
}

// Taylor series approximation for sin(x) using pre-defined functions (input unit: [deg])
double sindTaylor(double _x)
{
	double rad;
	double y;

	rad = _x * PI / 180;
	y = sinTaylor(rad);

	return y;
}

double cosTaylor(double x)
{
	int N_max = 50;
	double S_N = 0;

	for (int k = 0; k <= N_max; k++) {
		S_N = S_N + power(-1, k) * power(x, 2 * k) / factorial(2 * k);
	}

	return S_N;
}



/*==========================================================================*/
/*                          Non Linear solver         	   		*/
/*==========================================================================*/


/* Bisection Method
	_a      : initial value #1
	_b      : initial value #2
	_tol   : tolerance
*/
double bisection(float _a0, float _b0, float _tol)
{
	// Define Bisection function, assuming (func(a) * func(b) <0 )
	// Initialization
	int k = 0;
	int Nmax = 100;
	float a = _a0;
	float b = _b0;
	float xn = 0;
	float ep = 1000;

	// Bisection 
	while (k < Nmax && ep > _tol) {
		// Update xn as midpoint
		xn = (a + b) / 2;

		// Update range a, b
		if (func(a) * func(xn) < 0)
			b = xn;
		else
			a = xn;

		// Check tolerance
		ep = fabs(func(xn));

		// Exception handling ------------> in case USERS put weird a and b
		if (func(xn) == 0 || ep == 0)
			break;
		else if (func(a) * func(b) > 0) {
			printf("WARNING!! [a, b] does not include solution!!\n");
			break;
		}

		k++;

		printf("k:%d \t", k);
		printf("Xn(k): %f \t", xn);
		printf("Tol: %.8f\n", ep);
	}

	return xn;
}



/* Newton-Raphson Method without Passing a Function  */
double newtonRaphson(double func(double x), double dfunc(double x), double _x0, double _tol)
{
	float xn = _x0;
	float xn1 = 0;
	float ep = 1234;
	int Nmax = 200;
	int k = 0;
	double h = 0;

	while (k < Nmax && ep > _tol) {
		if (dfunc(xn) == 0)
		{
			printf("[ERROR] dF == 0 !!\n");
			break;
		}
		else
		{
			h = -func(xn) / dfunc(xn); 

			// update x(k+1)=x(k)+h(k)
			xn = xn + h;

			// check tolerance
			ep = fabs(func(xn));
			if (ep == 0) {
				break;
			}

			k++;

			printf("k:%d \t", k);
			printf("X(k): %f \t", xn);
			printf("Tol: %.10f\n", ep);

		}
	}

	return xn;
}


