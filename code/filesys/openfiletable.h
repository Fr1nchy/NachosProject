#include <stdlib.h>

#ifndef OPENFILETABLE_H
#define OPENFILETABLE_H

class OpenFileTable {
	public:
		OpenFileTable();
		~OpenFileTable();
		void Add(int sector);

		int Find(int sector);	

		void Remove(int sector);
	private:
		int tableSize;
		int* openFileTable;
};

#endif