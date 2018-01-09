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
	int n;
    PutString("ss_getchar\n");
	print(GetChar(), 3);

    PutInt(256);
    PutChar('\n');

    GetInt(&n);
    PutInt(n);
    PutChar('\n');
	//print(n);
	//Halt();
    return 0;
}
