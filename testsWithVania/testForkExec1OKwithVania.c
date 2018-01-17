#include "syscall.h"
int main(){
    //Put("testmake\n");
    PutString("1111111111111111111");
    ForkExec("./makethreads");
    //ForkExec("./testGetInt");
    //ForkExec("./testGetInt");
    //PutString("2222222222222222222222");
    //PutChar('o');
    ForkExec("./makethreads");
    //PutString("testint\n");
    //ForkExec("./testGetInt");
    //PutString("Fin test\n");
   // Halt();
    return 0;
}
