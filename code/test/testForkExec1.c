#include "syscall.h"
int main(){
    PutString("testmake\n");

    ForkExec("./makethreads");
    //PutString("testint\n");
    //ForkExec("./getint");
    PutString("Fin test\n");
   // Halt();
    return 0;
}
