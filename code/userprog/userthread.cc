#include "userthread.h"
#include "machine.h"
#include "syscall.h"

static void StartUserThread(int f) {
    Parametre p = *((Parametre*)f);
    
    currentThread->space->InitRegisters ();
    currentThread->space->RestoreState ();

    machine->WriteRegister(PrevPCReg,machine->ReadRegister(PCReg));
    machine->WriteRegister(PCReg,p.f);
    machine->WriteRegister(NextPCReg,p.f+4);
    machine->WriteRegister(4,p.arg);
    
	machine->WriteRegister(StackReg, machine->ReadRegister(PCReg)-PageSize*3);
    
	machine->Run();
}

int do_UserThreadCreate(int f, int arg) {
    Thread* newThread = new Thread("User thread");
    Parametre * p = new Parametre();
    p->f = f;
    p->arg = arg;
    newThread->Fork(StartUserThread, (int)p);
    delete p;
	return 0;
}    

int do_UserThreadExit() {
	currentThread->Finish();
	return 0;
}
