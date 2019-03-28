Autor: Alejandro Miguel Sánchez Mora
ID: A01272385

Funciones implemnentadas en el DLL:

	int asciiBinaryToInt(char *s)	//Convierte un número en binario (leído en string) a entero
	int asciiHEXToInt(char *s)	//Convierte un número en hexadecimal (leído en string) a entrero
	double asciiToDouble(char *)	//Convierte un número con punto decimal (leído en string) a double

Se recomienda usar LoadLibrary para usar la librería.

La estructura que se recomienda declarar para usar asciiBinaryToInt y asciiHEXToInt es:
	typedef int (CONVERT_TO_INT)(char *);

La estructura que se recomienda declarar para usar para asciiToDouble es:
	typedef double (CONVERT_TO_DOUBLE)(char *);

Se incluye código fuente de la librería, un código fuente con un ejemplo de implementación (.exe) y el código fuente 
de la implememntación.

Para usar la librería, los archivos .dll y .lib tienen que estar en la carpeta donde se encuentra el ejecutable
o si se encuentra en otra carpeta, se tiene que poner la dirección al momento de abrir la librería en el código
de implementación.
