#include "userthread.h"
#include "machine.h"
#include "syscall.h"

typedef struct void * (main)();


static void StartUserThread(int f) {
	machine->WriteRegister(StackReg, machine->ReadRegister(PCReg)-PageSize*3);
	main * f1;
	f1 = &f;
	machine->Run();
}

int do_UserThreadCreate(int f, int arg) {
    Thread* newThread = new Thread("User thread");
    //newThread->space->InitRegisters()
    //newThread->space->RestoreState
    newThread->Fork(StartUserThread, f);
	return do_UserThreadExit();
}

int do_UserThreadExit() {
	currentThread->Finish();
	return 0;
}