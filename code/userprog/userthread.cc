#include "userthread.h"
#include "machine.h"
#include "syscall.h"
#include "synch.h"

static Semaphore *userThreadEnded;

static void StartUserThread(int f) {  

    Parametre p = *((Parametre*)f);

    printf("bbb: %d, %d\n",p.f,p.arg);
    currentThread->space->InitRegisters ();
    currentThread->space->RestoreState ();

    machine->WriteRegister(PrevPCReg,machine->ReadRegister(PCReg));
    machine->WriteRegister(PCReg,p.f);
    machine->WriteRegister(NextPCReg,p.f+4);
    machine->WriteRegister(4,p.arg);

    //machine->WriteRegister(StackReg, machine->ReadRegister(PCReg)-PageSize*3);

    machine->Run();
}

int do_UserThreadCreate(int f, int arg) {
    userThreadEnded = new Semaphore("user thread finished", 0);
    Thread* newThread = new Thread("User thread");

    Parametre * p = new Parametre();
    p->f = f;
    p->arg = arg;

    newThread->Fork(StartUserThread, (int)p);
    userThreadEnded->P();
    
	return 0;
}    

int do_UserThreadExit() {
        printf("\nafin\n");
        userThreadEnded->V();
	currentThread->Finish();
        printf("\nbfin\n");

    printf("fin\n");
	return 0;
}
