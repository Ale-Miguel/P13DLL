// P8DLLA01272385.cpp : Define las funciones exportadas de la aplicación DLL.
//
/*
Nombre: Alejandro Miguel Sánchez Mora
Matrícula: A01272385

Descripción:
DLL de la práctica 8
Design the source code for the following routines:

int asciiBinaryToInt(char *s): 	This routine returns an integer, corresponding to the input string,
								that codifies a binary number; consider that the string internal
								characters are just '0' and '1', with a maximum length of 32. Also,
								consider that the conversion should be finished reaching a null or
								any invalid characer.

int asciiHEXToInt(char *s): 	This routine returns an integer, corresponding to an equivalent decimal
								number converted from a hexadecimal, represented in sequence of characters
								in the input string; consider that the only alowed characters are from '0'
								to '9', from 'A' to 'F' and from 'a' to 'f', with a maximum string length
								of 8 characters .. any invalid character will finish the conversion process,
								so the acumulated result will be returned.

double asciiToDouble(char *s): 	This routine returns a double precision float number, corresponding to an
								sequence of digit characters in the input string, with the optional single
								appearance of the sign ('+' or '-') and decimal point ('.') to commit with
								a valid representation for a real number, with integers and decimals; any
								invalid character will finish the conversion process, so the acumulated result
								will be returned.


*/

#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <string.h>

#define MAX_NUMBER_LENGTH 32 //Constante para definir la cantidad máxima de dígitos que se van a admitir

double getDigit(char *s);		//Función auxiliar que regresa el número que representa el dígito que se le pasa de parámetro

//Función que comvierte un número en binario a base 10
extern "C" __declspec(dllexport) int asciiBinaryToInt(char *s) {

	int iResultado = 0;	//Variable que guarda el número que se genera al convertir de base 2 a base 10
	int iDos = 1;		//Variable que guarda las potencias de 2 (empieza en 2 ^0 = 1)

	char *aux;			//Apuntador auxiliar que va a hacer el recorrido del arreglo

	//Con aritmética de apuntadores se lleva a aux a que apunte al último dígito del número, ya que se empieza a convertir desde 
	//el número menos significativo (el que tiene la potencia 2 ^ 0)
	aux = s;

	aux += strlen(s) - 1;	//Se resta 1 porque apuntraría al '\0'

	//Ciclo que itera sobre el string de reversa para convertir del dígito menos significativo al más significativo
	for (int i = 0; i < strlen(s); i++) {

		//Si el dígito es 1, se le suma la potencia de 2 que corresponda a su posición
		if (*aux == '1') {
			iResultado += iDos;
		}
		//Si el dígito no es 1, entonces tendría que ser 0, sin embargo, no puede ser otro número o caracter, por lo que si no es 0
		//se termina la función con el número calculado hasta antes de la posición de ese caractert
		else if (*aux != '0') {
			printf("ERROR: El digito %c no ha sido reconocido\n", *aux);
			return iResultado;
		}

		iDos *= 2;	//Se calcula la nueva potencia de 2
		aux--;		//Se recorre una posición el apuntador
	}

	//Se regresa el resultado final
	return iResultado;
}

//Función que convierte un número hexadecimal a base 10
extern "C" __declspec(dllexport) int asciiHEXToInt(char *s) {

	int iDieciseis = 1;	//Variable que guarda la potencia de 16 (se inicializa en 16 ^0 = 1)
	int iResultado = 0;	//Varialble que guarda el resultado de la conversión de hexadecimal a base 10
	int iDigito = 0;	//Variable que guarda el valor del dígito que el apuntador está apuntado

	char *aux;	//Apuntador auxiliar que va a hacer el recorrido del arreglo

	//Con aritmética de apuntadores se lleva a aux a que apunte al último dígito del número, ya que se empieza a convertir desde 
	//el número menos significativo (el que tiene la potencia 16 ^ 0)

	aux = s;

	aux += strlen(s) - 1;	//Se resta 1 porque apuntraría al '\0'

	//Si el tamaño del string es más grande que el permitido, regresa -1 que significa error
	if (strlen(s) > MAX_NUMBER_LENGTH) {
		return -1;
	}

	//Ciclo que itera sobre el string de reversa para convertir del dígito menos significativo al más significativo
	for (int i = 0; i < strlen(s); i++) {

		//Se obtiene el número que significa el caracter
		iDigito = (int)getDigit(aux);

		//Si la función regresó un valor menor a 0 significa que no reconoció el dígito, por lo que se termina la función regresando
		//el valor calculado hasta antes de ese dígito
		if (iDigito < 0) {

			return iResultado;

		}

		//Se le suma el valor correspondiente a la posición del digito en el número en hexadecimal
		iResultado += (iDieciseis * iDigito);

		iDieciseis *= 16;	//Se calcula la nueva potencia de 16
		aux--;	//Se recorre el apuntador una posición
	}

	//Se regresa el número convertido a base 10
	return iResultado;

}

//Función que convierte un número con punto decimal que se pasa como string a un double
extern "C" __declspec(dllexport) double asciiToDouble(char *s) {

	double dResultado = 0;	//Variable que guarda el número convertido a double
	double dDigito = 0;		//Variable que guarda el valor del dígito que el apuntador está apuntado
	double dDiez = 1;		//Variable que guarda la potencia de 10

	char * cPunto = NULL;	//Apuntador que apunta a donde esté el punto decimal, se inicializa en NULL ya que puede o no estar el punto
	char * cSigno = NULL;	//Apuntador que apunta a donde está el signo del número, se inicializa en NULL ya que puede o no estar el punto
	char * aux;				//Apuntador auxiliar que va a recorrer el string

	int iDistanciaEntera;	//Variable que guarda la distancia de digitos que hay entre el primer digito y el último de la parte entera


	//Si hay un signo, debe de estar en la primera posición del string
	if (*s == '+' || *s == '-') {
		//Se asigna el apuntador del signo al signo
		cSigno = s;
		s++;	//Se recorre el apuntador para apuntar al número sin signo
	}

	aux = s;

	//Se busca el punto decimal en el string
	while (*aux != '\0') {

		if (*aux == '.') {
			//Cuando encuetra el punto termina el ciclo
			cPunto = aux;
			break;
		}

		aux++;
	}

	aux--;	//Se recorre una posición el apuntador ya que al terminar el ciclo o apunta a \0 o al punto y solo se necesita que apunte al dígito 


	iDistanciaEntera = aux - s; //Se calcula la distancia en posiciones del último digito - posición del primer dígito

	//Ciclo que calcula la parte entera del número 
	for (int i = 0; i <= iDistanciaEntera; i++) {

		dDigito = getDigit(aux); //Se obtiene el valor del dígito

		//Si la función regresa un valor menor que 0, significa que se ingresó un caracter o no válido
		//por lo que se regresa el número calculado hasta antes de ese caracter
		if (dDigito < 0) {

			return dResultado;
		}

		//Se le suma el valor correspondiente a la posición del digito en el número
		dResultado += (dDigito  * dDiez);

		dDiez *= 10; //Se calcula la siguiente potencia de 10
		aux--;	//Se recorre el apuntador una posición

	}

	//Si el número tiene punto decimal
	if (cPunto) {

		//El apuntador aux va a apuntar al primer número que esté después del punto decimal
		aux = cPunto + 1;

		dDiez = 10;	//Se le asigna la potencia de 10 10 ya que el primer digito tiene el valor de  1/10

		//Ciclo que itera sobre el string para calcular los valores de los decimales
		while (*aux != '\0') {

			dDigito = getDigit(aux);	//Se obtiene el valor del dígito

			//Si la función regresa un valor menor que 0, significa que se ingresó un caracter o no válido
			//por lo que se regresa el número calculado hasta antes de ese caracter
			if (dDigito == -1) {
				return dResultado;
			}

			//Se le suma el valor correspondiente a la posición del digito en el número
			dResultado += (dDigito * (1 / dDiez));

			dDiez *= 10;	//Se calcula la siguiente potencia de 10
			aux++;			//El apuntador avanza una posición
		}
	}

	//Si el número tiene signo y ese signo es negativo, se va a multiplicar el número por -1 para volver negativo el número
	if (cSigno && *cSigno == '-') {

		dResultado *= -1;

	}

	return dResultado;	//Se regresa el número resultante

}

//Función auxiliar que regresa el número que representa el dígito que se le pasa de parámetro
double getDigit(char *s) {

	double dDigito = 0;	//Variable que almacena el dígito en formato double

	if (*s == '0') {
		dDigito = 0;
	}
	else if (*s == '1') {
		dDigito = 1;
	}
	else if (*s == '2') {
		dDigito = 2;
	}
	else if (*s == '3') {
		dDigito = 3;
	}
	else if (*s == '4') {
		dDigito = 4;
	}
	else if (*s == '5') {
		dDigito = 5;
	}
	else if (*s == '6') {
		dDigito = 6;
	}
	else if (*s == '7') {
		dDigito = 7;
	}
	else if (*s == '8') {
		dDigito = 8;
	}
	else if (*s == '9') {
		dDigito = 9;
	}
	else if (*s == 'A' || *s == 'a') {
		dDigito = 10;
	}
	else if (*s == 'B' || *s == 'b') {
		dDigito = 11;
	}
	else if (*s == 'C' || *s == 'c') {
		dDigito = 12;
	}
	else if (*s == 'D' || *s == 'd') {
		dDigito = 13;
	}
	else if (*s == 'E' || *s == 'e') {
		dDigito = 14;
	}
	else if (*s == 'F' || *s == 'f') {
		dDigito = 15;
	}
	else {
		printf("ERROR: El digito %c no ha sido reconocido\n", *s);
		dDigito = -1;	//Si el caracter que se pasó de parámetro no es un dígito, se regresa un -1 en señal de error
	}

	return dDigito;	//Se regresa el dígito correspondiente al caracter pasado de argumento de la función
}




