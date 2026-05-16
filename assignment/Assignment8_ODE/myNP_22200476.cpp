/* myNP_22200476.cpp */

#include "myNP_22200476.h"

void printVec(double* vec, int size)
{
	for (int i = 0; i < size; i++)
		printf("Vector[%d] = %.4f \n", i, vec[i]);
	printf("\n");
}

// (rad) -> (deg)
double deg(double x)
{
	return x * 180 / PI;
}

// (deg) -> (rad)
double rad(double x)
{
	return x * PI / 180;
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
double bisection(double func(double x), float _a0, float _b0, float _tol)
{
	// Define Bisection function, assuming (func(a) * func(b) <0 )
	// Initialization
	int k = 0;
	int Nmax = 100;
	float a = rad(_a0);    // convert (deg) into (rad)
	float b = rad(_b0); 
	float xn = 0;
	float ep = 1000;

	 //Bisection 
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
		printf("Xn(k): %f \t", deg(xn));
		printf("Tol: %.8f\n", ep);
	}

	xn = deg(xn);
	return xn;
}


/* Newton-Raphson Method with Passing a Function  */
double newtonRaphson(double func(double x), double dfunc(double x), double _x0, double _tol)
{
	// initialization
	float xn = rad(_x0);   // convert (deg) to (rad)
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
			xn = xn + h;	// or		xn += h;

			// check tolerance
			ep = fabs(func(xn));
			if (ep == 0) {
				break;
			}

			k++;

			printf("k:%d \t", k);
			printf("X(k): %f \t", deg(xn));
			printf("Tol: %.10f\n", ep);

		}
	}

	xn = deg(xn);
	return xn;
}


/* Secant Method with Passing a Function  */
double secantfzero(double func(double x), double x0, double x1, double tol)
{
	// initialization
	double dfunc;
	double ep = 100;
	int k = 0, Nmax = 200;
	double xn = rad(x1), xn_1 = rad(x0);   // convert (deg) to (rad)

	// Secant Method
	while(k < Nmax && ep > tol)
	{
		dfunc = -(xn - xn_1) / (func(xn) - func(xn_1));
		xn_1 = xn;
		xn = xn + dfunc * func(xn);

		// check tolerance
		ep = fabs(func(xn));
		if (ep == 0)
			break;

		k++;

		printf("k:%d \t", k);
		printf("X(k): %f \t", deg(xn));
		printf("Tol: %.10f\n", ep);
	}

	xn = deg(xn);
	return xn;
}




/*==========================================================================*/
/*                            Differentiation                	   		*/
/*==========================================================================*/


/*-- 1st order differentiation--------------------------------------*/
void gradient1D(double x[], double y[], double dydx[], int m) {

	// h = x[i+1] - x[i]

	//	Three-point forward difference
	dydx[0] = (-3 * y[0] + 4 * y[1] - y[2]) / (x[2] - x[0]);


	//	Two-point central difference
	for (int i = 1; i < m - 1; i++) {
		dydx[i] = (y[i + 1] - y[i - 1]) / (x[i + 1] - x[i - 1]);
	}

	// Three-point backward for the last point
	dydx[m - 1] = (y[m - 3] - 4 * y[m - 2] + 3 * y[m - 1]) / (x[m - 1] - x[m - 3]);
}


/*-- 1st order differentiation < with FUNCTION CALL >-----------------------------*/
void gradientFunc(double myFunc(const double x), double x[], double dydx[], int m) {

	/*  ---------------- TA session ---------------------
	여기 안에서 y[] 배열 만들어서 하려면 동적할당 써야함  -----> m값이 미리 정해지지 않기 때문
	double* y;
	y = (double *)malloc(sizeof(double *)* m);
	for(int i = 0; i < m; i++){
		y[i] = myfunc(x[i]);
	}
	*/

	// The first point:	Three-point forward difference
	dydx[0] = (-3 * myFunc(x[0]) + 4 * myFunc(x[1]) - myFunc(x[2])) / (x[2] - x[0]);


	// In the middle: Two-point central difference
	for (int i = 1; i < m - 1; i++) {
		dydx[i] = (myFunc(x[i + 1]) - myFunc(x[i - 1])) / (x[i + 1] - x[i - 1]);
	}

	// The last point: Three-point backward for the last point
	dydx[m - 1] = (myFunc(x[m - 3]) - 4 * myFunc(x[m - 2]) + 3 * myFunc(x[m - 1])) / (x[m - 1] - x[m - 3]);

}


/*-- 2nd order differentiation-----------------------------*/
void acceleration(double x[], double y[], double dy2dx2[], int m) {

	double h = x[1] - x[0];

	// First Point: Four-point forward difference  
	dy2dx2[0] = (2 * y[0] - 5 * y[1] + 4 * y[2] - y[3]) / power(h, 2.0);

	// Mid Point: Three-point central difference
	for (int i = 1; i < m - 1; i++) {
		dy2dx2[i] = (y[i - 1] - 2 * y[i] + y[i + 1]) / power(h, 2.0);
	}

	// End Point:	Four-point backward difference
	dy2dx2[m - 1] = (-y[m - 4] + 4 * y[m - 3] - 5 * y[m - 2] + 2 * y[m - 1]) / power(h, 2.0);
}


/*-- 2nd order differentiation < with FUNCTION CALL > -----------------------------*/
void acceleration_value(double myFunc(const double x), double x[], double dy2dx2[], int m)
{
	double h = x[1] - x[0];

	// First Point: Four-point forward difference  
	dy2dx2[0] = (2 * myFunc(0) - 5 * myFunc(1) + 4 * myFunc(2) - myFunc(3)) / power(h, 2.0);

	// Mid Point: Three-point central difference
	for (int i = 1; i < m - 1; i++) {
		dy2dx2[i] = (myFunc(i - 1) - 2 * myFunc(i) + myFunc(i + 1)) / power(h, 2.0);
	}

	// End Point:	Four-point backward difference
	dy2dx2[m - 1] = (-myFunc(m - 4) + 4 * myFunc(m - 3) - 5 * myFunc(m - 2) + 2 * myFunc(m - 1)) / power(h, 2.0);
}



/*==========================================================================*/
/*                            Interpolation               	   		*/
/*==========================================================================*/

double Lagrange(double x[], double y[], int n, double x_in)   // (n)th polynomial --> for loop index until (n+1)!!!
{
	double L, y_out = 0;

	for (int i = 0; i < n + 1; i++) {
		L = 1.0;	// initialization of L
		for (int j = 0; j < n + 1; j++) {
			if (j == i)
				continue;

			L = L * ((x_in - x[j]) / (x[i] - x[j]));
		}
		y_out = y_out + y[i] * L;
	}

	return y_out;
}




/*==========================================================================*/
/*                            Integration                	   		*/
/*==========================================================================*/

/* --------------------------- */
/*    from a discrete data     */
/* --------------------------- */
double trapz(double x[], double y[], int m)
{
	/* m = # of points
	* N = intervals */
	double I = 0;
	int N = m - 1;

	for (int k = 0; k < N; k++) {
		I = I + (y[k + 1] + y[k]) * (x[k + 1] - x[k]) / 2;
	}

	return I;
}



// * assume constant h *

double simpson13(double x[], double y[], int m)	/* -----> make sure N is an even # !!! */
{
	// initialization
	double I = 0;
	int N = m - 1; // N=12
	double h = x[1] - x[0];

	// midpoints
	for (int k = 1; k < (N / 2); k++) {
		I = I + (h / 3) * (4 * y[2 * k - 1] + 2 * y[2 * k]);
	}

	// first & last point + last 4f(x)
	I = I + (h / 3) * (y[0] + 4 * y[N - 1] + y[N]);

	return I;
}


double simpson38(double x[], double y[], int m)	/* -----> make sure (N%3 == 0) !!! */
{
	// initialization
	double I = 0;
	int N = m - 1; // N=12
	double h = x[1] - x[0];

	// midpoints
	for (int k = 1; k < (N / 3); k++) {
		I = I + (3 * h / 8) * (3 * y[3 * k - 2] + 3 * y[3 * k - 1] + 2 * y[3 * k]);
	}

	// first & last point + last 4f(x)
	I = I + (3 * h / 8) * (y[0] + 3 * y[N - 2] + 3 * y[N - 1] + y[N]);

	return I;
}


/* --------------------------- */
/*     from a function     */
/* --------------------------- */
double integral(double func(const double x), double a, double b, int n)
{
	int N = n;  // interval N
	double h = (b - a) / n;
	double I = 0;

	int midN = n - 3; // =====> must be even #

	if (N % 2 == 0) { /* ------- simpson13 -------- */

		// midpoints
		for (int k = 1; k < (N / 2); k++) {
			I = I + (h / 3) * (4 * func(a + (2 * k - 1) * h) + 2 * func(a + 2 * k * h));
		}

		// first & last point + last 4f(x)
		I = I + (h / 3) * (func(a) + 4 * func(b - h) + func(b));

	}
	else if (N % 3 == 0) {  /* ------- simpson38 -------- */

		// midpoints
		for (int k = 1; k < (N / 3); k++) {
			I = I + (3 * h / 8) * (3 * func(a + (3 * k - 2) * h) + 3 * func(a + (3 * k - 1) * h) + 2 * func(a + (3 * k) * h));
		}

		// first & last point + last 4f(x)
		I = I + (3 * h / 8) * (func(a) + 3 * func(b - 2 * h) + 3 * func(b - h) + func(b));

	}
	else { /* --------- simpson13 & 38 together -----------*/
		
		// midpoints  -- simpson13
		for (int k = 1; k < (midN / 2); k++) {
			I = I + (h / 3) * (4 * func(a + (2 * k - 1) * h) + 2 * func(a + 2 * k * h));
		}

		// first & last point + last 4f(x)
		I = I + (h / 3) * (func(a) + 4 * func((a + midN * h) - h) + func(a + midN * h));


		// last three points -- simpson38
		I = I + (3 * h / 8) * (func(b - 3 * h) + 3 * func(b - 2 * h) + 3 * func(b - h) + func(b));

	}

	return I;
}




/*==========================================================================*/
/*                            ODE             	   		*/
/*==========================================================================*/

void odeEU(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h,
	const double y_init)
{
	// 
	// [BRIEF DESCRIPTION OF THE FUNCTION  GOES HERE]
	// 
		// Variable Initialization
	double K1 = 0, K2 = 0;
	int N = (tf - t0) / h + 1;

	//Initial Condition
	double t = t0;
	y[0] = y_init;

	// Euler Explicit ODE Method
	for (int i = 0; i < N - 1; i++) {
		// First-point Gradient	
		K1 = odeFunc(t, y[i]);

		// Estimate: yE(i+1)= y(i) + K1 * h;
		y[i + 1] = y[i] + K1 * h;

		// Update Time step		
		t += h;
	}
}


void odeRK2(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h,
	const double y_init)
{
	// 
	// [BRIEF DESCRIPTION OF THE FUNCTION  GOES HERE]
	// 

		// Variable Initialization
	int N = (tf - t0) / h + 1;
	double y2 = 0;
	double t2 = 0;	// 중간(임시) y

	// Initial Condition
	double ti = t0;
	y[0] = y_init;

	// RK Design Parameters
	double C1 = 0.5;
	double C2 = 1 - C1;
	double alpha = 1;
	double beta = alpha;
	double K1 = 0, K2 = 0;

	// RK2 ODE Solver
	for (int i = 0; i < N - 1; i++) {

		// [First-point Gradient]
		K1 = odeFunc(ti, y[i]);

		// [Second-point Gradient]
		// Calculate t2=t(i)+alpha*h
		t2 = ti + alpha * h;

		// Calculate y2 = y(i) + beta * K1 * h
		y2 = y[i] + beta * K1 * h;

		// Calculate: K2   using t2 and y2	
		K2 = odeFunc(t2, y2);


		// Estimate: y(i+1) using RK2 
		y[i + 1] = y[i] + (C1 * K1 + C2 * K2) * h;

		ti += h;
	}
}



void odeRK3(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h,
	const double y0)
{
	// 
	// [BRIEF DESCRIPTION OF THE FUNCTION  GOES HERE]
	// 

		// Variable Initialization
	int N = (tf - t0) / h + 1;
	double y2, y3 = 0;
	double t2, t3 = 0;

	// Initial Condition
	double ti = t0;
	y[0] = y0;

	// RK Design Parameters
	double C1 = 1.0 / 6.0;
	double C2 = 4.0 / 6.0;
	double C3 = 1.0 / 6.0;
	double alpha2 = 0.5, alpha3 = 1;
	double beta21 = 0.5, beta31 = -1, beta32 = 2.0;
	double K1 = 0, K2 = 0, K3 = 0;

	// RK2 ODE Solver
	for (int i = 0; i < N - 1; i++) {

		// [First-point Gradient]
		K1 = odeFunc(ti, y[i]);

		// [Second-point Gradient]
		// Calculate t3, y3, and K3
		t2 = ti + alpha2 * h;
		y2 = y[i] + beta21 * K1 * h;
		K2 = odeFunc(t2, y2);

		// Calculate t3, y3, and K3
		t3 = ti + alpha3 * h;
		y3 = y[i] + beta31 * K1 * h + beta32 * K2 * h;
		K3 = odeFunc(t3, y3);


		// Estimate: y(i+1) using RK2 
		y[i + 1] = y[i] + (C1 * K1 + C2 * K2 + C3 * K3) * h;

		ti += h;
	}

}


// ODE RK2 for 2nd order ODE 
void sys2RK2(double y1[], double y2[], void odeFuncSys(double dYdt[], const double t, const double Y[]), const double t0,
	const double tf, const double h, const double y1_init, const double y2_init)
{
	// 
	// [BRIEF DESCRIPTION OF THE FUNCTION  GOES HERE]
	// 

	// Variable Initialization
	int N = (tf - t0) / h + 1;
	double ti = t0;
	double t2; // 중간 임시 t

	// Initial Condition	
	y1[0] = y1_init;	// _1 = y
	y2[0] = y2_init;	// _2 = z  ... 나는 인덱스 0->y, 1->v 하고싶은데 여기서 y1은 y, y2는 v 줘버려서 따로 다시 정의해줘야함

	// RK Design Parameters
	double C1 = 0.5;
	double C2 = 1 - C1;
	double alpha = 1;
	double beta = alpha;
	double K1[2] = { 0 };
	double K2[2] = { 0 };

	double yi[2] = { 0 };	// yi[0] = 현재y(i), yi[1] = 현재v(i)
	double yE[2] = { 0 }; // yE[0] = 임시y(i+1), yE[1] = 임시v(i+1)
	//double dYdt[2] = { 0 };		// K1, dYdt[0] = dydt / dYdt[1] = dvdt
	//double dYdt2[2] = { 0 };	// K2  ... 이걸 따로 만들 필요가 없지 않나...?


	// RK2 ODE for 2nd ODE
	for (int i = 0; i < N - 1; i++) {
		yi[0] = y1[i];	// current y
		yi[1] = y2[i];	// current v

		// First - point Gradient
		odeFuncSys(K1, ti, yi);		// slope K1 @ current y(i) and v(i)
		/*K1[0] = dYdt[0];
		K1[1] = dYdt[1];*/

		// [Second - point Gradient]
		// calculate t2 = t(i) + alpha * h
		t2 = ti + alpha * h;

		// calculate y2 = y(i) + beta * Ky1 * h -> 오일러로 다음값 y_(i + 1) 대충 추정
		yE[0] = y1[i] + beta * K1[0] * h;

		// calculate v2 = v(i) + beta * Kv1 * h -> 오일러로 다음값 v_(i + 1) 대충 추정
		yE[1] = y2[i] + beta * K1[1] * h;


		odeFuncSys(K2, t2, yE);		// slope K2 @ the next y(i+1) and v(i+1)

		// Calculate: Ky2   using t2 and y2 and v2
		//K2[0] = dYdt2[0];

		// Calculate: Kv2   using t2 and y2 and v2
		//K2[1] = dYdt2[1];

		// Estimate: y(i + 1) using RK2% 다음값 추정
		y1[i + 1] = y1[i] + (C1 * K1[0] + C2 * K2[0]) * h;

		// Estimate: v(i + 1) using RK2
		y2[i + 1] = y2[i] + (C1 * K1[1] + C2 * K2[1]) * h;


		ti += h;

	}	// end for


}
