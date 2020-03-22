#include "stdio.h"
#include "semaphore.h"
#include "pthread.h"
#include "signal.h"
#include <stdlib.h>
#include <unistd.h>

pthread_t ThreadA;
pthread_t ThreadB;

//init semaphore

struct SemaphoreStruct
{
    sem_t Semaphore;
    int IsShared;
    unsigned int InitValue;
};

int SemaphoreInit(sem_t *semaphore, int pshared, unsigned int value)
{
    Semaphore = semaphore;
    IsShared = pshared;
    InitValue = value;
}
int Sem_Wait(sem_t *semaphore)
{
}
int Sem_Post(sem_t *semaphore);
int Sem_GetValue(sem_t *semaphore, int *value_ptr);
int Sem_Detroy(sem_t *sem);

int main()
{
    return 0;
}
