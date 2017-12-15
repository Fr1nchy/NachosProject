#include "syscall.h"

void printChar() {
	PutChar('a');
} 
int main()
{
	printChar();
	Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
