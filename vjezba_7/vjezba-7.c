#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max_size (50)

struct _direktorij;
typedef struct _direktorij* DirPozicija;
typedef struct _direktorij {
	char ime[max_size];
	DirPozicija dijete;
	DirPozicija brat;
}direktorij;

struct _stog;
typedef struct _stog* StogPozicija;
typedef struct _stog {
	DirPozicija roditelj;
	StogPozicija next;
}Stog;

DirPozicija md(DirPozicija trenutni, DirPozicija element);
int dir(DirPozicija q);
StogPozicija StvoriStog();
DirPozicija StvoriDirektorij();
int IzbrisiMemoriju(DirPozicija roditelj);
DirPozicija cd_dir(StogPozicija stog, DirPozicija trenutni);
int push(StogPozicija stog, DirPozicija trenutni);
StogPozicija pop(StogPozicija stog);


int main()
{
	int x = 1;
	char y = { 0 };

	StogPozicija stog = NULL;
	DirPozicija roditelj = NULL, trenutni = NULL, element = NULL;

	stog = StvoriStog();
	roditelj = StvoriDirektorij();
	trenutni = roditelj;

	while (x)
	{
		printf("1- md, 2 - cd dir, 3 - cd.., 4 - dir 5 � izlaz\n");
		scanf(" %c", &y);

		switch (y) {
		case '1':
			element = StvoriDirektorij();
			trenutni->dijete = md(trenutni->dijete, element);
			break;
		case '2':
			element = cd_dir(stog, trenutni);
			trenutni = element;
			break;
		case '3':
			element = pop(stog);
			if (!element)
				printf("Ne moze ici vise od root-a!");
			else
				trenutni = element;
			break;
		case '4':
			dir(trenutni);
			break;
		case '5':
			IzbrisiMemoriju(roditelj);
			x = 0;
			break;
		default:
			printf("Pogresan upis! Probajte ponovo:");
			break;
		}
	}
	return 0;
}
StogPozicija StvoriStog()
{
	StogPozicija q = NULL;
	q = (StogPozicija)malloc(sizeof(Stog));
	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije!\n");
		return NULL;
	}
	q->next = NULL;

	return q;
}

DirPozicija StvoriDirektorij()
{
	DirPozicija q = NULL;
	q = (DirPozicija)malloc(sizeof(direktorij));
	if (q == NULL)
	{
		printf("Greska pri alokaciji memorije!\n");
		return NULL;
	}
	q->dijete = NULL;
	q->brat = NULL;

	printf("\nUnesi ime:");
	scanf(" %s", q->ime);

	return q;
}


DirPozicija md(DirPozicija trenutni, DirPozicija element)
{
	if (trenutni == NULL)
		return element;

	if (strcmp(trenutni->ime, element->ime) < 0)
	{
		trenutni->brat = md(trenutni->brat, element);
	}
	else if (strcmp(trenutni->ime, element->ime) > 0)
	{
		element->brat = trenutni;
		return element;
	}
	else if (strcmp(trenutni->ime, element->ime) == 0)
	{
		printf("\nTo ime je vec uneseno.");
	}
	return trenutni;
}
int dir(DirPozicija trenutni)
{
	DirPozicija pom = NULL;
	printf(" %s:\n", trenutni->ime);

	if (trenutni->dijete != NULL)
	{
		pom = trenutni->dijete;
		while (pom != NULL)
		{
			printf(" %s\t", pom->ime);
			pom = pom->brat;
		}
	}
	printf("\n");
	return 0;
}

int IzbrisiMemoriju(DirPozicija roditelj)
{
	if (roditelj == NULL)
		return 0;
	IzbrisiMemoriju(roditelj->brat);
	IzbrisiMemoriju(roditelj->dijete);
	return 0;
}

DirPozicija cd_dir(StogPozicija stog, DirPozicija trenutni)
{
	DirPozicija q = NULL, pom = NULL;
	char  ime[max_size] = { 0 };

	printf("Unesi ime direktorija kojem zelis pristupiti:\n");
	scanf(" %s", ime);

	if (trenutni->dijete == NULL)
	{
		printf("Direktorij je prazan!\n");
		return NULL;
	}
	pom = trenutni->dijete;
	while (pom != NULL)
	{
		if (strcmp(pom->ime, ime) == 0)
			q = pom;
		pom = pom->brat;
	}
	push(stog, trenutni);
	return q;
}
int push(StogPozicija stog, DirPozicija trenutni)
{
	StogPozicija q = NULL;
	q = StvoriStog();
	q->roditelj = trenutni;
	q->next = stog->next;
	stog->next = q;
	return 0;
}

StogPozicija pop(StogPozicija stog)
{
	StogPozicija pom = NULL;
	DirPozicija q = NULL;

	if (stog == NULL || stog->next == NULL)
		return NULL;
	pom = stog->next;
	q = pom->roditelj;
	stog->next = pom->next;

	free(pom);
	return q;
}