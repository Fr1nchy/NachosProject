#include <string.h>
#include "frameprovider.h"
#include "system.h"

FrameProvider::FrameProvider(int nbframes){
	bitmap = new BitMap(nbframes);
	nbFrames = nbframes;
}

FrameProvider::~FrameProvider(){
	delete bitmap;
}

int
FrameProvider::GetEmptyFrame(){
	int rand =0;
	RandomInit(0);
	
	rand = Random()%NumPhysPages;
        while(this->bitmap->Test(rand)) {
                rand = Random()%NumPhysPages;
        }
	bitmap->Mark(rand);
	bzero(&(machine->mainMemory[ PageSize * rand] ), PageSize);
	return rand;
}

int
FrameProvider::NumAvailFrame(){
	return bitmap->NumClear();
}
void
FrameProvider::ReleaseFrame(int id){
	bitmap->Clear(id);
}
