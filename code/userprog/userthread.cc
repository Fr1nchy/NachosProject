#include "userthread.h"


static void StartUserThread(int f) {
	int k = 0;
	for (int i = 0; i < 4; i++) {
		k = i;
	}
	k++;
}

int do_UserThreadCreate(int f, int arg) {
    Thread* newThread = new Thread("User thread");
    newThread->space = currentThread->space;
    newThread->Fork(StartUserThread, f);
	return do_UserThreadExit();
}

int do_UserThreadExit() {
	currentThread->Finish();
	return 0;
}