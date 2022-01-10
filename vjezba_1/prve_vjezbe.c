#define _CTR_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_line (1024)

typedef struct {
	char ime[30];
	char prezime[50];
	float bodovi;
	float relativni;
}Studenti;

int NadiBrojStudenata(char NazivDatoteke[max_line]);
Studenti* AlokacijaMemorije(int BrojStudenata, char dat[]);
int ispis(int BrojStudenata, Studenti* stud);
int MaxBodovi(int BrojStudenata, Studenti* stud);


int main() {
	char NazivDatoteke[max_line] = "studenti.txt";
	int BrojStudenata = 0;
	Studenti* stud = NULL;
	int IspisStudenata=0;

	BrojStudenata = NadiBrojStudenata(NazivDatoteke);
	stud = AlokacijaMemorije(BrojStudenata, NazivDatoteke);
	IspisStudenata = ispis(BrojStudenata, stud);
	
	free(stud);
	return 0;
}


int NadiBrojStudenata(char NazivDatoteke[]) {
	FILE* file = NULL;
	int brojac = 0;
	char string[max_line] = { 0 };


	file = fopen(NazivDatoteke, "r");

	if (file == NULL) {
		printf("Greska pri otvaranju datoteke.");
		return 1;
	}

	while (!feof(file)) {
		fgets(string, sizeof(string), file);
		brojac++;
	}
	fclose(file);

	return brojac;
}
Studenti* AlokacijaMemorije(int BrojStudenata, char dat[]) {
	FILE* file = NULL;
	Studenti* podaci =NULL;
	int i=0;

	file = fopen(dat, "r");

	if (file == NULL) {
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	podaci = (Studenti*)malloc(BrojStudenata * sizeof(Studenti));

	for(i=0;i<BrojStudenata;i++) {
		fscanf(file," %s %s %f", podaci[i].ime, podaci[i].prezime, &podaci[i].bodovi);
	}

	fclose(file);
	return podaci;
}

int ispis(int BrojStudenata, Studenti* stud) {
	int i;

	int MaxBrojBodova = MaxBodovi(BrojStudenata, stud);

	printf("IME\tPREZIME\t\tRELATIVNI BODOVI\tAPSOLUTNI BODOVI\n");
	for (i = 0;i < BrojStudenata;i++) {
		stud[i].relativni = ((stud[i].bodovi / MaxBrojBodova) * 100);
		printf("%s\t%s\t\t%f\t\t%f\n", stud[i].ime, stud[i].prezime,stud[i].relativni, stud[i].bodovi);
	}

	return 0;
}
int MaxBodovi(int BrojStudenata, Studenti* stud) {
	int i;
	int max = 0;

	for (i = 0;i < BrojStudenata;i++) {
		if (stud[i].bodovi > max) {
			max = stud[i].bodovi;
		}
	}

	return max;
}