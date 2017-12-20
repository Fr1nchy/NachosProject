#include "syscall.h"

void prints(const char *s){
	PutString(s);
}
int main()
{
	prints("hello");
	//prints("hello\n");
	//prints("this is EOF \0 this line should not be read\n");
	Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
