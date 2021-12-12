/*Napisati program koji pomocu vezanih listi(stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod - direktorija, ispis sadrzaja direktorija i
povratak u prethodni direktorij.Tocnije program treba preko menija simulirati
koristenje DOS naredbi : 1 - "md", 2 - "cd <dir>", 3 - "cd..", 4 - "dir" i 5 – izlaz.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX 50

typedef struct dir* dPosition;
typedef struct stack* sPosition;

typedef struct dir {
	char* name;
	dPosition sibling;
	dPosition child;
}Dir;

typedef struct stack {
	dPosition directory;

	sPosition next;
	sPosition prev;
}Stack;

int MakeDir(dPosition);
int Menu(dPosition, sPosition);
int Directory(dPosition);
dPosition ChangeDir(dPosition, sPosition);
dPosition Back(dPosition, sPosition);
dPosition FindByName(char*, dPosition);
int PushStack(sPosition, dPosition);
dPosition PopStack(sPosition);
int Line(sPosition, dPosition, dPosition);
sPosition FindLast(sPosition);

int main()
{
	dPosition root;
	root = (dPosition)malloc(sizeof(Dir));
	root->child = NULL;
	root->sibling = NULL;
	sPosition head;
	head = (sPosition*)malloc(sizeof(Stack));
	head->next = NULL;
	head->prev = NULL;
	root->name = (char*)malloc(MAX * sizeof(char));
	root->name = "C:";

	int status = 1;

	while (status) {
		status = Menu(root, head);
	}

	return 0;
}

int Line(sPosition head, dPosition root, dPosition curr)
{
	sPosition s;

	s = FindLast(head);

	if (head->next == NULL) {
		printf("%s>", root->name);
		return EXIT_SUCCESS;
	}

	while (s->prev != NULL) {
		printf("%s>", s->directory->name);
		s = s->prev;
	}

	printf("%s>", curr->name);

	return EXIT_SUCCESS;
}

sPosition FindLast(sPosition head)
{
	sPosition s;
	s = head->next;

	if (s == NULL) {
		return NULL;
	}

	while (s->next != NULL) {
		s = s->next;
	}

	return s;
}

int Menu(dPosition root, sPosition head) {
	dPosition curr = root;
	char command[MAX] = { 0 };

	//printf("****************************************\n");
	printf("md <filename> - Add new directory\n");
	printf("cd <filename> - Open directory\n");
	printf("cd.. - Return to the previous directory\n");
	printf("dir - Print directories in the current directory\n");
	printf("exit - Exit the program\n\n");
	//printf("****************************************\n");

	while (1) {
	
		Line(head, root, curr);
		scanf("%s", command);

		if (!strcmp(command, "md")) {
			MakeDir(curr);
		}

		else if (!strcmp(command, "cd")) {
			curr = ChangeDir(curr, head);
		}

		else if (!strcmp(command, "cd..")) {
			curr = Back(curr, head);
		}

		else if (!strcmp(command, "dir")) {
			Directory(curr);
		}

		else if (!strcmp(command, "exit")) {
			system("cls");
			return 0;
		}

		else
			printf("404 error: Command not found\n");
	}

	return EXIT_SUCCESS;
}

int MakeDir(dPosition curr) {
	dPosition directory;
	directory = (dPosition)malloc(sizeof(Dir));
	directory->name = (char*)malloc(MAX * sizeof(char));

	if (!directory)
		printf("Cannot alocate memory!\n");

	if (curr->child != NULL) {
		curr = curr->child;
		while (curr->sibling != NULL) {
			curr = curr->sibling;
		}
		curr->sibling = directory;
	}

	else
		curr->child = directory;

	scanf(" %s", directory->name);

	directory->sibling = NULL;
	directory->child = NULL;

	return EXIT_SUCCESS;
}

int Directory(dPosition curr) {
	if (curr->child == NULL) {
		printf("This directory is empty!\n");
		return EXIT_SUCCESS;
	}

	curr = curr->child;

	printf("Directories: \n");
	printf("\t%s\n", curr->name);

	while (curr->sibling != NULL) {
		printf("\t%s\n", curr->sibling->name);
		curr = curr->sibling;
	}

	return EXIT_SUCCESS;
}

dPosition FindByName(char* name, dPosition curr) {
	if (curr->child == NULL) {
		printf("This directory is empty!");
		return EXIT_SUCCESS;
	}

	curr = curr->child;

	while (strcmp(name, curr->name) != 0 && curr->sibling != NULL) {
		curr = curr->sibling;
	}

	if (curr->sibling == NULL) {
		if (strcmp(name, curr->name) != 0)
			return NULL;
		else
			return curr;
	}

	else
		return curr;
}

int PushStack(sPosition head, dPosition directory) {

	sPosition q = (sPosition)malloc(sizeof(Stack));

	q->next = head->next;
	q->prev = head;

	if (head->next != NULL) {
		head->next->prev = q;
	}

	head->next = q;
	q->directory = directory;

	return EXIT_SUCCESS;
}

dPosition PopStack(sPosition head) {

	sPosition q = (sPosition)malloc(sizeof(Stack));
	dPosition p;

	if (head->next == NULL)
		return NULL;

	q = head->next;
	p = q->directory;
	head->next = head->next->next;

	if (head->next != NULL)
		head->next->prev = head;

	free(q);

	return p;
}

dPosition Back(dPosition curr, sPosition head)
{
	dPosition s;

	s = PopStack(head);

	if (s == NULL) {
		printf("Cannot exit the root directory!\n");
		s = curr;
	}

	return s;
}

dPosition ChangeDir(dPosition curr, sPosition head)
{
	dPosition s;
	char* name;
	name = (char*)malloc(MAX * sizeof(char));

	scanf("%s", name);

	if (curr->child == NULL) {
		printf("There's no directory that you are able to open!\n");
		return curr;
	}

	s = FindByName(name, curr);

	if (s == 0) {
		printf("Directory not found!\n");
		return curr;
	}

	PushStack(head, curr);

	return s;
}