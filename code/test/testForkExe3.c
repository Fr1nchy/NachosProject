#include "syscall.h"
int main(){
    PutString("Test:");
    
    ForkExec("./test2threadsString");
    ForkExec("./test2threadsString");
    return 0;
}
