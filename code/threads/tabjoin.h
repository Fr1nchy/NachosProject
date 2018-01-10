#ifndef TABJOIN_H
#define TABJOIN_H

//#include "system.h"
#include "synch.h"

class Couple
{
  public:
    Couple (int id);
    ~Couple ();
    int getTid();
    void P();
    void V();

  private:
    Semaphore *s;
    int tid;
};

class Tabjoin
{
  public:
    Tabjoin (int taille);
    ~Tabjoin ();

    Couple * Find(int tid);//creation couple et le renvoie 
    int Add(int tid); //renvoie -1 si erreur 
    int Suppr(int tid);
  private:
    int size;
    Couple** tab;  
};

#endif 

/*creer thread:
    tabjoin->add(tid);

join:
    tabjoin->Find(tid)->P();

suppr thread
    tabjoin->suppr(current->thread->tid) /// ->V(); + delete couple

*/

