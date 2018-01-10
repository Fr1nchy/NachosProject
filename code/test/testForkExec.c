#include "syscall.h"
int main(){
    PutString("testchar\n");
    ForkExec("./getchar");
    PutString("testint\n");
    ForkExec("./getint");
    PutString("Fin test\n");
   // Halt();
    return 0;
}
