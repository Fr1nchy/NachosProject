#ifndef LISTJOIN_H
#define LISTJOIN_H

#include "synch.h"

class Element
{
  public:
    Element(int tid);
    Element *next;
    Semaphore *s;
    int tid;
};

class ListJoin
{
  public:
    ListJoin ();			
    ~ListJoin ();
    void Add(int tid);
    int Suppr(int tid);
    Element * Find(int tid);
    bool IsEmpty ();
  private:
    Element * first;
    Element *last;
};

#endif 


