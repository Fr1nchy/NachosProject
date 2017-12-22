#include "syscall.h"

void writeSomeChars(){
    char str[1003];
	int i;
    for (i = 0; i < sizeof(str); i++)
    {
            str[i] = '-';
    }
    str[sizeof(str)-1] = '\n';
    PutString(str);
}

int main(){
	//Écriture d'un caractère
	//PutString('c');

	//Écriture d'un int
	//PutString(150);

	//Écriture d'une chaîne de caractères
	PutString("Ceci est un test\n");

	//Écriture d'une chaîne de caractères vide
	PutString("");

	//Écriture d'un caractère non ascii
	PutString("橫\n");

	//Écriture de plusieurs caractères en dépassant MAX_STRING_SIZE
	//ATTENTION LA VALEUR EST À CHANGER MANUELLEMENT
	writeSomeChars();

	Halt();
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
