#include "userthread.h"
#include "machine.h"
#include "syscall.h"
#include "synch.h"
#include "system.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "userfork.h"
#include "listjoin.h"

static void StartUserThread(int f) {  
    Parametre p = *((Parametre*)f);
    currentThread->space->InitRegisters ();
    currentThread->space->RestoreState ();
    
    machine->WriteRegister(PrevPCReg,machine->ReadRegister(PCReg));
    machine->WriteRegister(PCReg,p.f);
    machine->WriteRegister(NextPCReg,p.f+4);
    machine->WriteRegister(4,p.arg);

    machine->WriteRegister(31,p.fin);

    machine->WriteRegister(StackReg,currentThread->space->ThreadSpace());
    //printf("stack:%d\n",machine->ReadRegister(StackReg));
    
    if(machine->ReadRegister(StackReg) == -1) {
    	do_UserThreadExit();
    }else {
    	machine->Run();
    }
}

int do_UserThreadCreate(int f, int arg, int fin) {
    Thread* newThread = new Thread("User thread");
    Parametre * p = new Parametre();
    p->f = f;
    p->arg = arg;
    p->fin = fin;
    int bid = currentThread->space->incrementIdNbThread();
    int tid = currentThread->space->getIdThread();

    if(bid!=-1){
    	p->f = f;
    	p->arg = arg;
	    newThread->setBid(bid);
	    newThread->setTid(tid);
        listThJoin->Add(tid);
    	newThread->Fork(StartUserThread, (int)p);
    }

    return tid;
}    

int do_UserThreadExit() {
    currentThread->space->decrementNbThreadResetSpace();
    if(currentThread->space->ExitThread()==0){
        do_UserForkExit();
    }else{
	    currentThread->Finish();        
    }
    return 0;
}

void join_UserThread(int tid){
    if(tid < nbThreadsMax){
        Element * e = listThJoin->Find(tid);
        if(e !=NULL){
            e->s->P();
        }
    }
}

