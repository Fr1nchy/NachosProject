#include "syscall.h"

void characterInterleaved(void *arg) {
  char c = *(char*) arg;
  PutChar('T');
  PutChar(c);
  PutChar('\n');
  UserThreadExit();
}

void characterInterleaved2(void *arg) {
  char c = *(char*) arg;
  PutChar('K');
  PutChar(c);
  PutChar('\n');
  UserThreadExit();
}

int main(){
  char c1 = 'c';
  char c2 = 'z';
  UserThreadCreate(characterInterleaved, (void *) &c1);
  UserThreadCreate(characterInterleaved2, (void *) &c2);
  Halt();
  return 0;
}
