#include "syscall.h"
int main(){
    PutString("Test:");
    
    ForkExec("./test2threadsString");
    ForkExec("./test3threadsString");
    return 0;
}
