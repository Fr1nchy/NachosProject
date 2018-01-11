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
    //PROCHAINE LIGNE BUGUEE
    //check tab[i].getTid() does not segfault
    while (i < size && tab[i] != NULL && tab[i]->getTid() != tid){
        i++;
    }
    printf("smthing %d,%s \n", i,(char*)tab[i]);
    if (i == size){
        printf("trace\n");
        return NULL;
    }
    else if (tab[i] == NULL)
        //printf("trace2\n");
        return NULL;
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
        c->V();
        delete c;
    return 0;
}


