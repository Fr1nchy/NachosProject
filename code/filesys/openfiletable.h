class OpenFileTable {
public:
	void Add(int sector);

	int Find(int sector);

	void Remove(int sector);


private:
	int tableSize;
	int[] openFileTable;
}