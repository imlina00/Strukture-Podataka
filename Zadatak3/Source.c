//Prethodnom zadatku dodati funkcije:
//A.dinamièki dodaje novi element iza odreðenog elementa,
//B.dinamièki dodaje novi element ispred odreðenog elementa,
//C.sortira listu po prezimenima osoba, 
//D.upisuje listu u datoteku,
//E.èita listu iz datoteke.

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 50

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

int PrependList(Position Head, char* name, char* surname, int birthYear);
int PrintList(Position Head);
int AppendList(Position Head, char* name, char* surname, int birthYear);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position Last, Position newPerson);
Position FindLast(Position Head);
Position FindBySurname(Position Head, char* surname);
Position FindPrevious(Position Head, Position newPerson);
int ToDelete(Position Head, Position Delete);
int SortListBySurname(Position Head);
int WriteList(Position Head);
int ReadList(Position Head);

int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0},
		.birthYear = 0 };
	Position P = &Head;

	int answer = 1;
	char name[MAX_SIZE] = { ' ' };
	char surname[MAX_SIZE] = { ' ' };
	int birthYear = 0;

	char wanted_surname[MAX_SIZE] = { ' ' };
	Position temp_s = NULL;
	temp_s = (Position)malloc(sizeof(Person));

	while (answer != 0)
	{
		//system("cls"); // "refresha" se pojava narednih printf linija a lista se spremi i pise iznova
		PrintList(P);
		printf("Sto zelite uciniti?\n");
		printf("\tUnijeti studenta na pocetak liste (1)\n");
		printf("\tUnijeti studenta na kraj liste (2)\n");
		printf("\tPretraziti studenta po prezimenu (3)\n");
		printf("\tIzbrisati studenta iz liste (4)\n");
		printf("\tDodati novog studenta iza odredjenog studenta (5)\n");
		printf("\tDodati novog studenta ispred odredjenog studenta (6)\n");
		printf("\tSortirati listu studenata po prezimenima (7)\n");
		printf("\tUpisati listu u datoteku (8)\n");
		printf("\tCitati listu iz datoteke (9)\n");
		printf("\tIzlazak iz programa (0)\n\n");
		printf("Vas odabir: ");
		scanf(" %d", &answer);

		switch (answer)
		{
		case 1:
			printf("\nUnesite ime i prezime studenta na pocetak liste: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodjenja studenta: ");
			scanf(" %d", &birthYear);
			PrependList(P, name, surname, birthYear);
			break;

		case 2:
			printf("\nUnesite ime i prezime studenta na kraj liste: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodjenja studenta: ");
			scanf(" %d", &birthYear);
			AppendList(P, name, surname, birthYear);
			break;

		case 3:
			printf("\nUnesite prezime studenta kojega zelite pronaci: ");
			scanf(" %s", wanted_surname);
			temp_s = FindBySurname(P, wanted_surname);
			printf("\nTrazeni student je %s %s, %d.\n", temp_s->name, temp_s->surname, temp_s->birthYear);
			break;

		case 4:
			printf("\nUnesite prezime studenta kojega zelite izbrisati: ");
			scanf(" %s", wanted_surname);
			temp_s = FindBySurname(P, wanted_surname);
			ToDelete(P, temp_s);
			break;

		case 5:
			printf("\nUnesite prezime studenta iza kojeg zelite nadodati novog studenta: ");
			scanf(" %s", wanted_surname);
			printf("\nUnesite ime i prezime novog studenta: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodjenja novog studenta: ");
			scanf(" %d", &birthYear);		
			temp_s = FindBySurname(P, wanted_surname);
			InsertAfter(temp_s, CreatePerson(name, surname, birthYear));
			break;

		case 6:
			printf("\nUnesite prezime studenta ispred kojeg zelite nadodati novog studenta: ");
			scanf(" %s", wanted_surname);
			temp_s = FindBySurname(P, wanted_surname);
			printf("\nUnesite ime i prezime novog studenta: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodjenja novog studenta: ");
			scanf(" %d", &birthYear);
			
			temp_s = FindPrevious(P, temp_s);
			InsertAfter(temp_s, CreatePerson(name, surname, birthYear));
			break;
			
		case 7:
			SortListBySurname(P);
			//ALI pokusaj napisati onako kako je prof rekao!
			break;

		case 8:
			WriteList(P);
			break;

		case 9:
			ReadList(P);
			break;
		}
	}

	//Nadodati ispis greske ako prezime ne postoji

	return EXIT_SUCCESS;
}

int PrependList(Position Head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		perror("Nije moguce alocirati memoriju!\n");
		return -1;
	}

	InsertAfter(Head, newPerson);

	return EXIT_SUCCESS;
}
Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Nije moguce alocirati memoriju!\n");
		return -1;
	}

	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;

	return newPerson;
}

int PrintList(Position Head)
{
	Position temp = Head->next;
	while (temp) {
		printf("Ime: %s, prezime: %s, godina rodjenja: %d\n",
			temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

int AppendList(Position Head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position Last = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		perror("Nije moguce alocirati memoriju!\n");
		return -1;
	}

	Last = FindLast(Head);
	InsertAfter(Last, newPerson);

	return EXIT_SUCCESS;
}

Position FindLast(Position Head)
{
	Position temp = Head;
	while (temp->next)
	{
		temp = temp->next;
	}
	return temp;
}

int InsertAfter(Position Last, Position newPerson)
{
	newPerson->next = Last->next;
	Last->next = newPerson;

	return EXIT_SUCCESS;
}

Position FindBySurname(Position Head, char* surname)
{
	Position temp = Head->next;

	while (temp != NULL && strcmp(temp->surname, surname))
		temp = temp->next;

	return temp;
}

Position FindPrevious(Position Head, Position newPerson)
{
	Position temp = Head;

	while (temp != NULL && temp->next != newPerson)
		temp = temp->next;

	return temp;
}

int ToDelete(Position Head, Position Delete)
{
	Position temp = NULL;
	Position q = NULL;
	temp = (Position)malloc(sizeof(Person));
	q = (Position)malloc(sizeof(Person));
	q = Delete;

	temp = FindPrevious(Head, Delete);
	temp->next = q->next;

	free(q);

	return EXIT_SUCCESS;
}

int SortListBySurname(Position Head) // UREDI IMENA VARIJABLI
{
	Position temp = Head;
	Position q = NULL;
	Position p = NULL;
	Position Last = NULL;

	while (temp->next != Last)
	{
		p = temp;
		q = p->next;

		while (q->next != Last)
		{
			if (strcmp(q->surname, q->next->surname) > 0)
			{
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = p->next;
			}
			p = q;
			q = q->next;
		}
		Last = q;
	}
	return EXIT_SUCCESS;
}

int WriteList(Position Head)
{
	Position temp = NULL;
	temp = (Position)malloc(sizeof(Person));
	temp = Head->next;

	FILE* dat = NULL;
	dat = fopen("studenti.txt", "w");

	if (dat == NULL) {
		printf("Datoteka se ne moze otvoriti!\n");
		return -1;
	}

	//fprintf(dat, "IME:\tPREZIME:\tGODINA RODJENJA:\n");

	while (temp != NULL) {
		fprintf(dat, "%s\t%s\t%d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}

	fclose(dat);

	return EXIT_SUCCESS;
}

int ReadList(Position Head)
{

	char name[MAX_SIZE] = { 0 };
	char surname[MAX_SIZE] = { 0 };
	int birthYear = 0;
	//ovo gore je nanovo
	char buffer[1024] = { 0 };
	int brojac = 0, i = 0;

	Position temp = NULL;
	Position q = FindLast(Head);

	FILE* dat = NULL;
	dat = fopen("studenti.txt", "r");

	if (dat == NULL) {
		printf("Datoteka se ne moze otvoriti!\n");
		return -1;
	}

	/*while (fgets(buffer, 1024, dat)) {
		brojac++;
	}

	rewind(dat);*/

	/*for (i = 0; i < brojac; i++) {
		temp = (Position)malloc(sizeof(Person));

		temp->next = NULL;
		q->next = temp;
		q = q->next;

		fscanf(dat, " %s %s %d", temp->name, temp->surname, &temp->birthYear);
	}*/

	while (!feof(dat))
	{
		temp = (Position)malloc(sizeof(Person));

		temp->next = NULL;
		q->next = temp;
		q = q->next;

		fscanf(dat, " %s %s %d", temp->name, temp->surname, &temp->birthYear);
		brojac++;
	}

	for (i = 0; i < brojac; i++) {
		printf("\n%s %s %d", temp->name, temp->surname, &temp->birthYear);
	}

	puts("");

	fclose(dat);

	return EXIT_SUCCESS;
}