#include "syscall.h"

int main()
{
	PutString("hello world \nThis is a new line\n");
	char str[900];
	for (int i = 0; i < 900; i++)
	{
		str[i] = '-';
	}
	str[899] = '\n';
	PutString(str);
	Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
