#ifndef STUDIO_CONICA_H
#define STUDIO_CONICA_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

//elemento matrice (mat puntatore)
#define ELEM(mat, r, c) ((mat)->data[(r) * (mat)->cols + (c)])

//punto coordinate
#define _o (0)
#define _x (1)
#define _y (2)

//coefficenti equazione conica
#define _a (0)
#define _b (1)
#define _c (2)
#define _d (3)
#define _e (4)
#define _f (5)

//TIPO CONICA 0 -> degenere, 1 -> iperbole, 2 -> parabola, 3 -> ellisse
#define DEGENERE (0)
#define IPERBOLE (1)
#define PARABOLA (2)
#define ELLISSE (3)

//matrice
typedef struct matrix {
	size_t rows, cols;
	double* data;
}matrix;

//punto in coordinate omogenee
typedef struct punto {
	double xyz[3];//coordinate omogenee
}punto;

//retta polare in forma ax + by + c = 0 e suo (punto) polo
typedef struct retta_pol {
	punto polo;//Coordinate omo del polo della retta polare
	double abc[3];//ax + by + c = 0
}retta_pol;

typedef struct autoval_mat2x2 {
	double autoval[2];//Autovalori della matrice 2x2, se sono entrambi 0 c'è un problema
}autoval_mat2x2;

//monomio con solo 1 lettera in forma (coeff)*(lettera)^(exp)
typedef struct monomio {
	double coeff;
	char lettera;//Il monomio accetta una sola lettera come parte lettterale
	size_t exp;//esponente lettera
}monomio;

//array di monomi 
typedef struct polinomio {
	size_t n_mon;//numero di monomi contenuti
	monomio* mon;//array di monomi nella forma (mon0) + (mon1) + (mon2) + ... | In cui grado(mon0) > grado(mon1) ...
}polinomio;

#endif // !STUDIO_CONICA_H

/*
ESEMPIO CONICA
iperbole
0x^2 - 6xy + 8y^2 + 6x - 4y - 13 = 0
0 -6 8 6 -4 -13
1 6 1 0 0 -3

ellisse
7 -2 7 -24 -24 0

parabola
1 -4 4 -14 -2 3
*/
