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

int umetni(pozicija head);
int UnesiPodatke(pozicija p);
int ispis(pozicija p);
int UmetniNaKraj(pozicija head);
int izbrisi(pozicija p);

pozicija PronadiZadnji(pozicija head);
pozicija PronadiPrethodni(pozicija p);
pozicija PronadiPrezime(pozicija p);

int main() {
	int x = 1;
	char i = 0;

	pozicija head=NULL;
	head = (pozicija) malloc(sizeof(osoba));
	head->next = NULL;

	if (head == NULL)
		return -1;
	while (x)
	{
		printf("\n\nUnesi broj koji zelis:\n1)dodaj novi element na pocetak liste\n2)ispisi listu\n");
		printf("3)dodaj novi element na kraj liste\n4)pronadi element u listi(po prezimenu)\n");
		printf("5)obrisi odredeni element iz liste\n6)prekini petlju\n");
		scanf(" %c", &i);
		switch (i) {
		case '1':  
			umetni(head);
			break;
		case '2': 
			ispis(head->next);
			break;
		case '3': 
			UmetniNaKraj(head);
			break;
		case '4': 
			PronadiPrezime(head->next);
			break;
		case '5': 
			izbrisi(head);
			break;
		case '6': 
			x = 0;
			break;
		}
	}
	return 0;
}

int umetni(pozicija head) {
	pozicija prvi = NULL;
	prvi = (pozicija)malloc(sizeof(osoba));

	if (prvi == NULL)
		return -1;
	UnesiPodatke(prvi);
	prvi->next = head->next;
	head->next = prvi;

	return 0;
}
int UnesiPodatke(pozicija p) {
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
	else {
		printf("IME\tPREZIME\tGODINA RODENJA\n");
		while (p != 0) {
			printf(" %s\t %s\t%d\n", p->ime, p->prezime, p->god_rodenja);
			p = p->next;
		}
	}
	return 0;
}
int UmetniNaKraj(pozicija head) {
	pozicija zadnji = NULL;
	zadnji = PronadiZadnji(head);
	umetni(zadnji);
	return 0;
}
pozicija PronadiZadnji(pozicija head) {
	while (head->next != NULL)
		head = head->next;

	return head;
}
int izbrisi(pozicija p) {
	pozicija trenutni = NULL;
	pozicija prethodni = NULL;

	prethodni = PronadiPrethodni(p);

	if (prethodni == NULL)
		return -1;

	trenutni = prethodni->next;
	prethodni->next = prethodni->next->next;
	free(trenutni);
	
	return 0;
}
pozicija PronadiPrethodni(pozicija p) {
	pozicija trenutni = NULL;
	pozicija prethodni = NULL;
	char prezime[max_size];

	prethodni = p;
	trenutni = prethodni->next;

	printf("Unesi prezime koje zelis izbristi:");
	scanf(" %s", prezime);

	while (trenutni != NULL && strcmp(trenutni->prezime, prezime) != 0) {
		prethodni = trenutni;
		trenutni = prethodni->next;
	}
	
	return prethodni;
}
pozicija PronadiPrezime(pozicija p) {
	char prezime[max_size];

	printf("Unesi prezime koje zelis pronaci:");
	scanf(" %s", prezime);

	while (p != NULL && strcmp(p->prezime, prezime) != 0) {
		p = p->next;
	}
	if (p == NULL) {
		printf("To prezime ne postoji.");
		return -1;
	}
	printf("Pronadeni element je: %s %s %d\n", p->ime, p->prezime, p->god_rodenja);
	return p;
}


