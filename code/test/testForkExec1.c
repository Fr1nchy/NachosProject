#include "syscall.h"
int main(){
    //PutString("testmake\n");
    ForkExec("./makethreads");
    //PutString("testint\n");
    ForkExec("./testGetChar");
    //PutString("Fin test\n");
   // Halt();
    return 0;
}
