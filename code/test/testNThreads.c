#include "syscall.h"
#define TAILLE 9

void printChar(void * c) {
    char s = *((char*)c);
	PutChar(s);
    PutChar('\n');
	UserThreadExit();
} 

int main()
{
/*    char str[TAILLE] = {"012345678"};
    int tab[TAILLE];*/
    int i;
	PutString("CECI EST UN TEST DE VÉRIFICATION D'EXÉCUTION");

    for(i = 0 ;; i++){
		if(UserThreadCreate(printChar,(char*)i)<0){
/*			PutString("Programme planté au ");
			PutInt(i);
			PutString("ème thread\n");*/
			Halt();
		}
    }

    Halt();
}


