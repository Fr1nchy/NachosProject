#include "syscall.h"

void prints(const char *s){
	PutString(s);
}
int main()
{
	char str[15];
	GetString(str, 15);
	//PutString(str);
	while(str[0] != '\0'){
		PutString(str);
		GetString(str, 15);
	}
	/*
	PutString(str);
	GetString(str, 15);
	PutString(str);
	GetString(str, 15);
	PutChar(str[0]);
	PutString(str);
	//prints("this is EOF \0 this line should not be read\n");*/
	Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 