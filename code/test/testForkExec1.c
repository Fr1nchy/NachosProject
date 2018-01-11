#include "syscall.h"
int main(){
    PutString("testmake\n");
//PutString("testint\n");
    ForkExec("./makethreads");
    //PutString("testint\n");
    ForkExec("./testGetInt");
    PutString("Fin test\n");
   // Halt();
    return 0;
}
