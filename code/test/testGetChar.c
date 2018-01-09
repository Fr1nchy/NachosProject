#include "syscall.h"

void print(char c, int n)
{
	int i;
	for (i = 0; i < n; i++) {
	PutChar(c+i);
	}

	PutChar('\n');
}

int main()
{
	print(GetChar(), 3);
	Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
