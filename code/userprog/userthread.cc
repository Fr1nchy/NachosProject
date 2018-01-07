#include "userthread.h"
#include "machine.h"
#include "syscall.h"
#include "synch.h"
#include "system.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static void StartUserThread(int f) {  
    Parametre p = *((Parametre*)f);

    currentThread->space->InitRegisters ();
    currentThread->space->RestoreState ();
    
    machine->WriteRegister(PrevPCReg,machine->ReadRegister(PCReg));
    machine->WriteRegister(PCReg,p.f);
    machine->WriteRegister(NextPCReg,p.f+4);
    machine->WriteRegister(4,p.arg);

    machine->WriteRegister(StackReg,currentThread->space->ThreadSpace());
    //printf("stack:%d\n",machine->ReadRegister(StackReg));
    
    if(machine->ReadRegister(StackReg) == -1) {
    	do_UserThreadExit();
    }else {
    	machine->Run();
    }
}

int do_UserThreadCreate(int f, int arg) {
    Thread* newThread = new Thread("User thread");
    Parametre * p = new Parametre();
    p->f = f;
    p->arg = arg;
  
    int bid = currentThread->space->incrementIdNbThread();
    int tid = currentThread->space->getIdThread();
    if(bid!=-1){
    	p->f = f;
    	p->arg = arg;
	newThread->setBid(bid);
	newThread->setTid(tid);
    	newThread->Fork(StartUserThread, (int)p);
    }
    return bid;
}    

int do_UserThreadExit() {
    //printf("fin:%d\n",currentThread->getBid());
    if(currentThread->getBid()!=-1){
	    semJoinThreads[currentThread->getBid()]->V();
	    currentThread->Finish();
	    currentThread->space->decrementNbThreadResetSpace();
    }else{
    	interrupt->Halt();
    }
    
    return 0;
}

void join_UserThread(int bid){
	semJoinThreads[bid]->P();
}


