#include "syscall.h"

void printChar(void * c) {
    int g = 56;
    PutInt(g);    
    int s = *((int*)c);
	PutInt(s);
	UserThreadExit();
} 

int main()
{
	int i = 5;

	UserThreadCreate(printChar, &i);
	Halt();
}
