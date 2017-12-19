// exception.cc 
//      Entry point into the Nachos kernel from user programs.
//      There are two kinds of things that can cause control to
//      transfer back to here from user code:
//
//      syscall -- The user code explicitly requests to call a procedure
//      in the Nachos kernel.  Right now, the only function we support is
//      "Halt".
//
//      exceptions -- The user code does something that the CPU can't handle.
//      For instance, accessing memory that doesn't exist, arithmetic errors,
//      etc.  
//
//      Interrupts (which can also cause control to transfer from user
//      code into the Nachos kernel) are handled elsewhere.
//
// For now, this only handles the Halt() system call.
// Everything else core dumps.
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"
#include "system.h"
#include "syscall.h"
#include "userthread.h"

//----------------------------------------------------------------------
// UpdatePC : Increments the Program Counter register in order to resume
// the user program immediately after the "syscall" instruction.
//----------------------------------------------------------------------
static void
UpdatePC ()
{
    int pc = machine->ReadRegister (PCReg);
    machine->WriteRegister (PrevPCReg, pc);
    pc = machine->ReadRegister (NextPCReg);
    machine->WriteRegister (PCReg, pc);
    pc += 4;
    machine->WriteRegister (NextPCReg, pc);
}


//----------------------------------------------------------------------
// ExceptionHandler
//      Entry point into the Nachos kernel.  Called when a user program
//      is executing, and either does a syscall, or generates an addressing
//      or arithmetic exception.
//
//      For system calls, the following is the calling convention:
//
//      system call code -- r2
//              arg1 -- r4
//              arg2 -- r5
//              arg3 -- r6
//              arg4 -- r7
//
//      The result of the system call, if any, must be put back into r2. 
//
// And don't forget to increment the pc before returning. (Or else you'll
// loop making the same system call forever!
//
//      "which" is the kind of exception.  The list of possible exceptions 
//      are in machine.h.
//----------------------------------------------------------------------

void copyStringFromMachine( int from, char *to, unsigned size){
  unsigned int i = 0;
  int res = 0;

  while((i < size) && (machine->ReadMem(from+i, 1, &res))){
    to[i] = res;
    i++;
  }
}

void copyStringToMachine( int reg, char *buf, unsigned size){
  unsigned int i = 0;
  while((i < size) && (machine->WriteMem(reg+i, 1,(int)buf[i])))
    i++;
}

void
ExceptionHandler (ExceptionType which)
{
    int type = machine->ReadRegister (2);

    /*if ((which == SyscallException) && (type == SC_Halt))
      {
	  DEBUG ('a', "Shutdown, initiated by user program.\n");
	  interrupt->Halt ();
      }
    else
      {
	  printf ("Unexpected user mode exception %d %d\n", which, type);
	  ASSERT (FALSE);
      }
    */
    if (which == SyscallException) {
      switch (type) {
      case SC_Halt: {
        DEBUG ('a', "Shutdown, initiated by user program.\n");
        interrupt->Halt();
        break;
      }
      case SC_PutChar: {
        DEBUG ('a', "Execp: Putchar\n");
        char ch = (char)machine->ReadRegister(4);
        synchconsole->SynchPutChar(ch);
        break;
      }
      case SC_PutString: {
        DEBUG ('a', "Execp: PutString\n");
        char buffer[MAX_STRING_SIZE];
        copyStringFromMachine(machine->ReadRegister(4), buffer, MAX_STRING_SIZE);
        synchconsole->SynchPutString(buffer);
        break;
      }
      case SC_GetChar: {
        DEBUG ('a', "Execp: GetChar\n");
        machine->WriteRegister (2, synchconsole->SynchGetChar());
        break;
      }
      case SC_GetString: {
        DEBUG ('a', "Execp: GetString\n");
        char buffer[MAX_STRING_SIZE];

        int s = machine->ReadRegister(4);
        int n = machine->ReadRegister(5);
        synchconsole->SynchGetString(buffer,n);
        copyStringToMachine(s, buffer,n);
        break;
      }
      case SC_PutInt: {
        DEBUG ('a', "Execp: PutInt\n");
        int n = machine->ReadRegister(4);
        synchconsole->SynchPutInt(n);

        break;
      }
      case SC_GetInt: {
        DEBUG ('a', "Execp: GetInt\n");
        int entier = 0;
        int n = machine->ReadRegister(4);

        synchconsole->SynchGetInt(&entier);
        machine->WriteMem(n, 1,entier);
        break;
      }
      case SC_UserThreadCreate: {
        DEBUG('a', "Excep: UserThreadCreate\n");
        int f = machine->ReadRegister(4);
        int arg = machine->ReadRegister(5);
        int res = do_UserThreadCreate(f, arg);
        machine->WriteMem(2, 1,res);
        break;
      }
      case SC_UserThreadExit: {
        DEBUG('a', "Excep: UserThreadExit\n");
        do_UserThreadExit();
        break;
      }

      default: {
        printf("Unexpected user mode exception %d %d\n", which, type);
        ASSERT(FALSE); break;
      }
      }
      UpdatePC();
    }

    // LB: Do not forget to increment the pc before returning!
    //UpdatePC ();
    // End of addition
}


