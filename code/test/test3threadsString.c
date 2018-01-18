#include "syscall.h"

void printChar(void * c) {
    int n =0;
    GetInt(&n);
    PutInt(n);
    PutString("\nFin\n");
} 

int main()
{
	char c;
    int n;
    PutString("\nEntier:\n");
    GetInt(&n);
    //
	int t1 = UserThreadCreate(printChar, &c);
    int t2 = UserThreadCreate(printChar, &c);
	UserThreadJoin(t1);
    UserThreadJoin(t2);
	return 0;
}

