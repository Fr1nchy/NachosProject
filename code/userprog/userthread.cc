#include "userthread.h"
#include "machine.h"
#include "syscall.h"
#include "synch.h"
#include "system.h"

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
    Thread* newThread = new Thread("User thread");
    Parametre * p = new Parametre();

    semaNumThreads->P();
    newThread->setId_t(numberThreads);
    numberThreads = numberThreads +1;
    semaNumThreads->V();
 
    p->f = f;
    p->arg = arg;

    newThread->Fork(StartUserThread, (int)p);
      
	  return newThread->getId_t();
}    

int do_UserThreadExit() {
	currentThread->Finish();
	return 0;
}

void join_UserThread(int id){
  
  
}


