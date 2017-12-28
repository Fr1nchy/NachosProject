#include "syscall.h"

void printChar(void * c) {
    int g = 44;
    int s = *((int*)c);

    PutInt(g);   
    PutChar('_');
	PutInt(s);
    PutChar('\n');
	UserThreadExit();
} 

int main()
{
    int i = 5;
    int t1 = UserThreadCreate(printChar, &i);
    int j = 10;
    int t2 = UserThreadCreate(printChar, &j);

    PutString("wait main\n");

    UserThreadJoin(t1);
    UserThreadJoin(t2);
    PutString("Fin prog\n");
	Halt();
}

//Test:
//Vérification :
// - création plusieurs threads 
// - Passage de parametre 
// - Ecriture en parallele
// - Gestion pile


