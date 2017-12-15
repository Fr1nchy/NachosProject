#include "userthread.h"
#include "machine.h"
#include "syscall.h"

static void StartUserThread(int f) {
    Parametre p = *((Parametre*)f);

	machine->WriteRegister(StackReg, machine->ReadRegister(PCReg)-PageSize*3);
	machine->Run();
}

int do_UserThreadCreate(int f, int arg) {
    
    Thread* newThread = new Thread("User thread");
    Parametre * p = new Parametre();
    p->f = f;
    p->arg = arg;
    newThread->Fork(StartUserThread, (int)p);
	return do_UserThreadExit();
}

int do_UserThreadExit() {
	currentThread->Finish();
	return 0;
}
