#ifndef FRAMEPROVIDER_H
#define FRAMEPROVIDER_H

#include "copyright.h"
#include "filesys.h"
#include "bitmap.h"

class FrameProvider
{
	public:
    	FrameProvider(int nbframes);
    	~FrameProvider();
	int GetEmptyFrame();
	int NumAvailFrame();
    	void ReleaseFrame(int id);
    private:
    	int nbFrames;
        BitMap * bitmap;
};
#endif
