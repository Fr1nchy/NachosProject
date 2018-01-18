#include "syscall.h"
int main(){
    PutString("Test:");
    ForkExec("./testPutChar");
    PutChar('\n');
    return 0;
}
