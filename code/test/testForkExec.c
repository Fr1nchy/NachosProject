#include "syscall.h"
int main(){
    //PutString("testchar\n");
    ForkExec("./testGetChar");
    //PutString("testint\n");
    ForkExec("./testGetInt");
    //PutString("Fin test\n");
   // Halt();
    return 0;
}
