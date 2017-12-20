#include "userthread.h"
#include "machine.h"
#include "syscall.h"
#include "synch.h"
#include "system.h"

static Semaphore* s;

static void StartUserThread(int f) {  

    Parametre p = *((Parametre*)f);

    
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
    s = new Semaphore("User thread finished", 0);
    Thread* newThread = new Thread("User thread");
    Parametre * p = new Parametre();

    semaNumThreads->P();
    newThread->setId_t(idThread);
    numberThreads = numberThreads +1;
    idThread = idThread +1;
    semaNumThreads->V();
 
    p->f = f;
    p->arg = arg;

    newThread->Fork(StartUserThread, (int)p);
    s->P();

      
    return newThread->getId_t();
}    

int do_UserThreadExit() {
    s->V();
    semaNumThreads->P();
    numberThreads = numberThreads -1;
    semaNumThreads->V();
	currentThread->Finish();
	return 0;
}

void join_UserThread(int id){
}


