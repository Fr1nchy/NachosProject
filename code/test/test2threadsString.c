#include "syscall.h"

void printChar(void * c) {
   // char s = *((char*)c);
    PutString("111111111111111111111111111\n");
    UserThreadExit();
} 

int main()
{
	char c;


	int t1 = UserThreadCreate(printChar, &c);
	int t2 = UserThreadCreate(printChar, &c);
	int t3 = UserThreadCreate(printChar, &c);
	int t4 = UserThreadCreate(printChar, &c);
	

	UserThreadJoin(t1);
	UserThreadJoin(t2);
	UserThreadJoin(t3);
	UserThreadJoin(t4);
	
	return 0;
}

