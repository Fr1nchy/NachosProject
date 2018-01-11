#include "syscall.h"

void print(char c, int n)
{
	int i;
	for (i = 0; i < n; i++) {
	PutChar(c+i);
	}

	PutChar('\n');
}

int main()
{
    //PutString("ss_getchar\n");
	print(GetChar(), 3);
	//Halt();
    return 0;
}

