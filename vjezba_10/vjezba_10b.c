#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max (60)

struct _lista;
typedef struct _lista* ListaPozicija;
typedef struct _lista
{
	char grad[max];
	int stanovnici;
	ListaPozicija next;
}lista;

struct _stablo;
typedef struct _stablo* StabloPozicija;
typedef struct _stablo
{
	char drzava[max];
	ListaPozicija lista;
	StabloPozicija L;
	StabloPozicija D;
}stablo;


StabloPozicija StvoriElementStabla(StabloPozicija S);
StabloPozicija ProcitajDatDrzave(StabloPozicija p, char* dat);
StabloPozicija UnosStabla(StabloPozicija S, char* drzava, char* drzava_ime);
StabloPozicija PronadiDrzavu(StabloPozicija S, char* drzava);
int inorder(StabloPozicija S);
int NapraviListu(ListaPozicija p, char* grad, int stanovnici);
ListaPozicija ProcitajDatGradovi(ListaPozicija p, char* dat);
int PrintListe(ListaPozicija p);
ListaPozicija StvoriClanListe(ListaPozicija p);
int ispis(ListaPozicija p, int broj);


int main()
{
	StabloPozicija root = NULL, trenutni=NULL;
	char dat[max] = "drzave.txt", drzava[max] = { 0 }, c = { 0 };
	int x = 1, broj=0;

	root = StvoriElementStabla(root);

	root = ProcitajDatDrzave(root, dat);
	inorder(root);


	printf("\n1)Biraj drzavu\n2)Izlaz iz petlje\n");
	while (x)
	{
		printf("\nOdabir:");
		scanf(" %c", &c);
		switch (c)
		{
		case '1':
			printf("Odaberi drzavu:");
			scanf(" %s", drzava);
			trenutni = PronadiDrzavu(root, drzava);
			if (trenutni == NULL)
			{
				printf("Odabrana drzava nije unesena u file.");
				return 0;
			}
			printf("\nPrikazat ce se gradovi s brojem stanovnika vecim nego uneseni.Unesi broj:");
			scanf("%d", &broj);
			ispis(trenutni->lista, broj);
			break;
		case '2':
			printf("Izlazak iz petlje.\n");
			x = 0;
			break;
		}
	}
	
	return 0;
}
ListaPozicija StvoriClanListe(ListaPozicija p)
{
	p = (ListaPozicija)malloc(sizeof(lista));
	if (p == NULL) {
		printf("Greska pri alokaciji memorije");
		return NULL;
	}

	strcpy(p->grad, "");
	p->stanovnici = 0;
	p->next = NULL;

	return p;
}

StabloPozicija StvoriElementStabla(StabloPozicija S)
{
	S = (StabloPozicija)malloc(sizeof(stablo));

	if (S == NULL)
	{
		printf("Greska pri alokaciji memorije.");
		return -1;
	}

	S->L = NULL;
	S->D = NULL;
	S->lista = NULL;
	strcpy(S->drzava, "");

	return S;
}
StabloPozicija ProcitajDatDrzave(StabloPozicija p, char* dat)
{
	FILE* file = NULL;
	char drzava[max] = { 0 }, drzava_dat[max] = { 0 };

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %s\n", drzava, drzava_dat);
		p=UnosStabla(p, drzava, drzava_dat);
	}

	fclose(file);
	return p;
}
StabloPozicija UnosStabla(StabloPozicija S, char* drzava, char* drzava_dat)
{
	if (S == NULL)
	{
		S = StvoriElementStabla(S);
		strcpy(S->drzava, drzava);
		S->lista = NULL;
		S->lista = ProcitajDatGradovi(S->lista, drzava_dat);
	}
	else if (strcmp(S->drzava, drzava) > 0)
		S->L=UnosStabla(S->L, drzava, drzava_dat);
	else if (strcmp(S->drzava, drzava) < 0)
		S->D = UnosStabla(S->D, drzava, drzava_dat);

	return S;
}
ListaPozicija ProcitajDatGradovi(ListaPozicija p, char* dat)
{
	FILE* file = NULL;
	char grad[max] = { 0 };
	int stanovnici = 0;

	p = StvoriClanListe(p);

	file = fopen(dat, "r");
	if (file == NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return -1;
	}

	while (!feof(file))
	{
		fscanf(file, " %s %d", grad, &stanovnici);
		NapraviListu(p, grad, stanovnici);
	}
	
	fclose(file);
	return p;
}
int NapraviListu(ListaPozicija p, char* grad, int stanovnici)
{	
	ListaPozicija q = NULL;
	q = StvoriClanListe(q);

	strcpy(q->grad, grad);
	q->stanovnici = stanovnici;

	while (p->next != NULL)
	{
		if (q->stanovnici < p->next->stanovnici)
			break;
		else if(q->stanovnici == p->next->stanovnici)
		{
			if (strcmp(q->grad, p->next->grad) < 0)
				break;
			else if (strcmp(q->grad, p->next->grad) > 0)
			{
				p = p->next;
				continue;
			}
		}
		p = p->next;
	}
	q->next = p->next;
	p->next = q;
	return 0;
	
}


//pom ispis
int inorder(StabloPozicija S)
{
	if (S == NULL)
		return 0;
	else
	{
		inorder(S->L);
		printf("\n%s:\n", S->drzava);
		PrintListe(S->lista);
		inorder(S->D);
	}
	return 0;
}
int PrintListe(ListaPozicija p)
{
	if (p == NULL)
		return 0;
	else
	{
		p=p->next;
		while (p != NULL)
		{
			printf(" %s-%d ", p->grad, p->stanovnici);
			p = p->next;
		}
		return 0;
	}
}

StabloPozicija PronadiDrzavu(StabloPozicija S, char* drzava)
{
	if (S == NULL)
		return NULL;
	else if (strcmp(drzava, S->drzava) == 0)
		return S;
	else if (strcmp(drzava, S->drzava) > 0)
		return PronadiDrzavu(S->D, drzava);

	return PronadiDrzavu(S->L, drzava);
}
int ispis(ListaPozicija p, int broj)
{
	while (p != NULL)
	{
		if (broj< p->stanovnici)
			printf(" %s-%d", p->grad, p->stanovnici);
		p = p->next;
	}
	return 0;
}
