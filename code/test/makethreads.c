#include "syscall.h"

void printChar(void * c) {
    char s = *((char*)c);
	PutChar(s);
	UserThreadExit();
} 

int main()
{
	char c = '0';
	int t1 = UserThreadCreate(printChar, &c);
	char d = '1';
	int t2 = UserThreadCreate(printChar, &d);
	char e = '2';
	int t3 = UserThreadCreate(printChar, &e);
	char f = '3';
	int t4 = UserThreadCreate(printChar, &f);
	char g = '4';
	int t5 = UserThreadCreate(printChar, &g);
	char h = '5';
	int t6 = UserThreadCreate(printChar, &h);

	UserThreadJoin(t1);
	UserThreadJoin(t2);
	UserThreadJoin(t3);
	UserThreadJoin(t4);
	UserThreadJoin(t5);
	UserThreadJoin(t6);
    Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
