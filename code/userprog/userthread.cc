#include "userthread.h"
#include "machine.h"
#include "syscall.h"
#include "synch.h"
#include "system.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


static Semaphore* s;
static Thread** threads = new Thread*[nbThreadsMax];

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

static int getIndexThreadById(int id) {
    int i = 0;
    while ((i < nbThreadsMax)&&(threads[i]!=NULL)&&(threads[i]->getTid() != id)) {
        i++;
    }
    if(i==nbThreadsMax || threads[i]==NULL){
        return -1;
    }else{
        return i;
    }
    
}

int do_UserThreadCreate(int f, int arg) {
    s = new Semaphore("User thread finished", 0);
    //char buffer[100];
    //snprintf(buffer, 100, "%d", idThread);
    //itoa(idThread, buffer, 10);
    //Thread* newThread = new Thread(strcat("User thread", buffer));
    Thread* newThread = new Thread("User thread");
    Parametre * p = new Parametre();

    newThread->setTid(idThread);
    newThread->setBid(currentThread->space->bitmap->Find());
    int i = 0;
    while (i < nbThreadsMax && threads[i] != NULL) i++;
    if (i < nbThreadsMax) threads[i] = newThread;
    else return 0; //Nb threads max atteint
    
    semaNumThreads->P();
    nbThreads++;
    idThread++;
    semaNumThreads->V();
 
    p->f = f;
    p->arg = arg;

    newThread->Fork(StartUserThread, (int)p);
    //s->P();

      
    return newThread->getTid();
}    

int do_UserThreadExit() {
    //s->V();

    currentThread->Sem_V();
    int index = getIndexThreadById(currentThread->getTid());
    if (index > nbThreadsMax) threads[index] = NULL;
    currentThread->Finish();
    currentThread->space->bitmap->Clear(currentThread->getBid());
    semaNumThreads->P();
    nbThreads--;
    semaNumThreads->V();

	return 0;
}

void join_UserThread(int tid){    
    if (tid < nbThreadsMax) {
        int index = getIndexThreadById(tid);   
        if(index !=-1){
            threads[index]->Sem_P();
        }
    }
}


