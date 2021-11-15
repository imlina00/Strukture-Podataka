#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define MAX_SIZE 50

/*Napisati program koji iz datoteke cita postfiks izraz i zatim koristenjem stoga racuna
rezultat.Stog je potrebno realizirati preko vezane liste.*/

struct Element;
typedef struct Element* Position;

typedef struct Element {
	double broj;
	Position next;
}El;

Position StvoriElement(double broj);
int UmetniNakon(Position P, Position noviElement);
int Push(Position Head, double broj);
int IzbrisiNakon(Position P);
int Pop(double* destinacija, Position Head);
int Operacija(Position Head, char op);
int RacunajPostfixIzDat(char* dat);
int IzbrisiSve(Position Head);

int main(int argc, char** argv)
{
	char dat[MAX_SIZE] = { 0 };

	printf("Unesite ime datoteke:");
	scanf(" %s", dat);

	RacunajPostfixIzDat(dat);

	return EXIT_SUCCESS;
}

Position StvoriElement(double broj)
{
	Position noviElement = NULL;

	noviElement = (Position)malloc(sizeof(El));
	if (!noviElement)
	{
		perror("Nije moguce alocirati memoriju!\n");
		system("pause > nul");
		return NULL;
	}

	noviElement->broj = broj;
	noviElement->next = NULL;

	return noviElement;

}

int UmetniNakon(Position P, Position noviElement)
{
	noviElement->next = P->next;
	P->next = noviElement;

	return EXIT_SUCCESS;
}

int Push(Position Head, double broj)
{
	Position noviElement = NULL;

	noviElement = StvoriElement(broj);
	if (!noviElement)
		return -1;

	UmetniNakon(Head, noviElement);
}

int IzbrisiNakon(Position P)
{
	Position temp = P->next;

	if (!temp)
		return EXIT_SUCCESS;

	P->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int Pop(double* destinacija, Position Head)
{
	Position prvi = Head->next;

	if (!prvi)
	{
		perror("Postfix nije valjan ili nema vise operanada i operacija, provjerite sadrzaj datoteke!\n");
		system("pause > nul");
		return -1;
	}

	*destinacija = prvi->broj;

	IzbrisiNakon(Head); //skidamo "knjigu"

	return EXIT_SUCCESS;
}

int IzbrisiSve(Position Head)
{
	Position temp = Head;

	while (temp->next)
	{
		IzbrisiNakon(temp);
	}

	return EXIT_SUCCESS;
}

int Operacija(Position Head, char op)
{
	double operand2 = 0.0;
	double operand1 = 0.0;
	double rez = 0.0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;


	status2 = Pop(&operand2, Head);
	if (status2 != EXIT_SUCCESS)
		return -1;

	status1 = Pop(&operand1, Head);
	if (status1 != EXIT_SUCCESS)
		return -2;

	switch (op)
	{
	case '+':
	{
		rez = operand1 + operand2;
		printf("%lf %c %lf = %lf\n", operand1, op, operand2, rez);
		break;
	}

	case '-':
	{
		rez = operand1 - operand2;
		printf("%lf %c %lf = %lf\n", operand1, op, operand2, rez);
		break;
	}

	case '*':
	{
		rez = operand1 * operand2;
		printf("%lf %c %lf = %lf\n", operand1, op, operand2, rez);
		break;
	}

	case '/':
	{
		if (operand2 == 0)
		{
			printf("Dijeljenje s 0 nije moguce!\n");
			return -3;
		}
		rez = operand1 / operand2;
		printf("%lf %c %lf = %lf\n", operand1, op, operand2, rez);
		break;
	}

	default:
	{
		printf("Operacija nije podrzana!\n");
		system("pause > nul");
		IzbrisiSve(Head);
		return -4;
	}
	}

	Push(Head, rez);

	return EXIT_SUCCESS;
}

int RacunajPostfixIzDat(char* dat)
{

	FILE* fp = NULL;
	int fpDuljina = 0;
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int nB = 0;
	char op = 0;
	double vrijednost = 0;
	int status = 0;
	int brojac = 0;
	El Head = { .broj = 0, .next = NULL };
	fp = fopen(dat, "rb");

	if (!fp)
	{
		perror("Nije moguce otvoriti datoteku!\n");
		system("pause > nul");
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	fpDuljina = ftell(fp);

	buffer = (char*)malloc((fpDuljina + 1)*sizeof(char));

	if (!buffer)
	{
		perror("Nije moguce alocirati memoriju!\n");
		system("pause > nul");
		return -1;
	}

	rewind(fp);

	fread(buffer, sizeof(char), fpDuljina, fp);
	printf("Postfix: \n");
	fclose(fp);

	currentBuffer = buffer;
	while (strlen(currentBuffer) > 0)
	{
		brojac = sscanf(currentBuffer, " %lf %n", &vrijednost, &nB);

		if (brojac == 1)
		{
			Push(&Head, vrijednost);
			currentBuffer += nB;
		}

		else
		{
			sscanf(currentBuffer, " %c %n", &op, &nB);
			status = Operacija(&Head, op);

			if (status != EXIT_SUCCESS)
			{
				free(buffer);
				while (Head.next = NULL)
				{
					IzbrisiNakon(&Head);
				}
				return -1;
			}

				currentBuffer += nB;
			}
		}
	
		free(buffer);

		return EXIT_SUCCESS;
}