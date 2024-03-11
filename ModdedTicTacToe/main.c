#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bool int
#define true 1
#define false 0

//funzione controllo se uno dei due giocatori ha vinto
int CheckVittoria(int* tris, int lung)
{
	int sommaG1;
	int sommaG2;
	int consecutivoG1;
	int consecutivoG2;

	//check colonne
	for (int j = 0; j < 5; j++)
	{
		sommaG1 = 0;
		sommaG2 = 0;
		consecutivoG1 = 0;
		consecutivoG2 = 0;
		//printf("\n\nControllo colonna %d :", j);

		for (int i = j; i < (25 -(4 - j)); i += 5)
		{
			if (tris[i] == 1)
			{
				sommaG1++;
				consecutivoG1++;
				consecutivoG2 = 0;
			}
			else if (tris[i] == -1)
			{
				sommaG2++;
				consecutivoG2++;
				consecutivoG1 = 0;
			}
			else
			{
				consecutivoG1 = 0;
				consecutivoG2 = 0;
			}

			//printf("\nControllo posizione %d = %d", i, tris[i]);
			//printf("\nSommaG1 = %d, SommaG2 = %d, consecG1 = %d, consecG2 = %d", sommaG1, sommaG2, consecutivoG1, consecutivoG2);

			if ((sommaG1 >= 4 || sommaG2 >= 4) && (consecutivoG1 == 4 || consecutivoG2 == 4))
			{
				//printf("\nVittoria di qualcuno confermata");
				return 1;
			}
		}
	}

	//check righe
	for (int j = 0; j < 21; j += 5)
	{
		sommaG1 = 0;
		sommaG2 = 0;
		consecutivoG1 = 0;
		consecutivoG2 = 0;

		for(int i = j; i < (5 + j); i++)
		{
			if (tris[i] == 1)
			{
				sommaG1++;
				consecutivoG1++;
				consecutivoG2 = 0;
			}
			else if (tris[i] == -1)
			{
				sommaG2++;
				consecutivoG2++;
				consecutivoG1 = 0;
			}
			else
			{
				consecutivoG1 = 0;
				consecutivoG2 = 0;
			}

			if ((sommaG1 >= 4 || sommaG2 >= 4) && (consecutivoG1 == 4 || consecutivoG2 == 4))
			{
				return 1;
			}
		}
	}

	//check diagonali
	sommaG1 = 0;
	sommaG2 = 0;
	consecutivoG1 = 0;
	consecutivoG2 = 0;
	//diagonale principale
	for (int i = 0; i < 25; i += 6)
	{
		if (tris[i] == 1)
		{
			sommaG1++;
			consecutivoG1++;
			consecutivoG2 = 0;
		}
		else if (tris[i] == -1)
		{
			sommaG2++;
			consecutivoG2++;
			consecutivoG1 = 0;
		}
		else
		{
			consecutivoG1 = 0;
			consecutivoG2 = 0;
		}

		if ((sommaG1 >= 4 || sommaG2 >= 4) && (consecutivoG1 == 4 || consecutivoG2 == 4))
		{
			return 1;
		}
	}
	sommaG1 = 0;
	sommaG2 = 0;
	consecutivoG1 = 0;
	consecutivoG2 = 0;
	//diagonale p1
	for (int i = 5; i < 25; i += 6)
	{
		if (tris[i] == 1)
		{
			sommaG1++;
			consecutivoG1++;
			consecutivoG2 = 0;
		}
		else if (tris[i] == -1)
		{
			sommaG2++;
			consecutivoG2++;
			consecutivoG1 = 0;
		}
		else
		{
			consecutivoG1 = 0;
			consecutivoG2 = 0;
		}

		if ((sommaG1 >= 4 || sommaG2 >= 4) && (consecutivoG1 == 4 || consecutivoG2 == 4))
		{
			return 1;
		}
	}
	sommaG1 = 0;
	sommaG2 = 0;
	consecutivoG1 = 0;
	consecutivoG2 = 0;
	//diagonale p2
	for (int i = 1; i < 25; i += 6)
	{
		if (tris[i] == 1)
		{
			sommaG1++;
			consecutivoG1++;
			consecutivoG2 = 0;
		}
		else if (tris[i] == -1)
		{
			sommaG2++;
			consecutivoG2++;
			consecutivoG1 = 0;
		}
		else
		{
			consecutivoG1 = 0;
			consecutivoG2 = 0;
		}

		if ((sommaG1 >= 4 || sommaG2 >= 4) && (consecutivoG1 == 4 || consecutivoG2 == 4))
		{
			return 1;
		}
	}
	sommaG1 = 0;
	sommaG2 = 0;
	consecutivoG1 = 0;
	consecutivoG2 = 0;

	//diagonale secondaria
	for (int i = 4; i <= 20; i += 4)
	{
		if (tris[i] == 1)
		{
			sommaG1++;
			consecutivoG1++;
			consecutivoG2 = 0;
		}
		else if (tris[i] == -1)
		{
			sommaG2++;
			consecutivoG2++;
			consecutivoG1 = 0;
		}
		else
		{
			consecutivoG1 = 0;
			consecutivoG2 = 0;
		}

		if ((sommaG1 >= 4 || sommaG2 >= 4) && (consecutivoG1 == 4 || consecutivoG2 == 4))
		{
			return 1;
		}
	}
	sommaG1 = 0;
	sommaG2 = 0;
	consecutivoG1 = 0;
	consecutivoG2 = 0;
	//diagonale s1
	for (int i = 3; i <= 15; i += 4)
	{
		if (tris[i] == 1)
		{
			sommaG1++;
			consecutivoG1++;
			consecutivoG2 = 0;
		}
		else if (tris[i] == -1)
		{
			sommaG2++;
			consecutivoG2++;
			consecutivoG1 = 0;
		}
		else
		{
			consecutivoG1 = 0;
			consecutivoG2 = 0;
		}

		if ((sommaG1 >= 4 || sommaG2 >= 4) && (consecutivoG1 == 4 || consecutivoG2 == 4))
		{
			return 1;
		}
	}
	sommaG1 = 0;
	sommaG2 = 0;
	consecutivoG1 = 0;
	consecutivoG2 = 0;
	//diagonale s2
	for (int i = 9; i <= 21; i += 4)
	{
		if (tris[i] == 1)
		{
			sommaG1++;
			consecutivoG1++;
			consecutivoG2 = 0;
		}
		else if (tris[i] == -1)
		{
			sommaG2++;
			consecutivoG2++;
			consecutivoG1 = 0;
		}
		else
		{
			consecutivoG1 = 0;
			consecutivoG2 = 0;
		}

		if ((sommaG1 >= 4 || sommaG2 >= 4) && (consecutivoG1 == 4 || consecutivoG2 == 4))
		{
			return 1;
		}
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
void DisegnoTris(int* tris, int seePos)
{
	/* 
	   O | O | O | O | O
	  ---|---|---|---|---
	   O | O | O | O | O
	  ---|---|---|---|---
	   O | O | O | O | O
	  ---|---|---|---|---
	   O | O | O | O | O
	  ---|---|---|---|---
	   O | O | O | O | O
	*/
	char trisc[25] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	if (seePos == 0)
	{
		for (int i = 0; i < 25; i++)
		{
			if (tris[i] == 1)
			{
				trisc[i] = 'X';
			}
			else if (tris[i] == -1)
			{
				trisc[i] = 'O';
			}
			else
			{
				trisc[i] = ' ';
			}
		}

		for (int i = 0; i < 25; i += 5)
		{
			printf("\n %c | %c | %c | %c | %c", trisc[i], trisc[i + 1], trisc[i + 2], trisc[i + 3], trisc[i + 4]);
			if (i < 20)
			{
				printf("\n---|---|---|---|---");
			}
		}
	}
	else
	{
		for (int i = 0; i < 25; i += 5)
		{
			if (i < 10)
			{
				printf("\n  %d |  %d |  %d |  %d |  %d", i + 1, i + 2, i + 3, i + 4, i + 5);
				if (i < 20)
				{
					printf("\n----|----|----|----|----");
				}
			}
			else
			{
				printf("\n %d | %d | %d | %d | %d", i + 1, i + 2, i + 3, i + 4, i + 5);
				if (i < 20)
				{
					printf("\n----|----|----|----|----");
				}
			}
		}
	}

	printf("\n\n");
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

int InputGiocatoreMossa(int* tris, unsigned int turno)
{
	int input;

	while (1)
	{
		printf("TURNO Giocatore %d\n\nPosizione mossa [1-25] : ", turno);
		scanf_s("%d", &input);
		input--;

		if (input > 24 || input < 0)//controlla che la mossa sia dentro l'array
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

void MossaComputer(int* tris, int lungTris, unsigned int turno)
{
	int numCasuale;
	srand(time(NULL));
	numCasuale = rand() % lungTris;
	
	if (tris[numCasuale] == 1 || tris[numCasuale] == -1)
	{
		tris[numCasuale] = 0;
	}
	else if(turno == 1)
	{
		tris[numCasuale] = 1;
	}
	else
	{
		tris[numCasuale] = -1;
	}

	printf("\nMossa del computer\nPosiziona %c in posizione : %d", turno == 1 ? 'X' : 'O', numCasuale + 1);
}

int main(void)
{
restart:;
	int input;
	bool primoTurno = true;
	unsigned int turno = 1; // 1, 2
	int giocatore;
	int tris[25] = { 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0,
					 0, 0, 0, 0, 0 };
	//gioco
	while (1)
	{
		DisegnoTris(tris, 1);

		//sezione input
		//input casuale computer
		if (primoTurno == false)
		{
			MossaComputer(tris, 25, turno);
			DisegnoTris(tris, 0);
		}
		else
		{
			primoTurno = false;
		}

		//input giocatore
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

		if (CheckVittoria(tris, 25))
		{
			printf("\nGiocatore %d ha VINTO!!\n\n", turno);
			DisegnoTris(tris, 0);

			if (GiocaDiNuovo())
			{
				goto restart;
			}
			else
			{
				break;
			}
		}
		else if (CheckPareggio(tris, 25))//controllo pareggio
		{
			printf("\nI GIOCATORI hanno PAREGGIATO\n\n");
			DisegnoTris(tris, 0);

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
