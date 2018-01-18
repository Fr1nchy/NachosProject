#include "syscall.h"
int main(){
    PutString("Test:");
    ForkExec("./makethreads");
    return 0;
}
