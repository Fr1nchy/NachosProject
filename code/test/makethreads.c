#include "syscall.h"

void printChar(char c) {
	PutChar('a');
} 

int main()
{
	char c = 'a';
	UserThreadCreate(printChar, &c);
	Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
