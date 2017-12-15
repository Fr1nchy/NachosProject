#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;

static Semaphore *writeDone;

static void ReadAvail(int arg) { readAvail->V(); }

static void WriteDone(int arg) { writeDone->V(); }

char *buffer[MAX_STRING_SIZE];

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
	console = new Console (readFile, writeFile, ReadAvail, WriteDone, 0);
}
	SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
}

void SynchConsole::SynchPutChar(const char ch)
{
    console->PutChar (ch);    // echo it!
	writeDone->P();
}

char SynchConsole::SynchGetChar()
{
	char ch;
	readAvail->P();
	ch = console->GetChar();
	return ch;
}

void SynchConsole::SynchPutString(const char s[])
{
	int i = 0;
	while((i < MAX_STRING_SIZE) && (s[i] != '\0')){
		SynchPutChar(s[i]);
		i++;    
	}
}

void SynchConsole::SynchGetString(char *s, int n)
{
	for(int i = 0; i< n; i++){
		s[i] = SynchGetChar();
	}
	s[n] = '\0';
}
void SynchConsole::SynchPutInt(int n){
    char str[15];
    snprintf(str,15,"%d",n);
	SynchPutString(str);
}

void SynchConsole::SynchGetInt(int *n){
  char c;
  char str[15];
  int i =0;

  c=SynchGetChar();
  while((c>='0')&&(c<='9')&&(i<15)){
    str[i] = c;
    c=SynchGetChar();
    i++;
  }
  str[i] = '\0';
  sscanf(str,"%d",n);
    
}
