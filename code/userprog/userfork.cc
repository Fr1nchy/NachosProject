#include "userfork.h"
#include "system.h"

int do_UserForkCreate (char *filename){
	OpenFile * executable = fileSystem->Open(filename);
	if(executable==NULL){
		printf("Erreur de fichier\n");
		delete executable;
		return -1;
	}
	AddrSpace * space = new AddrSpace(executable);
	if(space == NULL){
	    delete space;
	    delete executable;
	    return -1;
	}
	Thread* newThread = new Thread(filename);
	newThread->space = space;
    newThread->Fork(StartUserFork,0);
    
    return 0;
}

void StartUserFork (int arg){
    currentThread->space->InitRegisters ();
    currentThread->space->RestoreState ();
    machine->Run();
}

void do_UserForkExit(){
    interrupt->Halt();
}

