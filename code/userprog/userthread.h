#include "copyright.h"
#include "system.h"
#include "console.h"
#include "addrspace.h"
#include "synch.h"
#include "synchconsole.h"
#include "machine.h"
#include "syscall.h"


extern int do_UserThreadCreate(int f, int arg, int fin);

extern int do_UserThreadExit();

extern void join_UserThread(int id);

class Parametre {
    public:
        int f;
        int arg;
        int fin;
};


