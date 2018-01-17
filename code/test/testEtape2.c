#include "syscall.h"
//#include "testEtape2.h"
//#include "stdio.h"

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

void test_nominal(char c, int n){
	int i;
	for (i = 0; i < n; i++) {
		PutChar(c+i);
	}

	PutChar('\n');
}

int main(){
	PutString("Ceci est une chaîne de caractères écrite par PutString()\n");
	PutString("Elle effectue plusieurs PutChar()...\n");
	PutString("Cette fonction servira à écrire les retours des différents " 
				"tests.\n");

	PutString("Pour tester PutChar(), une boucle va afficher plusieurs "
			 "caractères à la suite.\n");
	PutString("Test PutChar() : ");	
	test_nominal('a', 6);
	PutChar('\n');

	PutString("Maintenant, nous allons tester la fonction PutInt() en "
		 "essayant d'abord d'afficher l'entier 150, "
		 "puis le nombre décimal 45.67\n");
	PutInt(150);
	PutChar('\n');
	PutInt(45.67);
	PutChar('\n');
	PutString("Il est maintenant temps de tester les fonctions permettant de "
				" récupérer des valeurs via la console\n");
	PutString("Commencez par essayer de rentrer un caractère afin de tester "
				"GetChar() : ");
	char bufferCh;
	char bufferStr[6];
	bufferCh = GetChar();
	PutChar('\n');

	PutString("Vous avez entré le caractère : ");
	PutChar(bufferCh);
	PutChar('\n');

	PutString("Et maintenant entrez une chaîne de 5 caractères afin de "
				"tester GetString() : ");
	GetString(bufferStr, 6);
	PutChar('\n');

	PutString("Vous avez écrit : ");
	PutString(bufferStr);
	PutChar('\n');

	PutString("Pour finir, il faut tester GetInt(). Veuillez entrer "
				" un entier : ");
	int n;
	GetInt(&n);

	PutString("Vous avez entré : ");
	PutInt(n);
	PutChar('\n');

	//Écriture de plusieurs caractères en dépassant MAX_STRING_SIZE
	//ATTENTION LA VALEUR EST À CHANGER MANUELLEMENT
	writeSomeChars();
	PutChar('\n');
    return 0;
}

/*Partie 6: return 0 ; puis  recupération erreur pour traiter
Ajouter un case dans execpt 
*/ 
