#include "syscall.h"

void characterInterleaved(void *arg) {
  PutChar('T');

  PutChar(*(char *) arg);
  //PutChar('E');

  //PutChar('\n');
  UserThreadExit();
}


int main(){
  char c1 = 'c';
  char c2 = 'z';
  UserThreadCreate(characterInterleaved, (void *) &c1);
  PutInt(4);
  UserThreadCreate(characterInterleaved, (void *) &c2);
  Halt();
  return 0;
}
