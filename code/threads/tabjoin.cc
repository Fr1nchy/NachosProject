#include "tabjoin.h"
#include <unistd.h>

Couple::Couple(int id){
    tid = id;
    s = new Semaphore("join",0);   
}

Couple::~Couple(){
    delete s;
}

int
Couple::getTid(){
    return tid;
}

void
Couple::P(){
    s->P();
}

void
Couple::V(){
    s->V();
}


Tabjoin::Tabjoin(int taille){    
    size = taille;
    tab = (Couple**) malloc(sizeof(Couple*)*taille);
    //for (int i = 0; i < taille; i++)
    //printf("%d\n",tab[0].getTid());
    
}

Tabjoin::~Tabjoin(){
    delete tab;
}

Couple *
Tabjoin::Find(int tid){
    int i = 0;
    while (i < size && tab[i]->getTid() != tid) //check tab[i].getTid() does not segfault
    {
        i++;
    }
    if (i == size)
    {
        return NULL;
    }
    return tab[i];
}

int
Tabjoin::Add(int tid){
    int cnt = 0;
    while (cnt < size && tab[cnt] != NULL)
    {
        cnt++;
    }
    if (cnt == size)
    {
        return -1;
    }
    tab[cnt] = new Couple(tid);
    return 0;
}

int
Tabjoin::Suppr(int tid){
    Couple* c = Find(tid);
    if (c == NULL)
        return -1;
    else
        delete c;
    return 0;
}


