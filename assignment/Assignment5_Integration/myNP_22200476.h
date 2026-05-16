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


//=============================== Integration ========================================
double trapz(double x[], double y[], int m);
double simpson13(double x[], double y[], int m);
double simpson38(double x[], double y[], int m);
double integral(double func(const double x), double a, double b, int n);


#endif#pragma once
