#include <stdio.h>
#include <stdlib.h>

//TRIS IN C
//matrice array


//NON USATA Funzione controllo vittoria con determinante
int CheckVittoriaDeterminante(int giocatore, int* tris, int lung) 
{
	//giocatore: 1, -1 //int* tris puntatore all’array tris //lung : lunghezza array 
	int determinante;
	int trisc[9] = { 2, 2, 2, 2, 2, 2, 2, 2, 2 };
					//+ 0*4*8+ 1*5*6 + 3*7*2
					//- 2*4*6 + 1*3*8 + 0*5*7
	

	//creazione copia vettore tris, con 0 al posto dei valori di giocatore
	for (unsigned int i = 0; i < lung; i++) {
		if (tris[i] == giocatore) {
			trisc[i] = 0;
		}
		else
		{
			trisc[i] = tris[i];
		}
	}

	determinante = (trisc[0] * trisc[4] * trisc[8] + 
					trisc[1] * trisc[5] * trisc[6] + 
					trisc[3] * trisc[2] * trisc[7]) - 
				   (trisc[2] * trisc[4] * trisc[6] + 
					trisc[1] * trisc[3] * trisc[8] + 
					trisc[0] * trisc[5] * trisc[7]);

	if (determinante == 0)
	{
		//il giocatore ha vinto
		return 1;
	}
	return 0;
}

int CheckVittoria(int* tris, int lung)
{
	int somma = 0;
	//check colonne
	for (unsigned int j = 0; j < 3; j++)
	{
		for (unsigned int i = j; i < 9; i += 3)
		{
			somma += tris[i];
		}

		if (somma == 3 || somma == -3)
		{
			return 1;
		}
		else
		{
			somma = 0;
		}
	}
	somma = 0;
	//check righe
	for (unsigned int j = 0; j < 7; j += 3)
	{
		for (unsigned int i = j; i < (3 + j); i++)
		{
			somma += tris[i];
		}
		if (somma == 3 || somma == -3)
		{
			return 1;
		}
		else
		{
			somma = 0;
		}
	}
	somma = 0;
	//check diagonali
	if ((tris[0] + tris[4] + tris[8]) == 3 || (tris[0] + tris[4] + tris[8]) == -3 || (tris[2] + tris[4] + tris[6]) == 3 || (tris[2] + tris[4] + tris[6]) == -3)
	{
		return 1;
	}

	return 0;
}
//funzione controllo pareggio
int CheckPareggio(int* tris, int lung)
{
	//printf("\nFunzione CheckPareggio chiamata\n");
	int t = 0;
	for (unsigned int i = 0; i < lung; i++)
	{
		if (tris[i] != 0)
		{
			t++;
			//printf("\ntris[%d] : %d,	t = %d\n", i, tris[i], t);
		}
	}
	if (t == lung)
	{
		return 1;
	}
	return 0;
}

//funzione disegna il tris
void DisegnoTris(int* tris)
{
	/*
	  _ _|_ _|_ _
	  _ _|_ _|_ _
	     |   |  
	*/
	int c = 0;
	//prima casella
	for (unsigned int j = 0; j < 3; j++)
	{
		for (unsigned int i = 0; i < 3; i++)
		{
			if (j != 2)
			{
				printf("_");
			}
			else 
			{
				printf(" ");
			}

			if (tris[c] == 0)
			{
				printf(" ");
			}
			else if (tris[c] == 1)
			{
				printf("x");
			}
			else if (tris[c] == -1)
			{
				printf("o");
			}
			else
			{
				printf("E");//in caso di errore
			}

			if (j != 2)
			{
				printf("_");
			}
			else
			{
				printf(" ");
			}

			if (i != 2)
			{
				printf("|");
			}

			c++;
		}
		printf("\n");
	}
}

int	GiocaDiNuovo()
{
	int input;
	printf("\n\n\n-----------------------------------------------------------------------------------------\n");
	printf("-----------------------------------------------------------------------------------------\n");
	printf("Volete giocare ancora?\nsi = [1], no = [0]\n");
	scanf_s("%d", &input);
	return input;
}

unsigned int InputGiocatoreMossa(int* tris, unsigned int turno)
{
	unsigned int input;

	while (1)
	{
		printf("TURNO Giocatore %d\n\nPosizione mossa : ", turno);
		scanf_s("%d", &input);
		if (input > 8)//controlla che la mossa sia dentro l'array
		{
			printf("mossa impossibile, reinserire dato\n");
		}
		else if (tris[input] != 0)//controlla che ci sia uno spazio vuoto
		{
			printf("mossa impossibile, reinserire dato\n");
		}
		else
		{
			break;
		}
	}

	return input;
}

int main(void)
{
restart:;
	unsigned int input;
	unsigned int turno = 1; // 1, 2
	int giocatore;
	int tris[9] = { 0, 0, 0,
				    0, 0, 0,
				    0, 0, 0 };
	//gioco
	while (1)
	{
		DisegnoTris(tris);

		//sezione input
		input = InputGiocatoreMossa(tris, turno);

		//assegnazione input nell'array
		if (turno == 1)
		{
			tris[input] = 1;
			giocatore = 1;
		}
		else
		{
			tris[input] = -1;
			giocatore = -1;
		}

		//controllo vittoria
		
		if (CheckVittoria(tris, 9))
		{
			printf("\nGiocatore %d ha VINTO!!\n\n", turno);
			DisegnoTris(tris);

			if (GiocaDiNuovo())
			{
				goto restart;
			}
			else
			{
				break;
			}
		}
		else if (CheckPareggio(tris, 9))//controllo pareggio
		{
			printf("\nI GIOCATORI hanno PAREGGIATO\n\n");
			DisegnoTris(tris);

			if (GiocaDiNuovo())
			{
				goto restart;
			}
			else
			{
				break;
			}
		}

		//cambio di turno
		if (turno == 1)
		{
			turno = 2;
		}
		else
		{
			turno = 1;
		}
	}
}
