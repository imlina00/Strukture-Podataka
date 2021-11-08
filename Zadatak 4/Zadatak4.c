//Napisati program za zbrajanje i množenje polinoma.Koeficijenti i eksponenti se
//èitaju iz datoteke.
//Napomena: Eksponenti u datoteci nisu nužno sortirani.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE 1024
#define MAX_SIZE 50

struct Polinom;
typedef struct Polinom* Position;
typedef struct Polinom {
	int koef, pot;
	Position next;
}Poli;

int CitanjePolinomaIzDat(Position Head1, Position Head2, char* Dat);
Position StvoriPolinom(int koef, int pot);
int Zbrajanje(Position Head1, Position Head2, Position HeadZ);
int Mnozenje(Position Head1, Position Head2, Position HeadM);
int UnosSortirano(Position Head, Position NoviElement);
int UnosPoslije(Position P, Position NoviElement);
int CitajRetke(Position Head, char* buffer);
int PonistiNulu(Position Head);
int Ispis(Position P);
int OslobodiMemoriju(Position Head);

int main()
{
	char Dat[MAX_SIZE] = { 0 };
	int odabir = 1;

	Poli Head1 = { .koef = 0, .pot = 0,  .next = NULL };
	Poli Head2 = { .koef = 0, .pot = 0,  .next = NULL };
	Poli HeadZ = { .koef = 0, .pot = 0,  .next = NULL };
	Poli HeadM = { .koef = 0, .pot = 0,  .next = NULL };

	Position P1 = &Head1;
	Position P2 = &Head2;
	Position PZ = &HeadZ;
	Position PM = &HeadM;

	printf("Unesite ime datoteke:");
	scanf(" %s", Dat);
	
	while (odabir != 0)
	{
		system("cls"); //cisti cmd
		printf("Sto zelite uciniti s polinomima?\n");
		printf("Zbrojiti ih - 1\n");
		printf("Pomnoziti ih - 2\n");
		printf("Izaci iz programa - 0\n\n");
		scanf(" %d", &odabir);

		switch (odabir)
		{
		case 0:
			break;

		case 1:
			if (CitanjePolinomaIzDat(P1, P2, Dat) != EXIT_SUCCESS) break;
			printf("Polinomi su:\n");
			printf("\n1. redak:\n");
			Ispis(P1);
			printf("\n2. redak:\n");
			Ispis(P2);
			printf("\nZbroj polinoma:\n");
			Zbrajanje(P1, P2, PZ);
			Ispis(PZ);
			system("pause > nul");
			OslobodiMemoriju(P1);
			OslobodiMemoriju(P2);
			OslobodiMemoriju(PZ);
			break;

		case 2:
			if (CitanjePolinomaIzDat(P1, P2, Dat) != EXIT_SUCCESS) break;
			printf("Polinomi su:\n");
			printf("\n1. redak:\n");
			Ispis(P1);
			printf("\n2. redak:\n");
			Ispis(P2);
			printf("\nUmnozak polinoma:\n");
			Mnozenje(P1, P2, PM);
			Ispis(PM);
			system("pause > nul");
			OslobodiMemoriju(P1);
			OslobodiMemoriju(P2);
			OslobodiMemoriju(PZ);
			break;

		default:
			printf("Niste unijeli broj u zadanom rasponu!\n");
			system("pause > nul");
			break;
		}
	}

	return EXIT_SUCCESS;
}

int CitanjePolinomaIzDat(Position Head1, Position Head2, char* Dat)
{//
	FILE* fp = NULL;
	char buffer[MAX_LINE] = { 0 };

	fp = fopen(Dat, "r");
	if (!fp)
	{
		perror("Nije moguce otvoriti datoteku!\n");
		system("pause > nul");
		return -1;
	}
	
	fgets(buffer, MAX_LINE, fp);
	CitajRetke(Head1, buffer);
	PonistiNulu(Head1);

	fgets(buffer, MAX_LINE, fp);
	CitajRetke(Head2, buffer);
	PonistiNulu(Head2);

	printf("\nPodatci su prepisani iz %s, pritisnite ENTER za prikaz rezultata!\n\n", Dat);

	fclose(fp);
	system("pause > nul");

	return EXIT_SUCCESS;
}

int CitajRetke(Position Head, char* buffer)
{
	char* pointer = NULL;
	int koef, pot;
	int brojac = 0;
	int nB = 0;

	pointer = buffer; //char buffer=NULL;??

	while (strlen(pointer) > 0)
	{
		nB = sscanf(pointer, " %d %d %n", &koef, &pot, &brojac);
		

		if (nB == 2 && koef != 0)
			UnosSortirano(Head, StvoriPolinom(koef, pot));

		pointer += brojac;
	}

	return EXIT_SUCCESS;
}

int PonistiNulu(Position Head)
{
	Position temp1 = Head;
	Position temp2 = NULL;

	while (temp1->next != NULL)
	{
		if (temp1->next->koef == 0)
		{
			temp2 = temp1->next;
			temp1->next = temp2->next;
			free(temp2);
		}
		else
			temp1 = temp1->next;
	}

	return EXIT_SUCCESS;
}

Position StvoriPolinom(int k, int p)
{
	Position noviElement = NULL;

	noviElement = (Position)malloc(sizeof(Poli));

	/*if (!noviElement)
	{
		perror("Greska pri alokaciji memorije!\n");
		return noviElement;
	}*/

	noviElement->koef = k;
	noviElement->pot = p;
	noviElement->next = NULL;

	return noviElement;
}

int UnosSortirano(Position Head, Position noviElement)//skuziti jos bolje
{
	Position temp1 = Head;
	Position temp2 = noviElement;
	int n = 0;

	while (temp1->next != NULL && temp1->next->pot > temp2->pot)
		temp1 = temp1->next;

	if (temp1->next != NULL && temp1->next->pot == temp2->pot)
	{
		temp1->next->koef += temp2->koef;
		n = temp1->koef;

		if (n == 0)
			PonistiNulu(temp1);
	}

	else
	{
		StvoriPolinom(temp2->koef, temp2->pot);
		UnosPoslije(temp1, temp2);
	}


	return EXIT_SUCCESS;
}

int UnosPoslije(Position P, Position noviElement)
{
	noviElement->next = P->next;
	P->next = noviElement;

	return EXIT_SUCCESS;
}

int Zbrajanje(Position Head1, Position Head2, Position HeadZ)
{
	Position P1 = Head1->next;
	Position P2 = Head2->next;
	Position PZ = HeadZ;

	Position noviElement = NULL;

	Position temp = NULL;

	while (P1 != NULL && P2 != NULL)
	{
		if (P1->pot > P2->pot)
		{

			noviElement = StvoriPolinom(P1->koef, P1->pot);
			if (!noviElement)
			{
				return EXIT_FAILURE;
			}
			UnosSortirano(PZ, noviElement);
			P1 = P1->next;
		}

		else if (P1->pot == P2->pot)
		{
			noviElement = StvoriPolinom(P1->koef + P2->koef, P1->pot);
			if (!noviElement)
			{
				return EXIT_FAILURE;
			}
			UnosSortirano(PZ, noviElement);
			P1 = P1->next;
			P2 = P2->next;
		}

		else // (P1->pot < P2->pot)
		{
			noviElement = StvoriPolinom(P2->koef, P2->pot);
			if (!noviElement)
			{
				return EXIT_FAILURE;
			}
			UnosSortirano(PZ, noviElement);
			P2 = P2->next;
		}
	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL)
	{
		noviElement = StvoriPolinom(temp->koef, temp->pot);
		if (!noviElement)
		{
			return EXIT_FAILURE;
		}
		UnosSortirano(PZ, noviElement);
		temp = temp->next;
	}

	PonistiNulu(PZ);

	return EXIT_SUCCESS;
}

int Mnozenje(Position Head1, Position Head2, Position HeadM)
{
	Position P1 = Head1->next;
	Position P2 = Head2->next;
	Position PP = HeadM;

	Position Pocetak = P2;

	Position noviElement = NULL;

	while (P1 != NULL)
	{
		P2 = Pocetak;
		while (P2 != NULL)
		{
			noviElement = StvoriPolinom(P1->koef * P2->koef, P1->pot + P2->pot);
			if (!noviElement)
			{
				return EXIT_FAILURE;
			}

			UnosSortirano(PP, noviElement);
			P2 = P2->next;
		}
		P1 = P1->next;
	}

	PonistiNulu(PP);

	return EXIT_SUCCESS;
}

int Ispis(Position P)
{
	Position temp = P->next;

	while (temp)
	{
		printf("%dx*^%d\n", temp->koef, temp->pot);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int OslobodiMemoriju(Position Head)
{
	Position P = Head;
	Position temp = NULL;

	if (NULL != P->next) {
		while (NULL != P->next)
		{
			temp = P->next;
			P->next = temp->next;
			free(temp);
		}
		return EXIT_SUCCESS;
	}

	else
		return EXIT_FAILURE;
}