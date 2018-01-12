#include "syscall.h"

void printChar(void * c) {
    char s = *((char*)c);
    PutChar(s);
    //UserThreadExit();
} 

int main()
{
	char c = '0';
	int t1 = UserThreadCreate(printChar, &c);
	PutChar('0');
	char d = '1';
	int t2 = UserThreadCreate(printChar, &d);
	PutChar('1');
	/*char e = '2';
	int t3 = UserThreadCreate(printChar, &e);
	PutChar('2');
	char f = '3';
	int t4 = UserThreadCreate(printChar, &f);
	PutChar('3');
	char g = '4';
	int t5 = UserThreadCreate(printChar, &g);
	PutChar('4');
	char h = '5';
	int t6 = UserThreadCreate(printChar, &h);
	PutChar('5');*/

	PutChar('a');
	UserThreadJoin(t1);
	PutChar('b');
	UserThreadJoin(t2);
	/*PutChar('c');
	UserThreadJoin(t3);
	PutChar('d');
	UserThreadJoin(t4);
	PutChar('e');
	UserThreadJoin(t5);
	PutChar('f');
	UserThreadJoin(t6);*/
    //Halt();
	return 0;
}

