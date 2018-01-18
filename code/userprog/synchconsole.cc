#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"
#include "stdio.h"

static Semaphore *readAvail;

static Semaphore *writeDone;

static Semaphore *monitorWrite;
static Semaphore *monitorRead;

static Semaphore *monitorWriteString;
static Semaphore *monitorReadString;

static void ReadAvail(int arg) { readAvail->V(); }

static void WriteDone(int arg) { writeDone->V(); }

char *buffer[MAX_STRING_SIZE];

/*void initBuffer(char *buffer){

}*/

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
    monitorWrite = new Semaphore("putChar security", 1);
    monitorRead = new Semaphore("putChar security", 1);
    monitorWriteString = new Semaphore("putString security", 1);
    monitorReadString = new Semaphore("putString security", 1);
	console = new Console (readFile, writeFile, ReadAvail, WriteDone, 0);
}
	SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
    delete monitorWrite;
    delete monitorRead;
    delete monitorWriteString;
    delete monitorReadString;
}

void SynchConsole::SynchPutChar(const char ch)
{
    //printf("e\n");
    monitorWrite->P();
    //printf("f\n");
    console->PutChar(ch);    // echo it!
    //printf("k\n");
	writeDone->P();
    //printf("j\n");
    monitorWrite->V();
    
    //printf("l\n");
}

char SynchConsole::SynchGetChar()
{
    
    monitorRead->P();
	char ch;
	readAvail->P();
	ch = console->GetChar();
    monitorRead->V();
	return ch;
}

void SynchConsole::SynchPutString(const char s[])
{
  monitorWrite->P();
	int i = 0;
	while((i < MAX_STRING_SIZE) && (s[i] != '\0')){
		console->PutChar(s[i]);
        writeDone->P();
		i++;    
	}
  monitorWrite->V();
}

void SynchConsole::SynchGetString(char *s, int n)
{
  monitorReadString->P();
	char ch;
	for(int i = 0; i< n; i++){
		ch = SynchGetChar();
		if (ch == EOF){
			break;
		}
		//Condition permettant d'éviter de quitter tout de suite
		//Si l'appel à SynchGetString sui un appel à SynchGetChar
		else if(ch 	== '\n' && i>0){
			break;
		}
		s[i] = ch;
	}
	s[n] = '\0';
  monitorReadString->V();
}
void SynchConsole::SynchPutInt(const int n){
    char str[15];
    snprintf(str,15,"%d",n);
	SynchPutString(str);
}

void SynchConsole::SynchGetInt(int *n){
  char c;
  char str[16];
  int i = 0;
  c=SynchGetChar();
  if (c=='-' || (c>='0' && c<='9') ) 
  {
    str[i] = c;
    i++;
  }
  c = SynchGetChar();
  while(c>='0' && c<='9' && i<15) {
    str[i] = c;
    c=SynchGetChar();
    i++;
  }
  str[i] = '\0';
  sscanf(str,"%d",n);
}
