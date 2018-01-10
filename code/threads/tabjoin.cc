#include "tabjoin.h"

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

}

Tabjoin::~Tabjoin(){

}

Couple *
Tabjoin::Find(int tid){
    return NULL;
}

int
Tabjoin::Add(int tid){
    return 0;
}

int
Tabjoin::Suppr(int tid){
    return 0;
}


