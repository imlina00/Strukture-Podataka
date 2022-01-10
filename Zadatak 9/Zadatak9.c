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

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define MAX_SIZE 128
#define MAX_LINE 1024

struct tree;
typedef struct tree* Position;
typedef struct tree
{
	int el;
	Position L;
	Position R;
}Tree;

struct stack;
typedef struct stack* SPosition;
typedef struct stack
{
	int el;
	SPosition next;
}Stack;

Position Insert(Position curr, Position new);
Position CreateNew(int number, Position curr);
int PrintInOrder(Position curr);
int Replace(Position curr);
int DeleteAll(Position curr);
int PopStack(SPosition head);
int PushStack(SPosition head, int element);
int ToFile(SPosition head, Position root, char* name);
int ToStack(SPosition head, Position curr);
int RandomNum(int min, int max);

int main()
{
	Position root = NULL;
	srand((unsigned)time(NULL));
	Stack head;
	head.el = 0;
	head.next = NULL;
	char name[MAX_SIZE] = { 0 };
	int i = 0;
	int n;

	printf("Enter the wanted file name: ");
	scanf(" %s", name);

	int list[10] = { 2, 5, 7, 8, 11, 1, 4, 2, 3, 7 };

	for (i = 0; i < 10; i++)
	{
		root = CreateNew(list[i], root);
	}

	PrintInOrder(root);
	printf("\n");

	ToStack(&head, root);
	ToFile(&head, root, name);

	Replace(root);

	PrintInOrder(root);
	printf("\n");

	ToStack(&head, root);
	ToFile(&head, root, name);

	DeleteAll(root);

	int min, max, nodes;

	printf("\nEnter the wanted number of nodes: ");
	scanf(" %d", &nodes);
	printf("Enter the limits of random numbers:\n");
	printf("Low: ");
	scanf(" %d", &min);
	if (min < 10) {
		printf("Number is too low, it must be bigger than 9!\n");
		scanf(" %d", &min);
	}
	printf("High: ");
	scanf(" %d", &max);
	if (max > 90) {
		printf("Number is too high, it must be lower than 90!\n");
		scanf(" %d", &min);
	}

	root = NULL;

	for (i = 0; i < nodes; i++)
	{
		root = CreateNew((rand() % (max - min - 1) + min + 1), root);
	}

	PrintInOrder(root);

	return 0;
}

Position Insert(Position curr, Position new)
{
	if (NULL == curr)
	{
		return new;
	}
	else if (new->el < curr->el)
	{
		curr->R = Insert(curr->R, new);
	}
	else
	{
		curr->L = Insert(curr->L, new);
	}

	return curr;
}

Position CreateNew(int number, Position curr)
{
	Position new = NULL;

	new = (Position)malloc(sizeof(Tree));
	if (!new)
	{
		perror("ERROR: Allocation failed!");
		return NULL;
	}

	new->el = number;
	new->L = NULL;
	new->R = NULL;

	new = Insert(curr, new);

	return new;
}

int PrintInOrder(Position curr)
{
	if (!curr)
	{
		return 0;
	}

	PrintInOrder(curr->L);
	printf("%d ", curr->el);
	PrintInOrder(curr->R);

	return 0;
}

int Replace(Position curr)
{
	int sum = 0;
	int temp = 0;

	if (NULL != curr)
	{
		sum = Replace(curr->L);
		sum += Replace(curr->R);

		temp = curr->el;
		curr->el = sum;
		sum += temp;
	}

	return sum;	
}

int DeleteAll(Position curr)
{
	if (curr == NULL)
	{
		return 0;
	}

	DeleteAll(curr->L);
	DeleteAll(curr->R);

	free(curr);

	return 0;
}

int PopStack(SPosition head)
{
	if (!head->next)
	{
		return 0;
	}

	SPosition delete = head->next;
	head->next = delete->next;
	free(delete);

	return 0;
}

int PushStack(SPosition head, int el)
{
	SPosition new = NULL;
	new = (SPosition)malloc(sizeof(Stack));
	if (!new)
	{
		perror("ERROR: Allocation failed!\n");
		return -1;
	}

	new->el = el;
	new->next = head->next;
	head->next = new;

	return 0;
}

int ToStack(SPosition head, Position curr)
{
	if (NULL == curr)
	{
		return 0;
	}

	ToStack(head, curr->R);
	PushStack(head, curr->el);
	ToStack(head, curr->L);

	return 0;
}

int ToFile(SPosition head, Position root, char* name)
{
	FILE* file = NULL;

	file = fopen(name, "a");
	if (!file)
	{
		perror("ERROR: File opening failed!\n");
		return -1;
	}

	while (head->next)
	{
		fprintf(file, "%d ", head->next->el);
		PopStack(head);
	}

	fprintf(file, "\n");

	fclose(file);

	return 0;
}

int RandomNum(int min, int max)
{
	int n = 0;
	n = max - min + 1;
	int m = RAND_MAX - (RAND_MAX % n);
	int rand_num = rand();
	if (rand_num < 99 && rand_num > 100) {
		while (rand_num > m)
			rand_num = rand();
	}
	return rand_num % n + min;
}
