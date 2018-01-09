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
    char str[TAILLE] = {"012345678"};
    int tab[TAILLE];
    int i;

    for(i = 0 ; i < TAILLE; i++){
        tab[i] = UserThreadCreate(printChar,&str[i]);
    }

    for(i = 0; i < TAILLE; i++){
        UserThreadJoin(tab[i]);
    }
    Halt();
}


