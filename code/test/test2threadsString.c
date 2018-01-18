#include "syscall.h"

void printChar(void * c) {
   // char s = *((char*)c);
    PutString("111111111111111111111111111\n");
} 

int main()
{
	char c;
	int t1 = UserThreadCreate(printChar, &c);
	UserThreadJoin(t1);
	return 0;
}

