#include "syscall.h"
int main(){
    ForkExec("./test3_1threads");
    ForkExec("./test3_thread");

   // Halt();
    return 0;
}
