#include "syscall.h"

void print(char c, int n)
{
	int i;
	for (i = 0; i < n; i++) {
	PutChar(c+i);
	}

	PutChar('\n');
}

void prints(const char *s){
	PutString(s);
}
int main()
{
	//print(GetChar(), 3);
	int n = 10;
	char str[n+1];
	GetString(str, n);
	prints(str); //Test getString
	Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
