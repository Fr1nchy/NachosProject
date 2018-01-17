#include "syscall.h"

#define N 30
Semaphore mutex;
Semaphore vide;
Semaphore plein;
char buffer[N];

void producteur(void *p)
{
	// PutString("producteur");
	Sem_wait(mutex);
	char c = 'a';
    int i = 0;
	for (i = 0; i < N; i++)
	{
		buffer[i] = c+i;
		if (i==N-1)
		{
			buffer[i] = '\n';
		}
		Sem_wait(vide);
	}
	Sem_post(plein);
	Sem_post(mutex);
	//PutString("Buffer de producteur =");
	//PutString(buffer);
}
void consommateur(void *p)
{
	char bufferConsommateur[N];
	Sem_wait(plein);
    int i = 0;
	for (i = 0; i < N; i++)
	{
		Sem_wait(mutex);
		if (buffer[i] != 'x')
		{
			bufferConsommateur[i] = buffer[i];
			buffer[i] = 'x';
		}else{
			bufferConsommateur[i] = buffer[i];
		}
		if (i == N-1)
		{
			bufferConsommateur[i] = '\n';
		}
		Sem_post(plein);
		Sem_post(mutex);
	}
	Sem_post(vide);
	//PutString("Buffer de consommateur =");
	PutString(bufferConsommateur);
}

int main()
{
	Sem_init(&mutex, 1);
	Sem_init(&vide, N);
	Sem_init(&plein, 0);
	char c = 'a';

	int t1, t2, t3;
	t1 = UserThreadCreate(producteur, &c);
	t2 = UserThreadCreate(consommateur, &c);
	t3 = UserThreadCreate(consommateur, &c);
	int t4 = UserThreadCreate(consommateur, &c);

	UserThreadJoin(t1); UserThreadJoin(t2); UserThreadJoin(t3); UserThreadJoin(t4);

	Sem_destroy(mutex);
	Sem_destroy(vide);
	Sem_destroy(plein);

	/*
    Semaphore sem;
    Sem_init(&sem,0);
    PutInt(sem);
    Sem_post(sem);
    Sem_wait(sem);
    Sem_destroy(sem);
    */
    return 0;
}


	