#include "syscall.h"


void printChar(void * c) {
    char s = *((char*)c);
    PutChar(s);
    //UserThreadExit();
} 

int main()
{
	char c = 'a';
	int t1 = UserThreadCreate(printChar, &c);
	
	//PutInt(t1);

	 char d = 'b';
	 int t2 = UserThreadCreate(printChar, &d);
	
	//PutChar('p');
	 char e = 'c';
	int t3 = UserThreadCreate(printChar, &e);
	 char f = 'd';
	 int t4 = UserThreadCreate(printChar, &f);
	 char g = 'e';
	 int t5 = UserThreadCreate(printChar, &g);
	 char h = 'f';
	 int t6 = UserThreadCreate(printChar, &h);
	 char i = 'g';
	 int t7 = UserThreadCreate(printChar, &i);
	 char j = 'h';
	 int t8 = UserThreadCreate(printChar, &j);
	 char k = 'i';
	 int t9 = UserThreadCreate(printChar, &k);
	 char l = 'j';
	 int t10 = UserThreadCreate(printChar, &l);
	 char m = 'k';
	 int t11 = UserThreadCreate(printChar, &m);
	 char n = 'l';
	 int t12 = UserThreadCreate(printChar, &n);
	 char o = 'm';
	 int t13 = UserThreadCreate(printChar, &o);
	 char p = 'n';
	 int t14 = UserThreadCreate(printChar, &p);
	 char q = 'o';
	 int t15 = UserThreadCreate(printChar, &q);
	 char r = 'p';
	 int t16 = UserThreadCreate(printChar, &r);
	// char s = 'q';
	// int t17 = UserThreadCreate(printChar, &s);
	// char t = 'r';
	// int t18 = UserThreadCreate(printChar, &t);
	//PutInt(t3);
	//PutChar('t');


	UserThreadJoin(t1);
	PutString("\nJoined t1 ");

	 UserThreadJoin(t2);
	 PutString("Joined t2 ");
	 UserThreadJoin(t3);
	 PutString("Joined t3 ");
     UserThreadJoin(t4);	
	 PutString("Joined t4 ");
	 UserThreadJoin(t5);
	 PutString("Joined t5 ");
     UserThreadJoin(t6);
	 PutString("Joined t6 ");	
	 UserThreadJoin(t7);
	 PutString("Joined t7 ");	
	 UserThreadJoin(t8);
	 PutString("Joined t8 ");	
	 UserThreadJoin(t9);	
	 PutString("Joined t9 ");
	 UserThreadJoin(t10);
	 PutString("Joined t10 ");
	 UserThreadJoin(t11);
	 PutString("Joined t11 ");
	 UserThreadJoin(t12);
	 PutString("Joined t12 ");
	 UserThreadJoin(t13);
	 PutString("Joined t13 ");
	 UserThreadJoin(t14);
	 PutString("Joined t14 ");
	 UserThreadJoin(t15);
	 PutString("Joined t15 ");
	 UserThreadJoin(t16);
	 PutString("Joined t16 ");
	// Max number of threads reached ! 
	// When one thread more, memory overwriting
	// When two threads more, no termination
	// UserThreadJoin(t17);
	// PutString("Joined t17 ");
	// UserThreadJoin(t18);
	// PutString("Joined t18 ");

    Halt();
	return 0;
}

