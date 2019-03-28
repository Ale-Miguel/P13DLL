Autor: Alejandro Miguel S�nchez Mora
ID: A01272385

Funciones implemnentadas en el DLL:

	int asciiBinaryToInt(char *s)	//Convierte un n�mero en binario (le�do en string) a entero
	int asciiHEXToInt(char *s)	//Convierte un n�mero en hexadecimal (le�do en string) a entrero
	double asciiToDouble(char *)	//Convierte un n�mero con punto decimal (le�do en string) a double

Se recomienda usar LoadLibrary para usar la librer�a.

La estructura que se recomienda declarar para usar asciiBinaryToInt y asciiHEXToInt es:
	typedef int (CONVERT_TO_INT)(char *);

La estructura que se recomienda declarar para usar para asciiToDouble es:
	typedef double (CONVERT_TO_DOUBLE)(char *);

Se incluye c�digo fuente de la librer�a, un c�digo fuente con un ejemplo de implementaci�n (.exe) y el c�digo fuente 
de la implememntaci�n.

Para usar la librer�a, los archivos .dll y .lib tienen que estar en la carpeta donde se encuentra el ejecutable
o si se encuentra en otra carpeta, se tiene que poner la direcci�n al momento de abrir la librer�a en el c�digo
de implementaci�n.
