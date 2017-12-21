#include "syscall.h"

void print(int n){
	int i;
	for (i = 0; i < n; i++) {
        PutChar('i');
        PutChar(':');
	    PutInt(i);
        PutChar('\n');
	}
}
int main()
{
	int n ;
    PutInt(256);
    PutChar('\n');
    GetInt(&n);
    PutChar('\n');
	print(n);
	Halt();
}
