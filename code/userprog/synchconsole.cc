#include "copyright.h"
#include "system.h"
#include "synchconsole.h"
#include "synch.h"

static Semaphore *readAvail;

static Semaphore *writeDone;
static Semaphore *monitor;

static void ReadAvail(int arg) { readAvail->V(); }

static void WriteDone(int arg) { writeDone->V(); }

char *buffer[MAX_STRING_SIZE];

/*void initBuffer(char *buffer){

}*/

SynchConsole::SynchConsole(char *readFile, char *writeFile)
{
	readAvail = new Semaphore("read avail", 0);
	writeDone = new Semaphore("write done", 0);
    monitor = new Semaphore("putChar security", 1);
	console = new Console (readFile, writeFile, ReadAvail, WriteDone, 0);
}
	SynchConsole::~SynchConsole()
{
	delete console;
	delete writeDone;
	delete readAvail;
    delete monitor;
}

void SynchConsole::SynchPutChar(const char ch)
{
    monitor->P();
    console->PutChar (ch);    // echo it!
	writeDone->P();
    monitor->V();
}

char SynchConsole::SynchGetChar()
{
    monitor->P();
	char ch;
	readAvail->P();
	ch = console->GetChar();
    monitor->V();
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
	char ch;
	for(int i = 0; i< n; i++){
		ch = SynchGetChar();
		if (ch == EOF){
			s[i] = '\0';
			break;
		}
		else if(ch 	== '\n'){
			s[i] = '\n';
			s[i+1] = '\0';
			break;
		}
		s[i] = ch;
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
