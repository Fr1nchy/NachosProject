#include "syscall.h"

/*	--------------------------------------------------------------
**							Test 1
**	Passer un caractère au parametre	
	--------------------------------------------------------------	*/
void test_nominal(char c, int n){
	int i;
	for (i = 0; i < n; i++) {
		PutChar(c+i);
	}

	PutChar('\n');
}


/* 	------------------------------------------------------------
**							Test 2
**	Passer une chaîne de caractères au parametre	
	------------------------------------------------------------*/ 
/*void test_string(char *str){
	PutChar(str);
}*/

/*	-------------------------------------------------------------
** 							Test 3
** Passer un integer au paramètre
	--------------------------------------------------------------*/
void test_int(int n){
	PutChar(n);
}

/*	-------------------------------------------------------------
** 							Test 4
** Passer un caractère non ASCII au paramètre
	--------------------------------------------------------------*/
/*void test_arabe(){
	PutChar('ح');
}*/

/*	-------------------------------------------------------------
** 							Test 5
** Passer un caractère vide au paramètre
	--------------------------------------------------------------*/
/*void test_vide(){
	PutChar('');
}*/



int main()
{
	PutChar('c');
    PutChar('\n');
	//test_nominal('a', 4);

	//test_string("hello");

	//test_int(100);

	//test_arabe();

	//test_vide();
    return 0;
}