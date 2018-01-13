#include "syscall.h"

int main()
{
    Semaphore sem;
    Sem_init(&sem,0);
    PutInt(sem);
    Sem_post(sem);
    Sem_wait(sem);
    Sem_destroy(sem);
    return 0;
}


