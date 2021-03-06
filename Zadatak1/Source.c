#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_SIZE 128
#define MAX_LINE 1024
#define MAX_BODOVI 100

//Napisati program koji prvo proèita koliko redaka ima datoteka, tj.koliko ima studenata
//zapisanih u datoteci.Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
//studenata(ime, prezime, bodovi) i uèitati iz datoteke sve zapise.Na ekran ispisati ime,
//prezime, apsolutni i relativni broj bodova.
//Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
//relatvan_br_bodova = br_bodova / max_br_bodova * 100

typedef struct {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
}student;

int ProcitajBrojRedakaDatoteke(char* nazivDatoteke);
student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteke);
double maksimalanBrojBodovaStudenata(student* studenti, int brojStudenata);

int main()
{
	int brojStudenata = 0;
	int brojac = 0;
	student* studenti = NULL;
	char* nazivDatoteke = "studenti.txt";
	double maxBrojBodova = 0;

	brojStudenata = ProcitajBrojRedakaDatoteke(nazivDatoteke);
	studenti = AlocirajMemorijuIProcitajStudente(brojStudenata, nazivDatoteke);
	maxBrojBodova = maksimalanBrojBodovaStudenata(studenti, brojStudenata);

	printf("Ime i Prezime\tApsolutni bodovi\tRelativni bodovi\n\n");

	for (brojac = 0; brojac < brojStudenata; brojac++)
	{
		printf("%s %s\t%lf\t%lf\n", studenti[brojac].ime, studenti[brojac].prezime,
			studenti[brojac].bodovi, (studenti[brojac].bodovi / maxBrojBodova) * 100);
	}

	return 0;
}


int ProcitajBrojRedakaDatoteke(char* nazivDatoteke)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(nazivDatoteke, "r");
	if (!datoteka) {
		printf("Greska!!!\n");
		return -1;
	}

	while (!feof(datoteka)) {
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}

	fclose(datoteka);

	return brojac;
}

student* AlocirajMemorijuIProcitajStudente(int brojStudenata, char* nazivDatoteke)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	student* studenti = NULL;

	studenti = (student*)malloc(brojStudenata * sizeof(student));
	datoteka = fopen(nazivDatoteke, "r");
	if (!datoteka)
	{
		printf("Greska alociranja memorije!\n");
		free(studenti);
		return NULL;
	}
	while (!feof(datoteka))
	{
		fscanf(datoteka, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}

	fclose(datoteka);

	return studenti;

}

double maksimalanBrojBodovaStudenata(student* studenti, int brojStudenata)
{
	int i = 0;
	double max = 0;

	max = studenti[0].bodovi;

	for (i = 0; i < brojStudenata; i++)
	{
		if (studenti[i].bodovi > max)
			max = studenti[i].bodovi;
	}
	return max;
}