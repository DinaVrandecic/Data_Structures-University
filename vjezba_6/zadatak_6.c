#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable :4996 )
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _lista1;
typedef struct _lista1* pozicija1;

struct _lista2;
typedef struct _lista2* pozicija2;

typedef struct _datum
{
	int godina;
	int mjesec;
	int dan;
}Datum;
typedef struct _lista2
{
	char proizvod[max];
	int kolicina;
	int cijena;
	pozicija2 next;
}lista2;

typedef struct _lista1
{
	char racun[max];
	Datum datum;
	pozicija2 head;
	pozicija1 next;
}lista1;


pozicija1 Inicijalizacija1(pozicija1 p);
int ProcitajFile(char *file, pozicija1 head);
int UnesiListu1(char *file2,int godina,int mjesec,int dan, pozicija1 head);
int UnesiPodatke(pozicija1 p, char* ime, int godina, int mjesec, int dan);
int UnesiPodatke2(char* naziv, int kolicina, int cijena, pozicija2 q);
pozicija2 ProcitajListu2(char* file2, pozicija2 head);
int UnesiListu2(char* naziv, int kolicina, int cijena, pozicija2 p);
pozicija2 Inicijaliziraj2(pozicija2 q);
int Ispis(pozicija1 head);
int Ispis2(pozicija2 p);
int Pretraga(pozicija1 head, char*artikl, int godina,int mjesec,int dan);
int InicDatum(pozicija1 p);
int UsporediDatume(pozicija1 p, int godina, int mjesec, int dan);

int main()
{
	pozicija1 head=NULL;
	char file[max] = "racuni.txt", artikl[max] = { 0 };
	int x = 1, godina=0, mjesec=0, dan=0;
	char op = { 0 };

	head=Inicijalizacija1(head);
	ProcitajFile(file, head);
	Ispis(head->next);

	printf("Unesi:\t1)za ponovni unos\n\t2)za izlazak iz petlje\n");
	while (x)
	{
		scanf(" %c", &op);
		switch (op)
		{
		case '1':
			printf("Odaberi artikl koji zelis prezraziti:\n");
			scanf(" %s", artikl);
			printf("Unesi datum do kojeg zelis ispis(u obliku YYYY-MM-DD:\n");
			scanf("%d-%d-%d", &godina, &mjesec, &dan);
			printf("%d-%d-%d", godina, mjesec, dan);
			Pretraga(head->next, artikl, godina, mjesec, dan);
			break;
		case '2':
			printf("Izlazak iz petlje.\n");
			x = 0;
			break;
		}
	}
	return 0;
}

int Ispis(pozicija1 p)
{
	while (p != NULL)
	{
		printf("--%s %d-%d-%d:\n", p->racun, p->datum.godina, p->datum.mjesec, p->datum.dan);
		Ispis2(p->head);
		p = p->next;
	}
	return 0;
}

int Ispis2(pozicija2 p)
{
	p = p->next;
	while (p != NULL)
	{
		printf("   %s %d %d\n", p->proizvod, p->kolicina, p->cijena);
		p = p->next;
	}
	return 0;
}

pozicija1 Inicijalizacija1(pozicija1 p) 
{
	p = (pozicija1)malloc(sizeof(lista1));
	if (p == NULL)
	{
		printf("Greska pri inicijalizaciji liste1.");
		return NULL;
	}

	strcpy(p->racun, "");
	InicDatum(p);
	p->next = NULL;
	p->head = NULL;

	return p;
}

int ProcitajFile(char* dat, pozicija1 head)
{
	FILE* file1 = NULL;
	FILE* file2 = NULL;
	int godina = 0, mjesec = 0, dan = 0;
	char ime[max] = { 0 };

	file1 = fopen(dat, "r");
	if (file1 == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -2;
	}

	while (!feof(file1))
	{
		fscanf(file1, " %s", ime);
		file2 = fopen(ime, "r");
		if (file2== NULL)
		{
			printf("Greska pri otvaranju datoteke.");
			return -2;
		}

		fscanf(file2, "%d-%d-%d", &godina, &mjesec, &dan);
		UnesiListu1(ime, godina, mjesec, dan,head);
		fclose(file2);
	}
	fclose(file1);

	return 0;
}

int UnesiListu1(char* file2, int godina, int mjesec, int dan, pozicija1 p)
{
	pozicija1 q = NULL;
	int rez = 0;

	q = Inicijalizacija1(q);
	UnesiPodatke(q, file2, godina, mjesec, dan);

	while (p->next != NULL) {
		if (UsporediDatume(p->next, godina, mjesec, dan)< 0) {
			break;
		}
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

int UsporediDatume(pozicija1 p, int godina, int mjesec, int dan)
{
	int rez=0;
	rez = godina - p->datum.godina;

	if (rez == 0)
	{
		rez = mjesec - p->datum.mjesec;
		if (rez == 0)
			rez = dan - p->datum.dan;
	}

	return rez;
}

int UnesiPodatke(pozicija1 p, char *ime, int godina, int mjesec,  int dan)
{
	strcpy(p->racun, ime);
	InicDatum(p);

	p->datum.godina = godina;
	p->datum.mjesec = mjesec;
	p->datum.dan = dan;
	p->head = ProcitajListu2(ime, p->head);

	return 0;
}

int InicDatum(pozicija1 p)
{
	p->datum.godina = 0;
	p->datum.mjesec = 0;
	p->datum.dan = 0;

	return 0;
}

pozicija2 ProcitajListu2(char *file2, pozicija2 head)
{
	FILE* file = NULL;
	int pom1 = 0, pom2 = 0, pom3 = 0, kolicina = 0, cijena = 0;
	char naziv[max] = { 0 };

	head = Inicijaliziraj2(head);

	file = fopen(file2, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return NULL;
	}

	fscanf(file, "%d-%d-%d", &pom1, &pom2, &pom3);
	while (!feof(file))
	{
		fscanf(file, " %s %d %d", naziv, &kolicina, &cijena);
		UnesiListu2(naziv, kolicina, cijena, head);
	}
	fclose(file);
	return head;
}

int UnesiListu2(char *naziv,int kolicina, int cijena, pozicija2 p)
{
	pozicija2 q = NULL;

	q=Inicijaliziraj2(q);
	UnesiPodatke2(naziv, kolicina, cijena, q);

	while (p->next != NULL) {
		if (strcmp(naziv, p->next->proizvod) < 0) {
			break;
		}
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
}

pozicija2 Inicijaliziraj2(pozicija2 q)
{
	q = (pozicija2)malloc(sizeof(lista2));
	if (q== NULL)
	{
		printf("Greska pri inicijalizaciji liste2.");
		return NULL;
	}

	q->kolicina = 0;
	q->cijena = 0;
	strcpy(q->proizvod, "");
	q->next = NULL;

	return q;
}

int UnesiPodatke2(char* naziv, int kolicina, int cijena, pozicija2 q)
{
	q->cijena = cijena;
	q->kolicina = kolicina;
	strcpy(q->proizvod, naziv);

	return 0;
}

int Pretraga(pozicija1 p, char* artikl, int godina, int mjesec, int dan)
{
	int kolicina = 0, cijena = 0;
	pozicija2 pom=NULL;
	pozicija1 p1 =NULL, p2=NULL;

	pom = Inicijaliziraj2(pom);
	p2 = Inicijalizacija1(p2);
	p1= Inicijalizacija1(p1);
	p1 = p;
	
	  
	while (p->next != NULL) {
		if (UsporediDatume(p->next, godina, mjesec, dan) >= 0)
		{
			pom = p->head;

			while (pom != NULL)
			{
				if (strcmp(artikl, pom->proizvod) == 0)
				{
					p2 = p;
					kolicina += pom->kolicina;
					cijena += pom->cijena;
				}
				pom = pom->next;
			}
		}
		p = p->next;
	}

	printf("\n Artikl: %s  Kolicina: %d  Ukupna cijena: %d", artikl, kolicina, cijena);
	printf("\nU razdoblju: od %d-%d-%d do %d-%d-%d", p1->datum.godina, p1->datum.mjesec, p1->datum.dan, p2->datum.godina, p2->datum.mjesec, p2->datum.dan);

	return 0;
}




