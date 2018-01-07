#include "syscall.h"
int main(){
    ForkExec("./getchar");
    ForkExec("./getint");
    Halt();
    return 0;
}
