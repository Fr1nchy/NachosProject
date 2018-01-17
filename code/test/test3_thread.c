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
	PutString("test3_thread t n°1\n");
	/*PutInt(t1);
	PutString(" \n");*/
    int j = 10;
    int t2 = UserThreadCreate(printChar, &j);
	PutString("test3_thread t n°2\n");
	/*PutInt(t2);
	PutString(" \n");*/

    UserThreadJoin(t1);
    UserThreadJoin(t2);
//	Halt();
	return 0;
}

//Test:
//Vérification :
// - création plusieurs threads 
// - Passage de parametre 
// - Ecriture en parallele
// - Gestion pile


