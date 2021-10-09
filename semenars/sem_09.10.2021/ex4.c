#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

int a[3] = {0};

void *mythread(void *dummy)
{
    pthread_t mythid; /* Для идентификатора нити исполнения */
    mythid = pthread_self();

    for (int i = 0; i < 10E7; i++)
    {
        a[0]++;
        a[2]++;
    }

    printf("Thread %d, Calculation result = %d\n", mythid, a);

    return NULL;
}


int main()
{
    pthread_t thid1, mythid;
    int result = pthread_create( &thid1, (pthread_attr_t *)NULL, mythread, NULL);
    if(result != 0)
    {
        printf ("Error on thread create, return value = %d\n", result);
        exit(-1);
    }
    printf("Thread created, thid = %d\n", thid1);

    mythid = pthread_self();

    for (int i = 0; i < 10E7; i++)
    {
        a[1]++;
        a[2]++;
    }

    printf("Thread %d, Calculation result = %d\n", mythid, a);

    pthread_join(thid1, (void **)NULL);
    
    printf ("a[0] = %d, a[1] = %d, a[2] = %d\n", a[0], a[1], a[2]);

    return 0;
}