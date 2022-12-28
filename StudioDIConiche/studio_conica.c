#include "studio_conica.h"

punto crea_punto(double o, double x, double y)
{
	punto pnt;
	pnt.xyz[_o] = o;
	pnt.xyz[_x] = x;
	pnt.xyz[_y] = y;

	return pnt;
}

retta_pol retta_polare(const matrix* A, punto polo)
{
	retta_pol r = { 0 };
	if (A == NULL)
	{
		printf("\nERRORE, cercata una retta polare di una matrice NULL");
		return r;
	}
	r.polo = crea_punto(polo.xyz[_o], polo.xyz[_x], polo.xyz[_y]);
	
	r.abc[_a] = ELEM(A, 1, 0) * polo.xyz[0] +
		ELEM(A, 1, 1) * polo.xyz[_x] +
		ELEM(A, 1, 2) * polo.xyz[_y];

	r.abc[_b] = ELEM(A, 2, 0) * polo.xyz[0] +
		ELEM(A, 2, 1) * polo.xyz[_x] +
		ELEM(A, 2, 2) * polo.xyz[_y];

	r.abc[_c] = ELEM(A, 0, 0) * polo.xyz[_o] +
		        ELEM(A, 0, 1) * polo.xyz[_x] +
		        ELEM(A, 0, 2) * polo.xyz[_y];

	return r;
}

void free_mat(matrix * m)
{
	if (m == NULL)
		return;
	if (m->data != NULL)
	{
		free(m->data);
	}
	free(m);
}

void Crea_matrice_associata(const double* coeff, matrix *mat, matrix *min_00, matrix* min_01, matrix* min_02)
{
	if (mat == NULL)
	{
		printf("ERRORE, matrice inesistente\n");
		return;
	}
	if (mat->data == NULL)
	{
		printf("ERRORE, dati matrice inesistenti\n");
		return;
	}
	if (coeff == NULL)
	{
		printf("ERRORE, coefficient matrice inesistenti\n");
		return;
	}
	
	/*
	f	 d/2  e/2
	d/2	  a	  b/2
	e/2  b/2   c
	*/

	ELEM(mat, 0, 0) = coeff[_f];
	ELEM(mat, 1, 1) = coeff[_a];
	ELEM(mat, 2, 2) = coeff[_c];

	ELEM(mat, 1, 0) = ELEM(mat, 0, 1) = coeff[_d] / 2;
	ELEM(mat, 2, 0) = ELEM(mat, 0, 2) = coeff[_e] / 2;

	ELEM(mat, 1, 2) = ELEM(mat, 2, 1) = coeff[_b] / 2;

	//creazione minore min_00
	if (min_00 == NULL || min_01 == NULL || min_02 == NULL)
		return;
	/*
	00 01 02
	10 11 12
	20 21 22
	*/

	if (min_00 != NULL)
	{
		ELEM(min_00, 0, 0) = ELEM(mat, 1, 1);
		ELEM(min_00, 0, 1) = ELEM(mat, 1, 2);
		ELEM(min_00, 1, 0) = ELEM(mat, 2, 1);
		ELEM(min_00, 1, 1) = ELEM(mat, 2, 2);
	}
	if (min_01 != NULL)
	{
		ELEM(min_01, 0, 0) = ELEM(mat, 1, 0);
		ELEM(min_01, 0, 1) = ELEM(mat, 1, 2);
		ELEM(min_01, 1, 0) = ELEM(mat, 2, 0);
		ELEM(min_01, 1, 1) = ELEM(mat, 2, 2);
	}
	if (min_02 != NULL)
	{
		ELEM(min_02, 0, 0) = ELEM(mat, 1, 0);
		ELEM(min_02, 0, 1) = ELEM(mat, 1, 1);
		ELEM(min_02, 1, 0) = ELEM(mat, 2, 0);
		ELEM(min_02, 1, 1) = ELEM(mat, 2, 1);
	}
}

void Stampa_matrice(const matrix *mat)
{
	if (mat == NULL)
	{
		printf("ERRORE, matrice inesistente\n");
		return;
	}
	if (mat->data == NULL)
	{
		printf("ERRORE, dati matrice inesistenti\n");
		return;
	}
	
	for (size_t r = 0; r < mat->rows; r++)
	{
		for (size_t c = 0; c < mat->cols; c++)
		{
			if (ELEM(mat, r, c) >= 0)
			{
				printf(" ");
			}
			printf("%5.4f ", ELEM(mat, r, c));
		}
		printf("\n");
	}
	
	/*
	printf("| %5.4f | %5.4f | %5.4f |", ELEM(mat, 0, 0), ELEM(mat, 0, 1), ELEM(mat, 0, 2));
	printf("\n");
	printf("| %5.4f | %5.4f | %5.4f |", ELEM(mat, 1, 0), ELEM(mat, 1, 1), ELEM(mat, 1, 2));
	printf("\n");
	printf("| %5.4f | %5.4f | %5.4f |", ELEM(mat, 2, 0), ELEM(mat, 2, 1), ELEM(mat, 2, 2));
	*/
	printf("\n");
}

double determinante_mat(const matrix* m)
{
	double det = 999999999;
	
	if (m->cols != m->rows)
	{
		//controllo matrice quadrata
		printf("\nERRORE, cercando ci calcolare un det di una matrice non quadrata\n");
	}
	else if (m->cols == 3)
	{
		/*
		00 01 02
		10 11 12
		20 21 22
		*/
		det = ELEM(m, 0, 0) * ELEM(m, 1, 1) * ELEM(m, 2, 2) +
			ELEM(m, 1, 0) * ELEM(m, 2, 1) * ELEM(m, 0, 2) +
			ELEM(m, 0, 1) * ELEM(m, 1, 2) * ELEM(m, 2, 0) -

			ELEM(m, 0, 2) * ELEM(m, 1, 1) * ELEM(m, 2, 0) -
			ELEM(m, 1, 2) * ELEM(m, 2, 1) * ELEM(m, 0, 0) -
			ELEM(m, 1, 0) * ELEM(m, 0, 1) * ELEM(m, 2, 2);
	}
	else if (m->cols == 2)
	{
		/*
		00 01
		10 11
		*/
		det = ELEM(m, 0, 0) * ELEM(m, 1, 1) - ELEM(m, 1, 0) * ELEM(m, 0, 1);
	}

	return det;
}

//ax^2 + bx + c
unsigned int sol_equaz_secondo_grado(const double abc[3], double* sol1, double* sol2)
{
	if (abc[_a] == 0 && abc[_b] == 0)
		return 0;

	if (abc[_a] != 0)
	{
		if (abc[_b] * abc[_b] - 4 * abc[_a] * abc[_c] < 0)
			return 0;

		*sol1 = (-abc[_b] + sqrt(abc[_b] * abc[_b] - 4 * abc[_a] * abc[_c])) / (2 * abc[_a]);
		*sol2 = (-abc[_b] - sqrt(abc[_b] * abc[_b] - 4 * abc[_a] * abc[_c])) / (2 * abc[_a]);
		return 2;
	}
	else if (abc[_a] == 0)
	{
		*sol1 = 0;
		*sol2 = -abc[_c] / abc[_b];
		return 3;
	}

	return 0;
}

//cancella polinomio dalla memora
void free_pol(polinomio* pol)
{
	if (pol == NULL)
		return;
	if (pol->mon != NULL)
	{
		free(pol->mon);
	}
	free(pol);
}

//crea pol grado 2 
//(coef_a)x^2 + (coef_b)x + (coef_c)
polinomio* crea_pol(const double coef_a, const double coef_b, const double coef_c, const char lettera)
{
	if (lettera < 'a' || lettera > 'z')
	{
		printf("\nERRORE, creato un polinomio con lettera non dentro l'alfabeto\n");
		return NULL;
	}
	//creazione polinomio
	polinomio* pol = malloc(sizeof(polinomio));
	if (pol == NULL)
	{
		free_pol(pol);
		return NULL;
	}
	pol->n_mon = 3;
	pol->mon = malloc(sizeof(monomio) * pol->n_mon);
	if (pol->mon == NULL)
	{
		free_pol(pol);
		return NULL;
	}

	//Inizializzazione polinomio
	pol->mon[0].coeff = coef_a;
	pol->mon[1].coeff = coef_b;
	pol->mon[2].coeff = coef_c;

	pol->mon[0].exp = 2;
	pol->mon[1].exp = 1;
	pol->mon[2].exp = 0;

	pol->mon[0].lettera = lettera;
	pol->mon[1].lettera = lettera;
	pol->mon[2].lettera = lettera;

	return pol;
}

//polinomi convertito nella forma (coef1)a^2 + (coef2)a^1 + (coef3)b^0
polinomio* standardizza_pol(polinomio* pol1)
{
	if (pol1 == NULL)
	{
		printf("\nERRORE, si è cercati di standardizzare un polinomio NULL\n");
		return NULL;
	}
	if (pol1->n_mon > 3)
	{
		printf("\nERRORE, si è cercati di standardizzare un polinomio con piu di 3 monomi\n");
		return NULL;
	}

	polinomio* temp = crea_pol(0, 0, 0, 'b');

	if (pol1->n_mon == 1)
	{
		temp->mon[2].coeff = pol1->mon[0].coeff;
		temp->mon[2].exp = pol1->mon[0].exp;
		temp->mon[2].lettera = pol1->mon[0].lettera;
	}
	else if (pol1->n_mon == 2)
	{
		//0 1 2
		temp->mon[1].coeff = pol1->mon[0].coeff;
		temp->mon[1].exp = pol1->mon[0].exp;
		temp->mon[1].lettera = pol1->mon[0].lettera;

		temp->mon[2].coeff = pol1->mon[1].coeff;
		temp->mon[2].exp = pol1->mon[1].exp;
		temp->mon[2].lettera = pol1->mon[1].lettera;
	}
	else
	{
		temp->mon[0].coeff = pol1->mon[0].coeff;
		temp->mon[0].exp = pol1->mon[0].exp;
		temp->mon[0].lettera = pol1->mon[0].lettera;

		temp->mon[1].coeff = pol1->mon[1].coeff;
		temp->mon[1].exp = pol1->mon[1].exp;
		temp->mon[1].lettera = pol1->mon[1].lettera;

		temp->mon[2].coeff = pol1->mon[2].coeff;
		temp->mon[2].exp = pol1->mon[2].exp;
		temp->mon[2].lettera = pol1->mon[2].lettera;
	}
	//free_pol(pol1);
	return temp;
}

//pol1 * pol2 [esempio ris : (coef1)a^2 + (coef2)a + (coef3)] 
//Max grado pol restituito -> 2
polinomio* molt_pol(const polinomio* pol1, const polinomio* pol2) 
{
	if (pol1 == NULL || pol2 == NULL)
	{
		printf("\nERRORE, tentata moltiplicazione tra polinomi NULL\n");
		return NULL;
	}
	if ((pol1->n_mon > 2 || pol2->n_mon > 2) && (pol1->mon[0].coeff != 0 || pol2->mon[0].coeff != 0))
	{
		printf("\nERRORE, tentata moltiplicazione tra polinomi di grado > 2\n");
		return NULL;
	}

	polinomio* molt = crea_pol(0, 0, 0, 'b');
	if (molt == NULL)
	{
		free_pol(molt);
		return NULL;
	}
	
	//conversione di pol1 e pol2 in forma (coef1)a^2 + (coef2)a + (coef3)
	polinomio* pol_1 = standardizza_pol(pol1);
	polinomio* pol_2 = standardizza_pol(pol2);
	
	//MOLTIPLICAZIONE
	//(a + b) * (a + d) = a^2 + (da + ba) + bd;
	molt->mon[0].coeff = pol_1->mon[1].coeff * pol_2->mon[1].coeff;
	molt->mon[0].exp = 2;// pol_1->mon[1].exp + pol_2->mon[1].exp;
	molt->mon[0].lettera = 'a';

	molt->mon[1].coeff = pol_1->mon[1].coeff * pol_2->mon[2].coeff + pol_2->mon[1].coeff * pol_1->mon[2].coeff;
	molt->mon[1].exp = 1;
	molt->mon[1].lettera = 'a';

	molt->mon[2].coeff = pol_1->mon[2].coeff * pol_2->mon[2].coeff;
	molt->mon[2].exp = 0;
	molt->mon[2].lettera = 'b';

	free(pol_1);
	free(pol_2);
	return molt;
}

//pol1 - pol2 [esempio ris : (coef1)a^2 + (coef2)a + (coef3)]
//grado pol1, pol2 <= 2
polinomio* sottr_pol(const polinomio* pol1, const polinomio* pol2) 
{
	if (pol1 == NULL || pol2 == NULL)
	{
		printf("\nERRORE, tentata sottrazzione tra polinomi NULL\n");
		return NULL;
	}
	if (pol1->mon[0].exp > 2 || pol2->mon[0].exp > 2)
	{
		printf("\nERRORE, tentata sottrazzione tra polinomi di grado > 2\n");
		return NULL;
	}

	polinomio* sottr = crea_pol(0, 0, 0, 'b');

	//conversione di pol1 e pol2 in forma (coef1)a^2 + (coef2)a + (coef3)
	polinomio* pol_1 = standardizza_pol(pol1);
	polinomio* pol_2 = standardizza_pol(pol2);
	if (sottr == NULL || pol_1 == NULL || pol_2 == NULL)
	{
		free_pol(sottr);
		free_pol(pol_1);
		free_pol(pol_2);
		return NULL;
	}

	//sottrazione tra polinomi di secondo grado
	for (size_t i = 0; i < 3; i++)
	{
		if (pol_1->mon[i].lettera == pol_2->mon[i].lettera && pol_1->mon[i].exp == pol_2->mon[i].exp && pol_1->mon[i].exp != 0)
		{
			sottr->mon[i].lettera = pol_1->mon[i].lettera;
			sottr->mon[i].exp = pol_1->mon[i].exp;
			sottr->mon[i].coeff = pol_1->mon[i].coeff - pol_2->mon[i].coeff;
		}
		else if (pol_2->mon[i].exp == 0 && pol_1->mon[i].exp == 0)
		{
			sottr->mon[i].lettera = 'b';
			sottr->mon[i].exp = 0;
			sottr->mon[i].coeff = pol_1->mon[i].coeff - pol_2->mon[i].coeff;
		}
		else
		{
			printf("\nERRORE, qualcosa non è andato nella somma tra polinomi\n");
		}
	}
	free(pol_1);
	free(pol_2);
	return sottr;
}

autoval_mat2x2 autovalori_matrice_2x2(const matrix *mat)
{
	
	autoval_mat2x2 a_mat2x2;
	a_mat2x2.autoval[0] = 0;
	a_mat2x2.autoval[1] = 0;
	if(mat == NULL)
	{
		printf("\nERRORE, cercato di calcolare gli autovalori di una matrice NULL\n");
		return a_mat2x2;
	}
	if (mat->cols > 2 || mat->rows > 2)
	{
		printf("\nERRORE, cercato di calcolare gli autovalori di una matrice con piu di 2 righe o colonne\n");
		return a_mat2x2;
	}
	/*matrice m 
	00 01
	10 11
	*/

	//creare una matrice di polinomi 
	//Il monomio di grado maggiore va sempre prima del monomio di grado minore
	//pol 00
	polinomio* pol_00 = crea_pol(0, 1, -ELEM(mat, 0, 0), 'a');
	//pol 01
	polinomio* pol_01  = crea_pol(0, 0, -ELEM(mat, 0, 1), 'a');
	//pol 10
	polinomio* pol_10 = crea_pol(0, 0, -ELEM(mat, 1, 0), 'a');
	//pol 11
	polinomio* pol_11 = crea_pol(0, 1, -ELEM(mat, 1, 1), 'a');

	//calcolare det matrice di polinomi (pol_00, pol_01, pol_10, pol_11)
	polinomio * diag1 = molt_pol(pol_00, pol_11);
	polinomio * diag2 = molt_pol(pol_01, pol_10);
	free_pol(pol_00);
	free_pol(pol_01);
	free_pol(pol_10);
	free_pol(pol_11);

	polinomio* det = sottr_pol(diag1, diag2);
	free_pol(diag1);
	free_pol(diag2);

	//det polinomio composto da 3 monomi (coef1)a^2 + (coef2)a + (coef3)
	double c[3] = {det->mon[0].coeff, det->mon[1].coeff , det->mon[2].coeff };
	free_pol(det);
	printf("\nIl det(tI - M_00) = (%.4f)t^2 + (%.4f)t + (%.4f)", c[0], c[1], c[2]);

	unsigned int sol = sol_equaz_secondo_grado(c, &a_mat2x2.autoval[0], &a_mat2x2.autoval[1]);

	return a_mat2x2;
}

//matrice m deve essere 2x2
punto autospazio(const double autoval, const matrix* m)
{
	punto pnt_auto = crea_punto(0, 0, 0);
	if (m == NULL)
	{
		printf("\nERRORE, cercato di calcolare gli autovalori di una matrice NULL\n");
		return pnt_auto;
	}
	if (m->cols > 2 || m->rows > 2)
	{
		printf("\nERRORE, cercato di calcolare gli autovalori di una matrice con piu di 2 righe o colonne\n");
		return pnt_auto;
	}

	matrix* mat_auto = malloc(sizeof(matrix));
	if (mat_auto == NULL)
	{
		free(mat_auto);
		return;
	}
	mat_auto->rows = 2;
	mat_auto->cols = 2;
	mat_auto->data = malloc(sizeof(mat_auto->data) * mat_auto->rows * mat_auto->cols);
	if (mat_auto->data == NULL)
	{
		free(mat_auto);
		return;
	}
	
	//calcolo matrice autospazio
	//diagonale principale
	ELEM(mat_auto, 0, 0) = - ELEM(m, 0, 0) + autoval;
	//ELEM(mat_auto, 1, 1) = ELEM(m, 1, 1) + autoval;
	//antidiagonale
	ELEM(mat_auto, 0, 1) = - ELEM(m, 0, 1);
	//ELEM(mat_auto, 1, 0) = ELEM(m, 1, 0);

	if (ELEM(mat_auto, 0, 0) == 0 && ELEM(mat_auto, 0, 1) != 0)
	{
		pnt_auto.xyz[_x] = 1;
		pnt_auto.xyz[_y] = 0;
	}
	else if (ELEM(mat_auto, 0, 0) != 0 && ELEM(mat_auto, 0, 1) == 0)
	{
		pnt_auto.xyz[_x] = 0;
		pnt_auto.xyz[_y] = 1;
	}
	else
	{
		pnt_auto.xyz[_x] = 1;
		pnt_auto.xyz[_y] = -ELEM(mat_auto, 0, 0) / ELEM(mat_auto, 0, 1);
	}

	return pnt_auto;
}

double trova_d_ip_el(matrix * _D, double detA)
{
	if (_D == NULL)
	{
		printf("\nERRORE, passata matrice D NULL\n");
		return 0;
	}
	double detD = determinante_mat(_D);

	return detA / detD;
}

double trova_d_par(matrix* _D, double detA)
{
	if (_D == NULL)
	{
		printf("\nERRORE, passata matrice D NULL\n");
		return 0;
	}
	double detD = determinante_mat(_D);

	double d = sqrt(detA / detD);

	if (ELEM(_D, 1, 1) > 0)
	{
		d = -d;
	}

	return d;
}

bool sol_sistema_secondo_grado(const retta_pol r, const double conica[6], punto * sol1, punto * sol2)
{
	if (sol1 == NULL)
		return false;
	/*
	a1x		 + b1y	    + c1        = 0
	r.abc[_a]  r.abc[_b]  r.abc[_c]

	a2x^2 + b2xy + c2y^2 + d2x + e2y + f2 = 0
	0       1      2       3     4     5      conica
	---------------------------------------------
	x = (-b1/a1)y + (-c1/a1)

	a2( (-b1/a1)y + (-c1/a1) ) ^(2) + b2y( (-b1/a1)y + (-c1/a1) ) + c2y^(2) + d2( (-b1/a1)y + (-c1/a1) ) + e2y + f2 = 0

	a2( (-b1/a1)^(2)y^(2) + 2*y(-b1/a1)(-c1/a1) + (-c1/a1)^(2) ) + (-b1 * b2/a1)y^(2) + (-c1 * b2/a1)y + c2y^(2) + (-b1 * d2/a1)y + (-c1 * d2/a1) + e2y + f2 = 0

	a2(-b1/a1)^(2)y^(2) + 2*a2(-b1/a1)(-c1/a1)y + a2(-c1/a1)^(2) + ((-b1 * b2/a1) + c2)y^(2) + ((-c1 * b2/a1) + (-b1 * d2/a1) + e2)y + (f2 - c1 * d2/a1) = 0

	(a2(-b1/a1)(-b1/a1) + (-b1 * b2/a1) + c2)y^(2) + (2*a2(-b1/a1)(-c1/a1) + (-c1 * b2/a1) + (-b1 * d2/a1) + e2)y + (a2(-c1/a1)(-c1/a1) + f2 - c1 * d2/a1) = 0

	*/
	double a = conica[_a] * (r.abc[_b] / r.abc[_a]) * (r.abc[_b] / r.abc[_a]) + (- r.abc[_b] * conica[_b] / r.abc[_a]) + conica[_c];
	double b = (2 * conica[_a] * r.abc[_b] * r.abc[_c]) / (r.abc[_a] * r.abc[_a]) + (- r.abc[_c] * conica[_b] / r.abc[_a]) + (- conica[_d] * r.abc[_b] / r.abc[_a]) + conica[_e];
	double c = conica[_f] + (- r.abc[_c] * conica[_d] / r.abc[_a]) + conica[_a] * (r.abc[_c] / r.abc[_a]) * (r.abc[_c] / r.abc[_a]);
	
	double abc[3] = { a, b, c};
	double x1, x2, y1, y2;
	unsigned int tipo_sol = sol_equaz_secondo_grado(abc, &y1, &y2);
	if (tipo_sol == 0)
	{
		//printf("\nERRORE, soluzioni sistema impossibili c'è qualcosa che non va\n");
		return false;
	}
	else if (tipo_sol == 3)
	{
		x1 = (-r.abc[_b] / r.abc[_a]) * y2 + (-r.abc[_c] / r.abc[_a]);

		*sol1 = crea_punto(1, x1, y2);
	}
	else
	{
		if (sol2 == NULL)
		{
			return false;
		}
		x1 = (-r.abc[_b] / r.abc[_a]) * y1 + (-r.abc[_c] / r.abc[_a]);
		x2 = (-r.abc[_b] / r.abc[_a]) * y2 + (-r.abc[_c] / r.abc[_a]);

		*sol1 = crea_punto(1, x1, y1);
		*sol2 = crea_punto(1, x2, y2);
	}

	return true;
}

double distanza_punti(const punto pnt1, const punto pnt2)
{
	return sqrt((pnt1.xyz[1] - pnt2.xyz[1]) * (pnt1.xyz[1] - pnt2.xyz[1]) + (pnt1.xyz[2] - pnt2.xyz[2]) * (pnt1.xyz[2] - pnt2.xyz[2]));
}

void crea_crf(const punto centro, const double raggio, double crf[6])
{
	if (crf == NULL)
	{
		printf("\nERRORE, creazione circonferenza andata male\n");
		return;
	}

	crf[_a] = 1;
	crf[_b] = 0;
	crf[_c] = 1;
	crf[_d] = -2 * centro.xyz[_x];
	crf[_e] = -2 * centro.xyz[_y];
	crf[_f] = centro.xyz[_x] * centro.xyz[_x] + centro.xyz[_y] * centro.xyz[_y] - raggio * raggio;
}

int main(void)
{
	printf("------------------------------------------------------------------------------------\n");
	printf("STUDIO CONICA\n");

	double C[6] = { 0 }; //Coefficienti conica

	double mat_data[9] = { 0 };
	matrix A = { 3, 3, &mat_data }; //matrice associata alla conica

	double min_A00_data[4] = { 0 };
	matrix min_A00 = { 2, 2, &min_A00_data };//minore A00 di A

	double min_A01_data[4] = { 0 };
	matrix min_A01 = { 2, 2, &min_A01_data };//minore A01 di A

	double min_A02_data[4] = { 0 };
	matrix min_A02 = { 2, 2, &min_A02_data };//minore A02 di A

	unsigned int tipo_conica;//0 -> degenere, 1 -> iperbole, 2 -> parabola, 3 -> ellisse

	while (1)
	{
		printf("Inserisci coefficienti separati da spazi con questo ordine:\n");
		printf("ax^2 + bxy + cy^2 + dx + ey + f = 0\n");

		int suc = scanf("%lf %lf %lf %lf %lf %lf", &C[_a], &C[_b], &C[_c], &C[_d], &C[_e], &C[_f]);
		if (suc != 6)
		{
			printf("C'è stato un problema con l'inserimento dei coefficienti, riprovare\n");
			continue;
		}
		break;
	}
	Crea_matrice_associata(C, &A, &min_A00, &min_A01, &min_A02);

	//MATRICE ASSOCIATA
	printf("\nLa Matrice associata alla conica è:\n");
	Stampa_matrice(&A);

	//TIPOLOGIA DI CONICA
	double detA = determinante_mat(&A);

	//check DEGENERE
	if (detA == 0)
	{
		tipo_conica = DEGENERE;
		printf("Al momento questo è il massimo che ti so dire\n\n");
		printf("FINE\n---------------------------------------------------------------------------------------");
		return 1;
	}
	
	//check IPERBOLE PARABOLA ELLISSE
	double det_min_A00 = determinante_mat(&min_A00);
	if (det_min_A00 == 0)
	{
		tipo_conica = PARABOLA;
		printf("\nLa conica è una PARABOLA con:\ndetA : %f\ndet_min_A00 : %f\n", detA, det_min_A00);
	}
	else if(det_min_A00 < 0)
	{
		tipo_conica = IPERBOLE;
		printf("\nLa conica è una IPERBOLE con:\ndetA : %f\ndet_min_A00 : %f\n", detA, det_min_A00);
	}
	else
	{
		tipo_conica = ELLISSE;
		printf("\nLa conica è una ELLISSE con:\ndetA : %f\ndet_min_A00 : %f\n", detA, det_min_A00);
	}

	//Centro
	punto centro;
	centro.xyz[0] = det_min_A00;
	centro.xyz[1] = determinante_mat(&min_A01);
	centro.xyz[2] = determinante_mat(&min_A02);

	printf("\nIl centro è di coordinate omogenee:\nC = [ %f, %f, %f]", centro.xyz[0], centro.xyz[1], centro.xyz[2]);

	if (centro.xyz[0] != 0)
	{
		centro = crea_punto(1, -centro.xyz[1] / centro.xyz[0], centro.xyz[2] / centro.xyz[0]);
		printf("= [ %f, %f, %f] --> Coordinate reali C = ( %f, %f)\n", centro.xyz[0], centro.xyz[1], centro.xyz[2],centro.xyz[1], centro.xyz[2]);
	}
	else
	{
		centro = crea_punto(0, 1, centro.xyz[2] / centro.xyz[1]);
		printf("= [ %f, %f, %f]\n", centro.xyz[0], centro.xyz[1], centro.xyz[2]);
	}

	//ASINTOTI se IPERBOLE
	if (tipo_conica == IPERBOLE)
	{
		//ax^2 + bxy + cy^2 dove y = 1
		double C_intersez[3] = { C[_a], C[_b], C[_c] };
		//punti all'infinito
		punto p1i = crea_punto(0 , 0, 1);
		punto p2i = crea_punto(0, 0, 1);

		unsigned int suc = sol_equaz_secondo_grado(C_intersez, &p1i.xyz[_x], &p2i.xyz[_x]);
		if (suc == false)
		{
			printf("\nERRORE, C'è stato un problema a calcolare i punti all'infinito degli asintoti\n");
			return 2;
		}
		else if (suc == 3)
		{
			//caso equazione di primo grado
			if (C_intersez[_a] == 0)
			{
				p1i = crea_punto(0, 1, 0);
			}
		}
		printf("\nI 2 punti all'infinito degli asintoti sono:\nP1i = [ 0, %f, %f]\nP2i = [ 0, %f, %f]", p1i.xyz[1], p1i.xyz[2], p2i.xyz[1], p2i.xyz[2]);
		
		//polare dei punti all'infinito
		retta_pol rpol_p1 = retta_polare(&A, p1i);
		retta_pol rpol_p2 = retta_polare(&A, p2i);
		printf("\nLe equazioni degli asintoti sono:\n");
		printf("Asintoto 1 : (%.4f)x + (%.4f)y + (%.4f) = 0 | Polo = [ %f, %f, %f]\n", rpol_p1.abc[_a], rpol_p1.abc[_b], rpol_p1.abc[_c], rpol_p1.polo.xyz[0], rpol_p1.polo.xyz[1], rpol_p1.polo.xyz[2]);
		printf("Asintoto 2 : (%.4f)x + (%.4f)y + (%.4f) = 0 | Polo = [ %f, %f, %f]\n", rpol_p2.abc[_a], rpol_p2.abc[_b], rpol_p2.abc[_c], rpol_p2.polo.xyz[0], rpol_p2.polo.xyz[1], rpol_p2.polo.xyz[2]);
	}

	//ASSI
	autoval_mat2x2 autov = autovalori_matrice_2x2(&min_A00);
	printf("\nGli autovalori di M_00 sono:\na1 = %.8f\na2 = %.8f\n", autov.autoval[0], autov.autoval[1]);
	punto q1i, q2i;
	retta_pol rpol_q1, rpol_q2;

	if (tipo_conica == PARABOLA)
	{
		//1 ASSE
		q1i = autospazio(autov.autoval[0], &min_A00);
		printf("\nIl punto all'infinito del' asse è :\nQ1i = [ %f, %f, %f]", q1i.xyz[_o], q1i.xyz[_x], q1i.xyz[_y]);

		rpol_q1 = retta_polare(&A, q1i);
		printf("\nEq asse 1 : (%f)x + (%f)y + (%f) = 0", rpol_q1.abc[_a], rpol_q1.abc[_b], rpol_q1.abc[_c]);
	}
	else if (tipo_conica == IPERBOLE || tipo_conica == ELLISSE)
	{
		//2 ASSI
		q1i = autospazio(autov.autoval[0], &min_A00);
	    q2i = autospazio(autov.autoval[1], &min_A00);
		printf("\nI punti all'infinito dei 2 assi sono :\nQ1i = [ %f, %f, %f] || Q2i = [ %f, %f, %f]", q1i.xyz[_o], q1i.xyz[_x], q1i.xyz[_y], q2i.xyz[_o], q2i.xyz[_x], q2i.xyz[_y]);
	
		rpol_q1 = retta_polare(&A, q1i);
		rpol_q2 = retta_polare(&A, q2i);
		printf("\nEq asse 1 : (%f)x + (%f)y + (%f) = 0", rpol_q1.abc[_a], rpol_q1.abc[_b],rpol_q1.abc[_c]);
		printf("\nEq asse 2 : (%f)x + (%f)y + (%f) = 0\n", rpol_q2.abc[_a], rpol_q2.abc[_b], rpol_q2.abc[_c]);
	}

	//VERTICI
	punto v1, v2, v3, v4;
	bool suc_sol_asse1, suc_sol_asse2;
	if (tipo_conica == PARABOLA)
	{
		suc_sol_asse1 = sol_sistema_secondo_grado(rpol_q1, C, &v1, NULL);
		if (suc_sol_asse1 == false)
		{
			printf("\nERRORE, intersezione asse conica vuota\n");
		}

		printf("\nI punti di intersezioni con l'asse sono :\n");
		printf("V1 = (%f, %f)\n", v1.xyz[1], v1.xyz[2]);
	}
	else if (tipo_conica == IPERBOLE || tipo_conica == ELLISSE)
	{
		suc_sol_asse1 = sol_sistema_secondo_grado(rpol_q1, C, &v1, &v2);
		suc_sol_asse2 = sol_sistema_secondo_grado(rpol_q2, C, &v3, &v4);
		if (suc_sol_asse1 == false && suc_sol_asse2 == false)
		{
			printf("\nERRORE, intersezione asse conica vuota\n");
		}

		if (suc_sol_asse1 == true)
		{
			printf("\nI punti di intersezioni con l'asse 1 sono :\n");
			printf("V1 = (%f, %f) || V2 = (%f, %f)", v1.xyz[1], v1.xyz[2], v2.xyz[1], v2.xyz[2]);
		}
		if (suc_sol_asse2 == true)
		{
			printf("\nI punti di intersezioni con l'asse 2 sono :\n");
			printf("V3 = (%f, %f) || V4 = (%f, %f)\n", v3.xyz[1], v3.xyz[2], v4.xyz[1], v4.xyz[2]);
		}
	}

	//EQ CANONICA
	double coeff_D[6] = { 0 };
	double Ddata[9] = { 0 };
	double a_, b_, p_;
	matrix D = { 3, 3, &Ddata };

	if (tipo_conica == PARABOLA)
	{
		/*matrice D associata a A
		0 0  d
		0 a1 0
		d 0  0

		ax^2 + bxy + cy^2 + dx + ey + f = 0
		*/
		coeff_D[_a] = autov.autoval[0];
		coeff_D[_e] = 2;

		Crea_matrice_associata(coeff_D, &D, NULL, NULL, NULL);

		D.data[2] = D.data[6] = trova_d_par(&D, detA);
		coeff_D[4] = D.data[2] + D.data[6];

		p_ = 1 / (2 * (-coeff_D[_a] / coeff_D[_e]));

		printf("\nLa matrice associata della equazione canonica è :\n");
		Stampa_matrice(&D);

		printf("\nL'equazione canonica della conica è :\n");
		printf("(%.5f)x^2 + (%.5f)y = 0", coeff_D[_a], coeff_D[_e]);

		printf("\nL'equazione canonica in forma standard della conica è :\n");
		printf("y = (%.5f)x^2\n", -coeff_D[_a] / coeff_D[_e]);

		printf("\nCon p = %.5f\n", p_);
	}
	else if (tipo_conica == IPERBOLE || tipo_conica == ELLISSE)
	{
		/*matrice D associata a A
		d 0  0
		0 a1 0
		0 0 a2

		ax^2 + bxy + cy^2 + dx + ey + f = 0
		*/
		if (autov.autoval[0] > autov.autoval[1] && tipo_conica == IPERBOLE)
		{
			coeff_D[_a] = autov.autoval[0];
			coeff_D[_c] = autov.autoval[1];
			coeff_D[_f] = 1;
		}
		else if (autov.autoval[0] > autov.autoval[1] && tipo_conica == ELLISSE)
		{
			coeff_D[_a] = autov.autoval[1];
			coeff_D[_c] = autov.autoval[0];
			coeff_D[_f] = 1;
		}
		else
		{
			coeff_D[_a] = autov.autoval[1];
			coeff_D[_c] = autov.autoval[0];
			coeff_D[_f] = 1;
		}

		Crea_matrice_associata(coeff_D, &D, NULL, NULL, NULL);

		coeff_D[_f] = D.data[0] = trova_d_ip_el(&D, detA);

		
		if (tipo_conica == ELLISSE)
		{
			a_ = 1 / sqrt(-coeff_D[_a] / coeff_D[_f]);
			b_ = 1 / sqrt(-coeff_D[_c] / coeff_D[_f]);
		}
		else//tipo_conica == IPERBOLE
		{
			a_ = 1 / sqrt(-coeff_D[_a] / coeff_D[_f]);
			b_ = 1 / sqrt(coeff_D[_c] / coeff_D[_f]);
		}
		printf("\nLa matrice associata della equazione canonica è :\n");
		Stampa_matrice(&D);

		printf("L'equazione canonica della conica è :\n");
		printf("(%.5f)x^2 + (%.5f)y^2 + (%.5f) = 0", coeff_D[_a], coeff_D[_c], coeff_D[_f]);

		printf("\nL'equazione canonica in forma standard della conica è :\n");
		printf("(%.5f)x^2 + (%.5f)y^2 = 1\n", -coeff_D[_a] / coeff_D[_f], -coeff_D[_c] / coeff_D[_f]);

		printf("\nCon a = %.5f, b = %.5f\n", a_, b_);
	}

	//FUOCHI
	double crf[6] = { 0 };
	double r_crf = 0;
	punto f1, f2;
	retta_pol asseFocale = { 0 };
	if (tipo_conica == PARABOLA)
	{
		asseFocale = rpol_q1;
		r_crf = p_ / 2;
		printf("\nd(V, F1) = d(V, F2) = %.5f", r_crf);
		
		crea_crf(v1 , r_crf, crf);

		bool succ_intersez = sol_sistema_secondo_grado(asseFocale, crf, &f1, &f2);
		if (!succ_intersez)
		{
			printf("\nERRORE, intersezione tra circonferenza e asse non andato bene\n");
		}
		printf("\nF1 = (%.5f, %.5f) || F2 = (%.5f, %.5f)\n", f1.xyz[_x], f1.xyz[_y], f2.xyz[_x], f2.xyz[_y]);
	}
	else if (tipo_conica == IPERBOLE)
	{
		if (suc_sol_asse1 == true)
		{
			//printf("\nI punti di intersezioni con l'asse 1 sono :\n");
			//printf("V1 = (%f, %f) || V2 = (%f, %f)", v1.xyz[1], v1.xyz[2], v2.xyz[1], v2.xyz[2]);
			asseFocale = rpol_q1;
			printf("\nL'asse focale è l'asse 1");
		}
		else if (suc_sol_asse2 == true)
		{
			//printf("\nI punti di intersezioni con l'asse 2 sono :\n");
			//printf("V3 = (%f, %f) || V4 = (%f, %f)\n", v3.xyz[1], v3.xyz[2], v4.xyz[1], v4.xyz[2]);
			asseFocale = rpol_q2;
			printf("\nL'asse focale è l'asse 2");
		}
		else
		{
			printf("\nERRORE, calcolo fuochi\n");
		}
		r_crf = r_crf = sqrt(a_ * a_ + b_ * b_);
		printf("d(C, F1) = d(C, F2) = %.5f\n", r_crf);

		crea_crf(centro, r_crf, crf);

		bool succ_intersez = sol_sistema_secondo_grado(asseFocale, crf, &f1, &f2);
		if (!succ_intersez)
		{
			printf("\nERRORE, intersezione tra circonferenza e asse non andato bene\n");
		}
		printf("\nF1 = (%.5f, %.5f) || F2 = (%.5f, %.5f)\n", f1.xyz[_x], f1.xyz[_y], f2.xyz[_x], f2.xyz[_y]);
	}	
	else if (tipo_conica == ELLISSE)
	{
		double dist_v1v2 = distanza_punti(v1, v2);
		double dist_v3v4 = distanza_punti(v3, v4);

		if (dist_v1v2 > dist_v3v4)
		{
			asseFocale = rpol_q1;
		}
		else
		{
			asseFocale = rpol_q2;
		}
		printf("\nd(V1, V2) = %.5f || d(V2, V3) = %.5f\nL'asse focale è l'asse %d\n", dist_v1v2, dist_v3v4, dist_v1v2 > dist_v3v4 ? 1 : 2);
		r_crf = sqrt(a_ * a_ - b_ * b_);
		printf("d(C, F1) = d(C, F2) = %.5f\n", r_crf);

		crea_crf(centro, r_crf, crf);

		bool succ_intersez = sol_sistema_secondo_grado(asseFocale, crf, &f1, &f2);
		if (!succ_intersez)
		{
			printf("\nERRORE, intersezione tra circonferenza e asse non andato bene\n");
		}
		printf("\nF1 = (%.5f, %.5f) || F2 = (%.5f, %.5f)\n", f1.xyz[_x], f1.xyz[_y], f2.xyz[_x], f2.xyz[_y]);
	}

	printf("\n\nFINE STUDIO CONICA\n------------------------------------------------------------------------------------\n");
	
	//inutile ma serve a pausare il programma
	system("pause");
	return 0;
}