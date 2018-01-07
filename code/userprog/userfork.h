#ifndef USERFORK_H
#define USERFORK_H

#include "copyright.h"
#include "system.h"
#include "syscall.h"

extern int do_UserForkCreate (char *filename);
void StartUserFork (int arg);
extern void do_UserForkExit ();

#endif

