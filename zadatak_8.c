#define _CRT_SECURE_NO_WARNINGS_
#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_size (50)

struct _cvor;
typedef struct _cvor* pozicija;
typedef struct _cvor
{
	int broj;
	pozicija L;
	pozicija D;
}cvor;

pozicija StvoriPrazno(pozicija S);
pozicija UnesiElement(pozicija S, int broj);
pozicija brisi(pozicija S, int broj);
pozicija TraziMin(pozicija S);
pozicija trazi(pozicija S, int el);
int inorder(pozicija S);
int preorder(pozicija S);
int postorder(pozicija S);

int main()
{
	char c = { 0 };
	int x = 1, broj = 0;
	pozicija root = NULL, trenutni = NULL;

	root = StvoriPrazno(root);
	printf("\t 1 - unesi novi element\n\t 2 - obrisi element\n\t 3 - pronadi element\n\t ");
	printf("Ispisi:\n\t 4 - inorder\n\t 5 - preorder\n\t 6 - postorder\n\t  7 - izlaz iz petlje\n");
	while (x)
	{
		printf(":");
		scanf(" %c", &c);

		switch (c)
		{
		case '1':
			printf("Unesi broj koji zelis unjeti u stablo:\n");
			scanf("%d", &broj);
			root = UnesiElement(root, broj);
			if (root == NULL)
				printf("Taj broj je vec unesen u stablo!\n");
			break;
		case '2':
			printf("Unesi element koji zelis izbrisati:\n");
			scanf("%d", &broj);
			trenutni = brisi(root, broj);
			if (trenutni == NULL)
				printf("Broj %d ne postoji u stablu\n", broj);
			else
				printf("Obrisali ste broj %d\n", broj);
			break;
		case '3':
			printf("Unesi element koji zelis pronaci:\n");
			scanf("%d", &broj);
			trenutni = trazi(root, broj);
			if (trenutni == NULL)
				printf("Broj %d ne postoji u stablu\n", broj);
			else
				printf("Broj %d uspjesno pronaden\n", broj);
			break;
		case '4':
			inorder(root);
			printf("\n");
			break;
		case '5':
			preorder(root);
			printf("\n");
			break;
		case '6':
			postorder(root);
			printf("\n");
			break;
		case '7':
			root = StvoriPrazno(root);
			x = 0;
			break;
		default:
			printf("Krivi unos!Pokusaj ponovo:\n");
			break;
		}
	}
	return 0;
}

pozicija StvoriPrazno(pozicija S)
{
	if (S != NULL)
	{
		S->L = StvoriPrazno(S->L);
		S->D = StvoriPrazno(S->D);
		free(S);
	}
	return NULL;
}

pozicija UnesiElement(pozicija S, int el)
{
	if (S == NULL)
	{
		S = (pozicija)malloc(sizeof(cvor));
		S->broj = el;
		S->L = NULL;
		S->D = NULL;
	}
	else if (el < S->broj)
	{
		S->L = UnesiElement(S->L, el);
	}
	else if (el > S->broj)
	{
		S->D = UnesiElement(S->D, el);
	}
	else if (S->broj == el)
	{
		printf("Taj je broj vec unesen!");
		return S;
	}

	return S;
}

int inorder(pozicija S)
{
	if (S == NULL)
		return 0;

	inorder(S->L);
	printf("%d\t", S->broj);
	inorder(S->D);

	return 0;
}

int preorder(pozicija S)
{
	if (S == NULL)
		return 0;
	printf("%d\t", S->broj);
	preorder(S->L);
	preorder(S->D);

	return 0;
}
int postorder(pozicija S)
{
	if (S == NULL)
		return 0;

	postorder(S->L);
	postorder(S->D);
	printf("%d\t", S->broj);

	return 0;
}

pozicija brisi(pozicija S, int el)
{
	pozicija pom = NULL;

	if (S == NULL)
	{
		printf("Taj element ne postoji.");
		return NULL;
	}
	else if (el < S->broj)
	{
		S->L = brisi(S->L, el);
	}
	else if (el > S->broj)
	{
		S->D = brisi(S->D, el);
	}
	else if (S->L != NULL && S->D != NULL)
	{
		pom = TraziMin(S->D);
		S->broj = pom->broj;
		S->D = brisi(S->D, S->broj);
	}
	else
	{
		pom = S;

		if (S->L == NULL)
			S = S->D;
		else
			S = S->L;

		free(pom);
	}
	return S;
}

pozicija TraziMin(pozicija S)
{
	if (S == NULL)
		return NULL;
	else if (S->L == NULL)
		return S;

	return TraziMin(S->L);
}

pozicija trazi(pozicija S, int el)
{
	if (S == NULL)
		return NULL;
	else if (el > S->broj)
		return trazi(S->D, el);
	else if (el < S->broj)
		return trazi(S->L, el);

	return S;
}
