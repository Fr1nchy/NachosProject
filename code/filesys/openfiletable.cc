#include "openfiletable.h"

OpenFileTable::OpenFileTable() {
	tableSize = 10; 
	openFileTable = new int[10];
	//openFileTable = malloc(sizeof(int)*tableSize);
	for (int i = 0; i < tableSize; i++) {
		openFileTable[i] = -1;
	}
}

OpenFileTable::~OpenFileTable() {
	delete[] openFileTable;
}

void OpenFileTable::Add(int sector) {
	int i = Find(-1);
	if (i >= 0) {
		openFileTable[i] = sector;
	}
}

int OpenFileTable::Find(int sector) {
	for (int i = 0; i < tableSize; i++) {
		if (openFileTable[i] == sector) {
			return i;
		}
	}	
	return -1;
}

void OpenFileTable::Remove(int sector) {
	int i = Find(sector);
	if (i >= 0) {
		openFileTable[i] = -1;
	}
}