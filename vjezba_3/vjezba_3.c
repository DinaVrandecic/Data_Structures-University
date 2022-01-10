#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#define max_size (50)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct _osoba;
typedef struct _osoba* pozicija;
typedef struct _osoba {
	char ime[max_size];
	char prezime[max_size];
	int god_rodenja;

	pozicija next;
}osoba;

int sortiraj(pozicija p);
int UmetniNakon(pozicija p);
int UmetniPrije(pozicija head);
int umetni1(pozicija head);
int UnesiPodatke1(pozicija p);
int ispis(pozicija p);
int UpisiUDatoteku(pozicija p, char dat1[max_size]);
int ProcitajIzDatoteke(pozicija p, char dat2[max_size]);

pozicija PronadiPrethodni(pozicija p);
pozicija PronadiPrezime(pozicija p);

int main() {
	int x = 1, j;
	char i = 0;
	char prez[max_size] = { 0 }, dat1[max_size] = "upisi.txt", dat2[max_size] = "procitaj.txt";

	pozicija head = NULL;
	pozicija element = NULL;
	head = (pozicija)malloc(sizeof(osoba));
	head->next = NULL;

	if (head == NULL)
		return -1;

	for (j = 0; j < 3; j++) {
		umetni1(head);
	}

	while (x)
	{
		printf("\nUnesi broj koji zelis:\n1)dodaj novi element iza odreðenog elementa\n2)dodaj novi element ispred odreðenog element\n");
		printf("3)upisuje listu u datoteku\n4)cita listu iz datoteke\n5)sortiraj\n");
		printf("6)Ispisi listu\n7)Prekini petlju\n");
		scanf(" %c", &i);
		switch (i) {
		case '1':
			UmetniNakon(head);
			break;
		case '2':
			UmetniPrije(head);
			break;
		case '3':
			UpisiUDatoteku(head->next, dat1);
			break;
		case '4':
			ProcitajIzDatoteke(head, dat2);
			break;
		case '5':
			sortiraj(head);
			break;
		case '6':
			ispis(head->next);
			break;
		case '7':
			x = 0;
			break;
		}
	}
	return 0;
}

int UmetniNakon(pozicija head) {
	pozicija element = NULL;

	element = PronadiPrezime(head->next);

	if (element == NULL)
		return -1;

	umetni1(element);

	return 0;
}
int UmetniPrije(pozicija head) {
	pozicija element = NULL;

	element = PronadiPrethodni(head);

	if (element == NULL)
		return -1;

	umetni1(element);

	return 0;
}
int umetni1(pozicija head) {
	pozicija prvi = NULL;
	prvi = (pozicija)malloc(sizeof(osoba));

	if (prvi == NULL)
		return -1;
	UnesiPodatke1(prvi);
	prvi->next = head->next;
	head->next = prvi;

	return 0;
}
int UnesiPodatke1(pozicija p) {
	printf("Ime:");
	scanf("%s", p->ime);
	printf("Prezime:");
	scanf("%s", p->prezime);
	printf("Godina roðenja:");
	scanf("%d", &p->god_rodenja);

	return 0;
}

int ispis(pozicija p) {
	if (p == NULL) {
		printf("Lista je prazna!");
		return -1;
	}

	printf("IME\tPREZIME\tGODINA RODENJA\n");
	while (p != 0) {
		printf(" %s\t%s\t%d\n", p->ime, p->prezime, p->god_rodenja);
		p = p->next;
	}

	return 0;
}

pozicija PronadiPrethodni(pozicija p) {
	pozicija trenutni = NULL;
	pozicija prethodni = NULL;
	char prezime[max_size] = { 0 };

	prethodni = p;
	trenutni = prethodni->next;

	printf("Unesi prezime prije kojeg zelis unjeti podatke:");
	scanf(" %s", prezime);

	while (trenutni != NULL && strcmp(trenutni->prezime, prezime) != 0) {
		prethodni = trenutni;
		trenutni = prethodni->next;
	}

	return prethodni;
}
pozicija PronadiPrezime(pozicija p) {
	char prezime[max_size] = { 0 };

	printf("Unesi prezime koje zelis pronaci:");
	scanf(" %s", prezime);

	while (p != NULL && strcmp(p->prezime, prezime) != 0)
		p = p->next;

	if (p == NULL) {
		printf("To prezime ne postoji.");
		return -1;
	}

	return p;
}
int sortiraj(pozicija p) {
	pozicija a = NULL, b = NULL, pret = NULL, kraj = NULL;
	for (a = p; a->next != kraj;) {
		pret = a;
		for (b = a->next; b->next != kraj; b = b->next) {
			if (strcmp(b->prezime, b->next->prezime) > 0) {
				pozicija pom = b->next;
				pret->next = pom;
				b->next = pom->next;
				pom->next = b;
				b = pom;
			}
			pret = b;
		}
		kraj = b;
	}
}
int UpisiUDatoteku(pozicija p, char dat1[max_size]) {
	FILE* file = NULL;

	file = fopen(dat1, "w");
	if (file == NULL) {
		printf("Greska pri otvaranju datoteke.");
		return 1;
	}

	fprintf(file, "IME\tPREZIME\tGODINA RODENJA\n");
	while (p != NULL) {
		fprintf(file, " %s\t %s\t%d\n", p->ime, p->prezime, p->god_rodenja);
		p = p->next;
	}

	fclose(file);
	return 0;
}
int ProcitajIzDatoteke(pozicija p, char dat2[max_size]) {
	FILE* file;
	pozicija q = NULL;

	file = fopen(dat2, "r");

	if (file == NULL) {
		printf("GRESKA");
	}
	else {
		while (!feof(file)) {
			q = (pozicija)malloc(sizeof(osoba));

			if (q == NULL) { 
				printf("Memorija se nije alocirala!"); 
				return -1;
			}
			else {
				fscanf(file, "\n %s %s %d", q->ime, q->prezime, &q->god_rodenja);

				q->next = p->next;
				p->next = q;
				p = q;
			}
		}
	}

	fclose(file);
	return 0;
}