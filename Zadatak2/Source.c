//Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
//A.dinamièki dodaje novi element na poèetak liste,
//B.ispisuje listu,
//C.dinamièki dodaje novi element na kraj liste,
//D.pronalazi element u listi(po prezimenu),
//E.briše odreðeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable.

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
int FindBySurname(Position Head, char* surname);
Position FindBefore(Position Head);
int ToDelete(Position Head, char* surname);

int main(int argc, char** argv)
{
	Person Head = { .next = NULL, .name = {0}, .surname = {0}, 
		.birthYear = 0 };
	Position P = &Head;

	int answer = 1;
	char name[MAX_SIZE] = {' '};
	char surname[MAX_SIZE] = {' '};
	int birthYear = 0;

	while (answer != 0)
	{
		system("cls"); // nadodaj ovo da se "refresha" pojava narednih printf linija a lista se spremi i pise iznova !!!
		PrintList(P);
		printf("\nSto zelite uciniti?\n");
		printf("\tUnijeti studenta na pocetak liste (1)\n");
		printf("\tUnijeti studenta na kraj liste (2)\n");
		printf("\tPretraziti studenta po prezimenu (3)\n");
		printf("\tIzbrisati studenta iz liste (4)\n\n");
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
			scanf(" %s", surname);
			FindBySurname(P, surname);
			break;

		case 4:
			printf("\nUnesite prezime studenta kojega zelite izbrisati: ");
			scanf(" %s", surname);
			ToDelete(P, surname);
			break;
		}
	}

	//mozemo jos nadodati da se ispisuje greska ukoliko se upise broj koji nije u intervalu od 1-4 ili prezime koje ne postoji

	return EXIT_SUCCESS;
}

int PrependList(Position Head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;

	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		perror("Can't allocate memory!\n");
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
		perror("Can't allocate memory!\n");
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
		perror("Can't allocate memory!\n");
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

int FindBySurname(Position Head, char* surname)
{
	Position temp = Head->next;

	while (temp)
	{
		if (strcmp(temp->surname, surname) == 0) {
			printf("\nTrazeni student je %s %s, %d.\n", temp->name, temp->surname, temp->birthYear);
			system("pause > nul"); // nadodaj da "ponistis" system("cls") iz main-a (47)
			return temp;
			}
		temp = temp->next;
	}
	return EXIT_SUCCESS;
}

Position FindBefore(Position Head) 
{
	Position temp = Head->next;
	while (temp) {
		temp = Head->next;
		if (temp == NULL) return NULL;
		else return Head;
	}
	return temp;
}

int ToDelete(Position Head, char* surname) 
{
	Position temp = Head->next;
	Head = FindBefore(temp);

	if (NULL == Head) printf("Error\n");
	else {
		temp = Head->next;
		Head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}