#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a = 0;

void *mythread(void *dummy)
{
    pthread_t mythid; /* Для идентификатора нити исполнения */
    mythid = pthread_self();

    a = a + 1;

    printf("Thread %d, Calculation result = %d\n", mythid, a);

    return NULL;
}


int main()
{
    pthread_t thid1, thid2, mythid;
    int result = pthread_create( &thid1, (pthread_attr_t *)NULL, mythread, NULL);
    if(result != 0)
    {
        printf ("Error on thread create, return value = %d\n", result);
        exit(-1);
    }
    printf("Thread created, thid = %d\n", thid1);
    
    result = pthread_create( &thid2, (pthread_attr_t *)NULL, mythread, NULL);
    if(result != 0)
    {
        printf ("Error on thread create, return value = %d\n", result);
        exit(-1);
    }
    printf("Thread created, thid = %d\n", thid2);

    mythid = pthread_self();

    a = a + 1;

    printf("Thread %d, Calculation result = %d\n", mythid, a);

    pthread_join(thid1, (void **)NULL);
    pthread_join(thid2, (void **)NULL);
    
    return 0;
}