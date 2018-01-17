// filehdr.cc 
//	Routines for managing the disk file header (in UNIX, this
//	would be called the i-node).
//
//	The file header is used to locate where on disk the 
//	file's data is stored.  We implement this as a fixed size
//	table of pointers -- each entry in the table points to the 
//	disk sector containing that portion of the file data
//	(in other words, there are no indirect or doubly indirect 
//	blocks). The table size is chosen so that the file header
//	will be just big enough to fit in one disk sector, 
//
//      Unlike in a real system, we do not keep track of file permissions, 
//	ownership, last modification date, etc., in the file header. 
//
//	A file header can be initialized in two ways:
//	   for a new file, by modifying the in-memory data structure
//	     to point to the newly allocated data blocks
//	   for a file already on disk, by reading the file header from disk
//
// Copyright (c) 1992-1993 The Regents of the University of California.
// All rights reserved.  See copyright.h for copyright notice and limitation 
// of liability and disclaimer of warranty provisions.

#include "copyright.h"

#include "system.h"
#include "filehdr.h"

//----------------------------------------------------------------------
// FileHeader::Allocate
// 	Initialize a fresh file header for a newly created file.
//	Allocate data blocks for the file out of the map of free disk blocks.
//	Return FALSE if there are not enough free   blocks to accomodate
//	the new file.
//
//	"freeMap" is the bit map of free disk sectors
//	"fileSize" is the bit map of free disk sectors
//----------------------------------------------------------------------

bool
FileHeader::Allocate(BitMap *freeMap, int fileSize)
{ 
    numBytes = fileSize;
    numSectors  = divRoundUp(fileSize, SectorSize);
    unsigned numIndSectors = 0;
    unsigned numDirectSectors = numSectors;    


    if ((unsigned) numSectors > NumDirect) { //if we need indirection
        numIndSectors = divRoundUp(numSectors - NumDirect, NumDirect - 1); //For every (NumDirect-1) sectors, we have one less direct sector
        numDirectSectors = NumDirect - numIndSectors;
    }

    //unsigned indirectDataSize = numBytes - SectorSize * numDirectSectors;

    DEBUG('f', "numSectors = %d\n", numSectors);
    DEBUG('f', "Nb secteurs d'indirection : %d\n", numIndSectors);
    DEBUG('f', "Nb secteurs de données : %d\n\n", numDirectSectors);

    if (freeMap->NumClear() < numSectors)
	return FALSE;		// not enough space


    for (int i = 0; (unsigned)i < numDirectSectors; i++) {
	   dataSectors[i] = freeMap->Find();
    }   
    
    unsigned size = numBytes - numDirectSectors * SectorSize;


    for (unsigned i = numDirectSectors; i < NumDirect && (int) i < numSectors; i++) {
        FileHeader *hdr;
        hdr = new FileHeader;
        dataSectors[i] = freeMap->Find();  

        
        if (size > MaxFileSize) {
            hdr->Allocate(freeMap, MaxFileSize);
        }
        else
            hdr->Allocate(freeMap, size);
        
        hdr->WriteBack(dataSectors[i]);
        size -= MaxFileSize;

        /*Indirection *indir = new Indirection(indirectData);
        indir->WriteBack(dataSectors[i]);*/
        delete hdr;
    }
    return TRUE;
}

//----------------------------------------------------------------------
// FileHeader::Deallocate
// 	De-allocate all the space allocated for data blocks for this file.
//
//	"freeMap" is the bit map of free disk sectors
//----------------------------------------------------------------------

void 
FileHeader::Deallocate(BitMap *freeMap)
{   
    unsigned numIndSectors = 0;
    unsigned numDirectSectors = numSectors;    
    unsigned i;


    if ((unsigned) numSectors > NumDirect) { //if we need indirection
        numIndSectors = divRoundUp(numSectors - NumDirect, NumDirect - 1); //For every (NumDirect-1) sectors, we have one less direct sector
        numDirectSectors = NumDirect - numIndSectors;
    }

    for (i = 0; i < numIndSectors; i++) {
        FileHeader *hdr = new FileHeader;
        hdr->FetchFrom(dataSectors[i+numDirectSectors]);
        hdr->Deallocate(freeMap);
        delete hdr;
    }

    for (int j = 0; j < numSectors; j++) {
	   ASSERT(freeMap->Test((int) dataSectors[j]));  // ought to be marked!
	   freeMap->Clear((int) dataSectors[j]);
    }

}

//----------------------------------------------------------------------
// FileHeader::FetchFrom
// 	Fetch contents of file header from disk. 
//
//	"sector" is the disk sector containing the file header
//----------------------------------------------------------------------

void
FileHeader::FetchFrom(int sector)
{
    synchDisk->ReadSector(sector, (char *)this);
}

//----------------------------------------------------------------------
// FileHeader::WriteBack
// 	Write the modified contents of the file header back to disk. 
//
//	"sector" is the disk sector to contain the file header
//----------------------------------------------------------------------

void
FileHeader::WriteBack(int sector)
{
    synchDisk->WriteSector(sector, (char *)this); 
}

//----------------------------------------------------------------------
// FileHeader::ByteToSector
// 	Return which disk sector is storing a particular byte within the file.
//      This is essentially a translation from a virtual address (the
//	offset in the file) to a physical address (the sector where the
//	data at the offset is stored).
//
//	"offset" is the location within the file of the byte in question
//----------------------------------------------------------------------

int
FileHeader::ByteToSector(int offset)
{
    unsigned numIndSectors = 0;
    unsigned numDirectSectors = numSectors;
    int index = offset/SectorSize;
    int r;
    int k = dataSectors[index];

 
    if ((unsigned) numSectors > NumDirect) { //if we need indirection
        numIndSectors = divRoundUp(numSectors - NumDirect, NumDirect - 1); //For every (NumDirect-1) sectors, we have one less direct sector
        numDirectSectors = NumDirect - numIndSectors;


        if ((unsigned)offset >= SectorSize*numDirectSectors) {
            r = (offset - numDirectSectors*SectorSize +1) / MaxFileSize;

            index = numDirectSectors + r;

            FileHeader *hdr = new FileHeader;

            hdr->FetchFrom(dataSectors[index]); 

            return hdr->ByteToSector(offset - numDirectSectors*SectorSize - MaxFileSize*r);
        }
    }

//    DEBUG('f', "k = %d\n", k);

    
    
    /*DEBUG('f', "ByteToSector: offset = %d, k = %d, numIndirectSectors = %d, numDirectSectors = %d, taille totale = %d, index = %d\n"
        , offset, k, 
        numIndSectors, numDirectSectors, FileLength(), index);*/
    
    return(k);
}

//----------------------------------------------------------------------
// FileHeader::FileLength
// 	Return the number of bytes in the file.
//----------------------------------------------------------------------

int
FileHeader::FileLength()
{
    return numBytes;
}

//----------------------------------------------------------------------
// FileHeader::Print
// 	Print the contents of the file header, and the contents of all
//	the data blocks pointed to by the file header.
//----------------------------------------------------------------------

void
FileHeader::Print()
{
    unsigned i;
    unsigned numIndSectors = 0;
    unsigned numDirectSectors = numSectors;    


    if ((unsigned) numSectors > NumDirect) { //if we need indirection
        numIndSectors = divRoundUp(numSectors - NumDirect, NumDirect - 1); //For every (NumDirect-1) sectors, we have one less direct sector
        numDirectSectors = NumDirect - numIndSectors;
    }
/*
    printf("FileHeader contents.  File size: %d.  File blocks:\n", numBytes);
    for (i = 0; i < numDirectSectors; i++)
	printf("%d ", dataSectors[i]);*/
    printf("FileHeader contents.  File size: %d.  File blocks:\n", numBytes);
    PrintSectors();

    for (i = 0; i < numIndSectors; i++) {
        FileHeader *hdr = new FileHeader;
        hdr->FetchFrom(dataSectors[i+numDirectSectors]);
        hdr->PrintSectors();
        delete hdr;
    }


    printf("\nFile contents:\n");
    PrintContent();
    for (i = 0; i < numIndSectors; i++) {
        FileHeader *hdr = new FileHeader;
        hdr->FetchFrom(dataSectors[i+numDirectSectors]);
        hdr->PrintContent();
        delete hdr;
    }
}

void FileHeader::PrintSectors() {
    unsigned i;
    unsigned numDirectSectors = numSectors; 
    unsigned numIndSectors = 0;



    if ((unsigned) numSectors > NumDirect) { //if we need indirection
        numIndSectors = divRoundUp(numSectors - NumDirect, NumDirect - 1); //For every (NumDirect-1) sectors, we have one less direct sector
        numDirectSectors = NumDirect - numIndSectors;
    }
   
    for (i = 0; i < numDirectSectors; i++)
    printf("%d ", dataSectors[i]);

}

void FileHeader::PrintContent() {    
    unsigned i;
    int j, k;
    char *data = new char[SectorSize];
    unsigned numDirectSectors = numSectors; 
    unsigned numIndSectors = 0;

    if ((unsigned) numSectors > NumDirect) { //if we need indirection
        numIndSectors = divRoundUp(numSectors - NumDirect, NumDirect - 1); //For every (NumDirect-1) sectors, we have one less direct sector
        numDirectSectors = NumDirect - numIndSectors;
    }

    for (i = k = 0; i < numDirectSectors; i++) {
        synchDisk->ReadSector(dataSectors[i], data);
        for (j = 0; (j < SectorSize) && (k < numBytes); j++, k++) {
            if ('\040' <= data[j] && data[j] <= '\176') // isprint(data[j]) 
                printf("%c", data[j]);
            else
                printf("\\%x", (unsigned char)data[j]);
        }
        printf("\n"); 
    }
    delete [] data;
}