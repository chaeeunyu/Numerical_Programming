/* myNP_tutorial.h */
#ifndef		_MY_NP_H		// use either (#pragma once) or  (#ifndef ...#endif)
#define		_MY_NP_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define		PI		3.14159265358979323846264338327950288419716939937510582

extern void printVec(double* vec, int row);

//============================ Sine Taylor =========================================
double factorial(int _x);
double power(double _x, int N);

double sinTaylor(double _x);
double sindTaylor(double _x);
double cosTaylor(double x);


//============================ Non-Linear ===============================================

double func(double x);
double dfunc(double x);
double bisection(float _a0, float _b0, float _tol);
double newtonRaphson(double func(double x), double dfunc(double x), double _x0, double _tol);


#endif#pragma once
