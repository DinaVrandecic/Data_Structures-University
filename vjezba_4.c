#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)


#include<stdio.h>
#include<stdlib.h>
#include "vjezba_4.h"
#define MAX 100

int main() {
	Position poly1 = NULL, poly2 = NULL, zbroj = NULL, umnozak = NULL;
	char buff1[MAX], buff2[MAX];

	poly1 = ProcitajDatoteku("polinom1.txt", buff1);
	poly2 = ProcitajDatoteku("polinom2.txt", buff2);
	printf("Polinom 1: ");
	Ispis(poly1->next);
	printf("Polinom 2: ");
	Ispis(poly2->next);

	zbroj = ZbrojiPolinome(poly1->next, poly2->next);
	printf("Zbroj polinoma: ");
	Ispis(zbroj->next);

	umnozak = PomnoziPolinome(poly1->next, poly2->next);
	printf("Umnozak polinoma: ");
	Ispis(umnozak->next);

	return 0;
};