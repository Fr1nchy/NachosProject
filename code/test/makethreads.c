#include "syscall.h"

void printChar(void * c) {
    char s = *((char*)c);
	PutChar(s);
	UserThreadExit();
} 

int main()
{
	char c = 't';
	int res = UserThreadCreate(printChar, &c);
    PutInt(res);
	Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
