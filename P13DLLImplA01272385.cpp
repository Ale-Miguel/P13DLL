// A simple program that uses LoadLibrary and 
// GetProcAddress to access functions from P8DLLA01272385.dll. 

#include "pch.h"
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define _CRT_SECURE_NO_WARNINGS	//Constante para que VS no marque error en el scanf

#define MAX_NUMBER_LENGTH 32

HINSTANCE hCodigoDll;

long l1;
long l2;
long lResult;
char sNumeroIngresado[MAX_NUMBER_LENGTH];
int iResult;
double dResult;

typedef int (CONVERT_TO_INT)(char *);
typedef double (CONVERT_TO_DOUBLE)(char *);

CONVERT_TO_INT* ptrFuncBinaryToInt = NULL;
CONVERT_TO_INT* ptrFuncAsciiHEXToInt = NULL;
CONVERT_TO_DOUBLE* ptrFuncAsciiToDouble = NULL;

void main() {
	//Explicit inclusion: Upload the DLL from disk to memory
	if (hCodigoDll = LoadLibrary(TEXT("P8DLLA01272385.dll"))) {
		ptrFuncBinaryToInt = (CONVERT_TO_INT *)GetProcAddress(hCodigoDll, "asciiBinaryToInt");
		ptrFuncAsciiHEXToInt = (CONVERT_TO_INT *)GetProcAddress(hCodigoDll, "asciiHEXToInt");
		ptrFuncAsciiToDouble = (CONVERT_TO_DOUBLE *)GetProcAddress(hCodigoDll, "asciiToDouble");
		if (ptrFuncBinaryToInt && ptrFuncAsciiHEXToInt && ptrFuncAsciiToDouble) {

			//Se le pide al usuario ingresar un número en binario
			printf("Ingrese un numero en binario para convertirlo a base 10: ");
			scanf_s("%s", &sNumeroIngresado, sizeof(sNumeroIngresado));

			iResult = (*ptrFuncBinaryToInt)(sNumeroIngresado);

			printf("El numero %s en base 10 es: %d\n", sNumeroIngresado, iResult);	//Se imprime el resultado de la conversión

			//Se le pide al usuario ingresar un número en hexadecimal
			printf("Ingrese un numero en hexadecimal para convertirlo a base 10: ");
			scanf_s("%s", sNumeroIngresado, sizeof(sNumeroIngresado));

			iResult = (*ptrFuncAsciiHEXToInt)(sNumeroIngresado);
			printf("El numero %s en base 10 es: %d\n", sNumeroIngresado, iResult);	//Se imprime el resultado de la conversión

			//Se le pide al usuario ingresar un número decimal
			printf("Ingrese un numero decimal para convertirlo a variable double: ");
			scanf_s("%s", sNumeroIngresado, sizeof(sNumeroIngresado));

			dResult = (*ptrFuncAsciiToDouble)(sNumeroIngresado);
			printf("El numero en variable double es: %lf\n", dResult);	//Se imprime el resultado de la conversión

		}
		else
			printf("ERROR: Routine not found!\n");
	}
	else
		printf("ERROR: Library not found!\n");
	FreeLibrary(hCodigoDll);

	getchar();
}
