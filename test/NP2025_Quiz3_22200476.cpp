/*----------------------------------------------------------------\
@ Numerical Programming by Young-Keun Kim - Handong Global University

Author           : Yu Chaeeun
Created          : 10-07-2025

Description      : Quiz 3 - ODE 2025
----------------------------------------------------------------*/

#include "stdio.h"
#include "stdlib.h"
#include <math.h>
#define PI 3.14159265358979323846264338327950288419716939937510582
// DO NOT Include your library "myNP.h"

double odeFunc_rc(const double t, const double v);
void odeFunc_mck(double dYdt[], const double t, const double Y[]);

void odeRK2(double odeFunc(const double t, const double y), double y[], const double t0, const double tf, const double h, const double y0);
void odeRK3(double odeFunc(const double t, const double y), double y[], const double t0, const double tf, const double h, const double y0);
void sys2RK2(void odeFuncSys(double dYdt[], const double t, const double Y[]), double y1[], double y2[], const double t0, const double tf, const double h, const double y1_init, const double y2_init);



int main(int argc, char* argv[])
{
    /*------------------------------------------------------------------------------------------*/
    /*==========================================================================*/
    /*					Part 1:  1st order ODE-IVP (single equation)			*/
    /*--------------------------------------------------------------------------*/
    /*   - A simple RC circuit response to sinusoidal voltage input				*/
    /*   - You can change the variable names									*/
    /*   - You can create additional functions									*/
    /*==========================================================================*/

    /*==========================================================================*/
    /*						Initialization										*/
    /*==========================================================================*/
    // Initial Conditions
    double a = 0;
    double b = 0.1;
    double h = 0.001;

    double y_RK2[200] = { 0 };
    double y_RK3[200] = { 0 };

    // IVP initial values
    double y0 = 0;

    /*==========================================================================*/
    /*					Apply your numerical method algorithm					*/
    /*==========================================================================*/
    //  Runge-Kutta 2nd order
    odeRK2(odeFunc_rc, y_RK2, a, b, h, y0);

    //  Runge-Kutta 3rd order
    odeRK3(odeFunc_rc, y_RK3, a, b, h, y0);

    /*==========================================================================*/
    /*							  Print your results							*/
    /*==========================================================================*/

    // Print outputs
    printf("----------------------------------------------------------\n");
    printf("                1st ODE - IVP  Results						\n");
    printf("----------------------------------------------------------\n");

    printf("t\t yRK2\t\t yRK3\t \n\n");
    printf("%.1f\t %.5f\t %.5f\t \n", 1.0, y_RK2[100], y_RK3[100]);
    printf("\n");

    /*------------------------------------------------------------------------------------------*/

    /*==========================================================================*/
    /*					Part 2:  2nd order ODE-IVP	with mck 					*/
    /*--------------------------------------------------------------------------*/
    /*   - A simple m-c-k  response to sinusoidal force input					*/
    /*   - You can change the variable names									*/
    /*   - You can create additional functions									*/
    /*==========================================================================*/

    /*==========================================================================*/
    /*						Initialization										*/
    /*==========================================================================*/
    // Parameter Definitions
    double t0 = 0;
    double tf = 1;
    h = 0.01;
    double Y_RK2[200] = { 0 };
    double V_RK2[200] = { 0 };

    // Initial values
    double y_initQ2 = 0;
    double v_initQ2 = 0.2;

    /*==========================================================================*/
    /*					Apply your numerical method algorithm					*/
    /*==========================================================================*/
    //  Runge-Kutta 2nd order
    sys2RK2(odeFunc_mck, Y_RK2, V_RK2, t0, tf, h, y_initQ2, v_initQ2);

    /*==========================================================================*/
    /*							  Print your results							*/
    /*==========================================================================*/
    //
    printf("----------------------------------------------------------\n");
    printf("                2nd order ODE - IVP  Results		      \n");
    printf("----------------------------------------------------------\n");

    double dYdt_Q2[2] = { 0 }, Y_Q2[2] = { Y_RK2[100], V_RK2[100] };
    odeFunc_mck(dYdt_Q2, 1.0, Y_Q2);

    printf("t\t Y_RK2\t\t V_RK2\t\t Acc\t\t \n\n");
    printf("%.1f\t %0.5f\t %.5f\t %.5f\t \n", 1.0, Y_RK2[100], V_RK2[100], dYdt_Q2[1]);
    printf("\n");

    system("pause");
    return 0;
}


/*==========================================================================*/
/*						MODIFY HERE FROM HERE 										*/
/*==========================================================================*/

/*==========================================================================*/
/*					Part 1:  1st order ODE-IVP (single equation)			*/
/*--------------------------------------------------------------------------*/
void odeRK2(double odeFunc(const double t, const double y), double y[], const double t0, const double tf, const double h, 
    const double y0) {

    // variable initialization
    double K1 = 0.0, K2 = 0.0, t2 = 0.0, y2 = 0.0;
    int N = (tf - t0) / h + 1;

    // initialization
    y[0] = y0;
    double ti = t0;

    // RK parameter
    double C1 = 0.5;   
    double C2 = 1 - C1;
    double alpha = 1;
    double beta = alpha;

    // RK2 solver
    for (int i = 0; i < N - 1; i++) {
        K1 = odeFunc(ti, y[i]);

        // next tmp t2, y2
        t2 = ti + alpha * h;
        y2 = y[i] + beta * K1 * h;

        K2 = odeFunc(t2, y2);

        // next y
        y[i + 1] = y[i] + (C1 * K1 + C2 + K2) * h;
        
        ti += h;
    }

}

void odeRK3(double odeFunc(const double t, const double y), double y[], const double t0, const double tf, const double h, 
    const double y0) {

    // variable initialization
    double K1 = 0, K2 = 0, K3 = 0;
    int N = (tf - t0) / h + 1;

    // initialization
    double ti = t0;
    y[0] = y0;
    double t2 = 0, y2 = 0;
    double t3 = 0, y3 = 0;

    // RK parameter
    double C1 = 1.0 / 6.0;
    double C2 = 4.0 / 6.0;
    double C3 = 1.0 / 6.0;
    double alpha2 = 0.5; 
    double alpha3 = 1;
    double beta21 = 0.5;
    double beta31 = -1;
    double beta32 = 2;

    // RK solver
    for (int i = 0; i < N - 1; i++) {
        K1 = odeFunc(ti, y[i]);

        t2 = ti + alpha2 * h;
        y2 = y[i] + beta21 * K1 * h;

        K2 = odeFunc(t2, y2);

        t3 = ti + alpha3 * h;
        y3 = y[i] + beta31 * K1 * h + beta32 * K2 * h;

        K3 = odeFunc(t3, y3);

        y[i + 1] = y[i] + (C1 * K1 + C2 * K2 + C3 * K3) * h;

        ti += h;
    }

}

/*==========================================================================*/
/*					Part 2:  2nd order ODE-IVP								*/
/*--------------------------------------------------------------------------*/
void odeFunc_mck(double dYdt[], const double t, const double Y[]) {
    // Input:	 vecY = [y; z], t
    // Output:	 dYdt = [dydt; dvdt]

    double m = 1.0; 
    double k = 6.9;
    double c = 7.0;
    double A = 2.0;
    double f = 5.0;
    double omega = 2 * PI * f;

    dYdt[0] = Y[1];
    dYdt[1] = (( - k * Y[0]) - c * Y[1] + A * cos(omega * t)) / m;
   
}

void sys2RK2(void odeFuncSys(double dYdt[], const double t, const double Y[]), double y1[], double y2[], 
    const double t0, const double tf, const double h, const double y1_init, const double y2_init) {

    // variable initialization
    double K1[2] = { 0 };
    double K2[2] = { 0 };
    int N = (tf - t0) / h + 1;
    double t2 = 0;
    double yE[2] = { 0 };   // tmp y/ yE[0]->y, yE[1]->z 

    // initialization
    double ti = t0;
    y1[0] = y1_init;    // y1 -> y
    y2[0] = y2_init;    // y2 -> z
   
    // RK parameters
    double C1 = 0.5;
    double C2 = 1 - C1;
    double alpha = 1;
    double beta = alpha;

    double yi[2] = { 0 };   // for determining K1

    // sys2RK2 solver
    for (int i = 0; i < N - 1; i++) {
        yi[0] = y1[0];
        yi[1] = y2[0];

        odeFuncSys(K1, ti, yi);

        // determine the next tmp
        t2 = ti + alpha * h;
        yE[0] = y1[i] + beta * K1[0] * h;
        yE[1] = y2[i] + beta * K1[1] * h;

        odeFuncSys(K2, t2, yE);

        y1[i + 1] = y1[i] + (C1 * K1[0] + C2 * K2[0]) * h;
        y2[i + 1] = y2[i] + (C1 * K1[1] + C2 * K2[1]) * h;

        ti += h;
    }
    
}



/*==========================================================================*/
/*						Function Definitions	(Given), DON'T MODIFY     	*/
/*==========================================================================*/
double odeFunc_rc(const double t, const double v) {
    // Input:	 y, t
    // Output:	 dydt

    // system modeling parameters
    double tau = 0.01;
    double f = 100;
    double Vm = 1;
    double omega = 2 * PI * f;
    double dvdt = 0;

    // output
    dvdt = (Vm * cos(omega * t) - v) / tau;

    return dvdt;
}


