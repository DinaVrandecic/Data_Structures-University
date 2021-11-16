#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable : 4996)
#include <stdio.h>
#include<stdlib.h>
#include<string.h>

struct _stog;
typedef struct _stog* pozicija;
typedef struct _stog {
	double broj;
	pozicija next;
} stog;


int IzracunajPostfiks(char* fileName, double* result);
char* ProcitajFile(char* file);
int StringUPostfiks(char* buffer, double* rezultat);
int Rezultat(pozicija head, double* rezultat);
pozicija StvoriElement(double broj);
int UmetniNakon(pozicija head, pozicija element);
int Print(pozicija prvi);
int Pop(pozicija head, double* rezultat);
int PopIOperacija(pozicija head, char operacija, double* rezultat);


int main(){
	double result = 0;

    IzracunajPostfiks("postfiks.txt", &result);
	printf("Rezultat: %lf\n", result);

	return EXIT_SUCCESS;
}

int IzracunajPostfiks(char* file, double* rezultat){
    char* buffer = NULL;
    int status = 0;

    buffer = ProcitajFile(file);
    if (buffer == NULL){
        return -1;
    }
    status = StringUPostfiks(buffer, rezultat);
    if (status != EXIT_SUCCESS){
        return -1;
    }

    return 0;
}

char* ProcitajFile(char* datoteka){
    FILE* file = NULL;
    int duljina = 0;
    char* buffer = NULL;

    file = fopen(datoteka, "rb");
    if (!file){
        perror("Can't open file!\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    duljina = ftell(file);

    buffer = (char*)calloc(duljina + 1, sizeof(char));
    if (!buffer){
        perror("\nMemorija nije alocirana.");
        return NULL;
    }

    rewind(file);
    fread(buffer, sizeof(char), duljina, file);
    printf("|%s|\n", buffer);
    fclose(file);

    return buffer;
}

int StringUPostfiks(char* buffer, double* rezultat)
{
    stog head = { .broj = 0, .next = NULL };
    char* currentBuffer = buffer;
    char operacija = 0;
    double number = 0.0;
    int status = 0, BrojBajtova = 0;
    pozicija element = NULL;

    while (strlen(currentBuffer) > 0){
        status = sscanf(currentBuffer, " %lf %n", &number, &BrojBajtova);
        if (status != 1){
            sscanf(currentBuffer, " %c %n", &operacija, &BrojBajtova);
            status = PopIOperacija(&head, operacija, rezultat);

            if (status != EXIT_SUCCESS) {
                return -1;
            }

            number = *rezultat;
        }

        element = StvoriElement(number);
        if (!element){
            return -1;
        }

        currentBuffer += BrojBajtova;
        printf("|%s| =>", currentBuffer);

        UmetniNakon(&head, element); //push na pocetak stack-a
    }

    return Rezultat(&head, rezultat);
}

int Rezultat(pozicija head, double* rezultat){
    int status = 0;

    status = Pop(head, rezultat);

    if (status != 0) {
        return status;
    }
    if (head->next) {
        printf("\nNije dobar postfiks.");
        return -1;
    }

    return 0;
}

pozicija StvoriElement(double broj){
    pozicija element = NULL;

    element = (pozicija)malloc(sizeof(stog));
    if (!element){
        perror("\nMemorija nije alocirana.");
        return element; //NULL
    }

    element->broj = broj;
    element->next = NULL;

    return element;
}

int UmetniNakon(pozicija head, pozicija element){
    element->next = head->next;
    head->next = element;

    Print(head->next);

    return 0;
}

int Print(pozicija first)
{
    pozicija temp = first;

    while (temp)
    {
        printf(" %lf", temp->broj);
        temp = temp->next;
    }
    printf("\n");

    return 0;
}

int Pop(pozicija head, double* rezultat){
    pozicija izbrisi = NULL;

    izbrisi = head->next;
    if (!izbrisi){
        perror("\nStog je prazan.");
        return -1;
    }

    head->next = izbrisi->next;
    *rezultat = izbrisi->broj;
    free(izbrisi);

    return 0;
}

int PopIOperacija(pozicija head, char operacija, double* rezultat){
    double operand1 = 0;
    double operand2 = 0;
    int status1 = 0;
    int status2 = 0;

    status1 = Pop(head, &operand1);
    if (status1 != 0) {
        return -1;
    }

    status2 = Pop(head, &operand2);
    if (status2 != 0) {
        return -1;
    }

    switch (operacija)
    {
    case '+':
        *rezultat = operand2 + operand1;
        break;
    case '-':
        *rezultat = operand2 - operand1;
        break;
    case '*':
        *rezultat = operand2 * operand1;
        break;
    case '/':
        *rezultat = operand2 / operand1;
        break;
    default:
        printf("\nOva operacija nije jos u sustavu.", operacija);
        return EXIT_FAILURE;
    }

    return 0;
}
