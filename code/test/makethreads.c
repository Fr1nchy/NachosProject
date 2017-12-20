#include "syscall.h"

void printChar(void * c) {
    char s = *((char*)c);
	PutChar(s);
	UserThreadExit();
} 

int main()
{
	char c = 't';
	UserThreadCreate(printChar, &c);
	c = 'a';
	UserThreadCreate(printChar, &c);
    Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
