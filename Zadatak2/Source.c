//Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
//A.dinamièki dodaje novi element na poèetak liste,
//B.ispisuje listu,
//C.dinamièki dodaje novi element na kraj liste,
//D.pronalazi element u listi(po prezimenu),
//E.briše odreðeni element iz liste,
//U zadatku se ne smiju koristiti globalne varijable.

#define _CRT_SECURE_NO_WARNINGS
#define MAX_STRING 128

#include<stdio.h>
#include<stdlib.h>

struct _Person;
typedef struct _Person* Position;

typedef struct _Person {
	char name[MAX_STRING];
	char surname[MAX_STRING];
	int BirthYear;
	Position next;
}Person;

Position Create(char* name, char* surname, int birthyear);
int AddOnBeginning(Position Head, char* name, char* surname, int birthyear);//prepend
int InsertAfter(Position last, Position new);
int Print(Position Head);
int AddOnEnd(Position Head, char* name, char* surname, int birthyear);//NE RADI
Position FindLast(Position Head);
int FindBySurname(Position Head, char* surname);
Position DeleteWanted(Position Head, char* surname);//NE RADI
Position FindBefore(Position Head);//doddatak za brisanje
//int Menu();

int main() {
	Person Head = { .next = NULL, .name = {0}, .surname = {0},
	.BirthYear = 0 };
	Position P = &Head;

	int answer = 1;
	char name[MAX_STRING] = { ' ' };
	char surname[MAX_STRING] = { ' ' };
	int birthyear = 0;

	while (answer)
	{
		system("cls"); // nadodaj ovo da se "refresha" pojava narednih printf linija a lista se spremi i pise iznova !!!
		Print(P->next);
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
			scanf(" %d", &birthyear);
			AddOnBeginning(P, name, surname, birthyear);//saljemo adresu head-a
			break;

		case 2:
			printf("\nUnesite ime i prezime studenta na kraj liste: ");
			scanf(" %s %s", name, surname);
			printf("Unesite godinu rodjenja studenta: ");
			scanf(" %d", &birthyear);
			AddOnEnd(P, name, surname, birthyear);
			break;

		case 3:
			printf("\nUnesite prezime studenta kojega zelite pronaci: ");
			scanf(" %s", surname);
			FindBySurname(P, surname);
			break;

		case 4:
			printf("\nUnesite prezime studenta kojega zelite izbrisati: ");
			scanf(" %s", surname);
			DeleteWanted(P, surname);//saljemo adresu
			break;
		}
	}

	return EXIT_SUCCESS;
}

Position Create(char* name, char* surname, int birthyear) {

	Position q = NULL;

	q = (Position)malloc(sizeof(Person));
	if (!q) {
		perror("Can't allocate memory!\n");
		return -1;
	}

	strcpy(q->name, name);
	strcpy(q->surname, surname);
	q->BirthYear = birthyear;
	q->next = NULL;

	return q;
}

int AddOnBeginning(Position Head, char* name, char* surname, int birthyear) {
	Position newPerson = NULL;

	newPerson = Create(name, surname, birthyear);
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return -1;
	}

	InsertAfter(Head, newPerson);//u ovu fju saljemo adresa head-a

	return EXIT_SUCCESS;
}

int InsertAfter(Position head, Position new) {
	new->next = head->next;
	head->next = new;

	return EXIT_SUCCESS;
}

int Print(Position P) {
	while (P != NULL) {
		printf("%s %s, %d. godine\n", P->name, P->surname, P->BirthYear);
		P = P->next;
	}

	return EXIT_SUCCESS;
}

int AddOnEnd(Position Head, char* name, char* surname, int birthyear) {//adresa head-a
	Position newPerson = NULL;
	Position last = NULL;

	newPerson = Create(name, surname, birthyear);
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return -1;
	}

	last = FindLast(Head);//adresa head-a
	InsertAfter(last, newPerson);
	return EXIT_SUCCESS;
}

Position FindLast(Position Head) {
	Position temp = Head;

	while (temp->next != NULL) {
		temp = temp->next;
	}

	return temp;
}

int FindBySurname(Position Head, char* surname) {//adresa head-a
	Position temp = Head->next;

	while (temp != NULL) {
		if (strcmp(temp->surname, surname) == 0) {
			printf("\nWanted student is: %s %s, %d.\n", temp->name, temp->surname, temp->BirthYear);
			system("pause > nul"); // nadodaj da "ponistis" system("cls") iz main-a (47)
			return temp;
		}
		temp = temp->next;
	}

	return EXIT_SUCCESS;
}

Position DeleteWanted(Position Head, char* surname) {//adresa head-a
	Position temp = Head;
	Head = FindBefore(surname, temp);

	if (NULL == Head) 
		printf("Error!\n");
	else {
		temp = Head->next;
		Head->next = temp->next;
		free(temp);
	}
	return EXIT_SUCCESS;
}

Position FindBefore(char* surname, Position P) {//adresa head-a
	Position prev = P;
	P = P->next;
	while (P!=NULL && (strcmp(P->surname, surname)!=0)) {
		prev = P;
		P = P->next;
	}
	if (P == NULL)
		return NULL;
	else
		return prev;
}
