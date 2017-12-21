#include "syscall.h"

int t2;
int t1;

void printChar(void * c) {
    PutChar('\n');
	PutChar(*((char*)c));
    PutChar('\n');
    if(*((char*)c) =='1'){
        UserThreadJoin(t2);
    }

    
	UserThreadExit();
} 

int main()
{
	char c = '1';
	t1 = UserThreadCreate(printChar, &c);
	char d = '2';
	t2 = UserThreadCreate(printChar, &d);

    UserThreadJoin(t1);

    Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
