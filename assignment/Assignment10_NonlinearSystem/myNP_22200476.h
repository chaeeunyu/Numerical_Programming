/* myNP_22200476.h */
#ifndef		_MY_NP_H		// use either (#pragma once) or  (#ifndef ...#endif)
#define		_MY_NP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define		PI		3.14159265358979323846264338327950288419716939937510582

extern void printVec(double* vec, int row);
double deg(double x);
double rad(double x);

//============================ Sine Taylor =========================================
double factorial(int _x);
double power(double _x, int N);

double sinTaylor(double _x);
double sindTaylor(double _x);
double cosTaylor(double x);


//============================ Non-Linear ===============================================

double bisection(double func(double x), float _a0, float _b0, float _tol);
double newtonRaphson(double func(double x), double dfunc(double x), double _x0, double _tol);
double secantfzero(double func(double x), double x0, double x1, double tol);


//======================== Differentiation ============================================
void gradient1D(double x[], double y[], double dydx[], int m);
void gradientFunc(double myFunc(const double x), double x[], double dydx[], int m);
void acceleration(double x[], double y[], double dy2dx2[], int m);

void acceleration_value(double myFunc(const double x), double x[], double dy2dx2[], int m);


//=============================== Interpoltion ========================================
double Lagrange(double x[], double y[], int n, double x_in);


//=============================== Integration ========================================
double trapz(double x[], double y[], int m);
double simpson13(double x[], double y[], int m);
double simpson38(double x[], double y[], int m);
double integral(double func(const double x), double a, double b, int n);


//=============================== ODE ========================================
// 1st order ODE
void odeEU(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y_init);
void odeRK2(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y_init);
void odeRK3(double y[], double odeFunc(const double t, const double y), const double t0, const double tf, const double h, const double y0);

// 2nd order ODE
void sys2RK2(double y1[], double y2[], void odeFuncSys(double dYdt[], const double t, const double Y[]), const double t0, const double tf, const double h, const double y1_init, const double y2_init);


//=============================== CurveFit ========================================
// Calculates coefficients of least squares regression - Line
void linearRegression(double z_opt[], double xdata[], double ydata[], int dataN);

// Non-linear curve fitting (exp)
void expRegression(double z_opt[], double xdata[], double ydata[], int dataN);

#endif#pragma once
