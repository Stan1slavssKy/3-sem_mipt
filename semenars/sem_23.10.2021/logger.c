#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/sem.h>

//=============================================================================================================

void* log_in_file (void* fd_ptr);
void create_threads ();
void create_semafor (char* pathname);

const char* LOG_FILE_NAME = "log_file.txt";

int semid;

//=============================================================================================================

int main ()
{
    char pathname[] = "semafor_file";
    create_semafor (pathname);
    create_threads ();
    return 0;
}

//=============================================================================================================

void create_semafor (char* pathname)
{
    assert (pathname);

    key_t key = 0;
    
    if (key = ftok (pathname, 0) < 0)
    {
        fprintf (stderr, "error %d\n", __LINE__);
        exit (-1);
    }
    
    if (semid = semget (key, 1, 0666 | IPC_CREAT) == -1)
    {
        fprintf (stderr, "error %d\n", __LINE__);
        exit (-1);    
    }
}

//=============================================================================================================

void create_threads ()
{
    pthread_t fir_thread = 0;
    pthread_t sec_thread = 0;

    FILE* fd = fopen (LOG_FILE_NAME, "wb");

    if (pthread_create (&fir_thread, (pthread_attr_t*) NULL, log_in_file, (void*)fd))
    {
        fprintf (stderr, "error in pthread_create, %d\n", __LINE__);
    }

    if (pthread_create (&sec_thread, (pthread_attr_t*) NULL, log_in_file, (void*)fd))
    {
        fprintf (stderr, "error in pthread_create, %d\n", __LINE__);
    }

    pthread_join (fir_thread, (void **) NULL);
    pthread_join (sec_thread, (void **) NULL);

    fclose (fd);
}

//=============================================================================================================

void* log_in_file (void* fd_ptr)
{   
    struct sembuf buf;
    buf.sem_flg = 0;
    buf.sem_num = 0;
    buf.sem_op = 1;

    if (semop (semid, &buf, 1) < 0)
    {
        fprintf (stderr, "error %d\n", __LINE__);
        exit (-1);    
    }

    FILE* fd = (FILE*) fd_ptr; 

    for (int i = 0; i < 10000; i++)
    {
        buf.sem_op = - 1;
        if (semop (semid, &buf, 1) < 0)
        {
            fprintf (stderr, "error %d\n", __LINE__);
            exit (-1);    
        }

        fprintf (fd, "%d Fran. I think i hear them. Stand, ho! Who is there?\n", i);
        fprintf (fd, "%d Mar. What, has this thing appear'd again to-night?\n", i);
        fprintf (fd, "%d Mar. Peace! Break thee off! Look where it comes again!\n", i);
        fprintf (fd, "%d Hor. In what particular thought to work i know not;\n", i);
        fprintf (fd, "%d I'll cross it, though it blast me. - stay illusion!\n", i);
        
        buf.sem_op = 1;
        if (semop (semid, &buf, 1) < 0)
        {
            fprintf (stderr, "error %d\n", __LINE__);
            exit (-1);    
        }
    }

    return NULL;
}

//=============================================================================================================