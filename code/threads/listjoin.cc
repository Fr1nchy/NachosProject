#include "listjoin.h"
#include <unistd.h>

Element::Element(int id){
    tid = id;
    next = NULL;
    s = new Semaphore("join",0);   
}


ListJoin::ListJoin(){
    first = last = NULL;
}

ListJoin::~ListJoin(){

}

Element *
ListJoin::Find(int tid){

    Element * ptr = first;
    while((ptr != NULL) && (ptr->tid ==tid)){
        ptr = ptr->next;
    } 
    return ptr;
}

void
ListJoin::Add(int tid){
    Element *element = new Element(tid);
    if (IsEmpty ()){
	  first = element;
	  last = element;
    }else{
	  last->next = element;
	  last = element;
    }
}

int
ListJoin::Suppr(int tid){

    Element * ptr = first;
    Element * AC = NULL;

    while((ptr != NULL) && (ptr->tid !=tid)){
        printf("tid:%d\n",ptr->tid);
        AC = ptr;
        ptr = ptr->next;
    }
    printf("Suppr:%p\n",ptr);
    if(ptr == NULL){
        return -1;
    }else{
        ptr->s->V();
        if(AC == NULL && ptr != NULL){
            first = ptr->next;
        }else{
            AC->next = ptr->next;
        }
        delete ptr->s;
        delete ptr;
    }
    return 0;
}

bool
ListJoin::IsEmpty ()
{
    if (first == NULL)
	return TRUE;
    else
	return FALSE;
}


