/*Zadan je niz brojeva 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 koji su spremljeni u cvorove binarnog stabla.
a) Napisati funkciju insert koja dodaje element u stablo tako da se pozivima te funkcije za
	sve element zadanog niza brojeva stvori stablo kao na slici Slika 1. Funkcije vraca
	pokazivac na korijen stabla.
b) Napisati funkciju replace koja ce svaki element stabla zamijeniti sumom elemenata u
	njegovom lijevom i desnom podstablu(tj.sumom svih potomaka prije zamjene
	vrijednosti u tim potomcima).Npr.stablo sa slike Slika 1 transformirat ce se u stablo na
	slici Slika 2.
c) Prepraviti program na nacin da umjesto predefiniranog cjelobrojnog polja koristenjem
	funkcije rand() generira slucajne brojeve u rasponu <10, 90>.Takoder, potrebno je
	upisati u datoteku sve brojeve u inorder prolasku nakon koristenja funkcije iz a), zatim b)
	dijela zadatka.*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>

#define LINE 1024
#define COUNT 10

struct _Tree;
typedef struct _Tree* Position;

typedef struct _Tree{
	int el;
	Position L;
	Position R;
}Tree;

Position CreateElement(int element);
Position Insert(Position curr, Position new);
int Replace(Position current);
//int ToFile(Position head, char* ime);
int RandomNum(int min, int max);
int Inorder(Position curr);
int ToFile(Position current, FILE* fp);

int main()
{
	char* file = "stablo.txt";
	Position head = NULL;
	Position first = NULL;
	Position root = NULL;
	Position temp = NULL;

	int list1[10] = {2, 5, 7, 8, 11, 1, 4, 2, 3, 7};
	int list2[10] = {0};
	int min = 0;
	int max = 0;
	int i = 0;

	srand(time(NULL));

	head = (Position)malloc(sizeof(Tree));

	for (i = 0; i < 10; i++)
	{
		temp = CreateElement(list1[i]);
		if (i == 0)
		{
			first = temp;
		}
		else
		{
		Insert(first, temp);
		}
	}

	printf("(Inorder) print before the sum operation: \n");
	Inorder(first);

	Replace(first);

	puts("\n\n");

	head->el = 0;
	head->L = NULL;
	head->R = NULL;

	printf("(Inorder) print after the sum operation: \n");
	Inorder(first);

	first = head->R;

	while (first != NULL)
	{
		printf("%d ", first->el);
		first = first->R;
	}

	puts("\n\n");

	ToFile(head, file);

	printf("Enter the limits of random numbers:\n");
	printf("Low: ");
	scanf(" %d", &min);
	printf("High: ");
	scanf(" %d", &max);

	puts("\n");
	
	for (i = 0; i < 10; i++)
	{
		list2[i] = RandomNum(min, max);
	}

	for (i = 0; i < 10; i++)
	{
		temp = CreateElement(list2[i]);
		if (i == 0)
		{
			first = temp;
		}
		else
		{
			Insert(first, temp);
		}
	}

	Inorder(first);

	Replace(first);

	puts("\n");

	return 0;
}

Position CreateElement(int element)
{
	Position new = NULL;
	new = (Position)malloc(sizeof(Tree));
	new->el = element;
	new->L = NULL;
	new->R = NULL;
	return new;
}

Position Insert(Position curr, Position new)
{
	if (curr == NULL)
	{
		return new;
	}
	if ((curr->el) <= (new->el))
	{
		curr->R = Insert(curr->R, new);
	}
	else if ((curr->el) > (new->el))
	{
		curr->L = Insert(curr->L, new);
	}
	return curr;
}

int Inorder(Position curr)
{
	if (curr)
	{
		Inorder(curr->L);
		printf("%d ", curr->el);
		Inorder(curr->R);
	}

	return EXIT_SUCCESS;
}


int Replace(Position current)
{
	int L1 = 0;
	int D1 = 0;
	int L2 = 0;
	int D2 = 0;

	if (current != NULL)
	{
		if (current->L != NULL)
		{
			L1 = current->L->el;
		}
		if (current->R != NULL)
		{
			D1 = current->R->el;
		}

		Replace(current->L);
		Replace(current->R);

		if (current->L != NULL)
		{
			L2 = current->L->el;
		}

		if (current->R != NULL)
		{
			D2 = current->R->el;
		}

		return current->el = L2 + D2 + L1 + D1;
	}
	return EXIT_SUCCESS;
}

int ToFile(Position head, char* name)
{
	FILE* dat = NULL;
	Position temp;

	temp = head->R;
	dat = fopen(name, "w");

	while (temp != NULL)
	{
		fprintf(dat, "%d ", temp->el);
		temp = temp->R;
	}

	fclose(dat);

	return EXIT_SUCCESS;
}


int RandomNum(int min, int max)
{
	int n = 0;
	n = max - min + 1;
	int m = RAND_MAX - (RAND_MAX % n);
	int rand_num = rand();
	while (rand_num > m)
		rand_num = rand();
	return rand_num % n + min;
}