#include "syscall.h"

void printChar(void * c) {
    int g = 56;
    PutInt(g);    
    int s = *((int*)c);
    PutChar('c');
	PutInt(s);
    PutChar('\n');
	UserThreadExit();
} 

int main()
{
	int i = 5;
	UserThreadCreate(printChar, &i);
    i = 10;
    UserThreadCreate(printChar, &i);
	Halt();
}
