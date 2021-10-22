#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>

//=============================================================================================================

int   processes_console_data (int argc, char** argv);
char* console_input          (int argc, char** argv);
void* read_message           (void* fifo_name);
void* write_message          (void* fifo_name);
void  create_client_thread   (int client_number);

enum bool 
{
    true = 1,
    false = 0
};

char FIRST_FIFO []  = "fifo_1_to_2";
char SECOND_FIFO[]  = "fifo_2_to_1";

#define MAX_MESSAGE_LEN 1000

//=============================================================================================================

int main (int argc, char** argv)
{
    create_client_thread (processes_console_data (argc, argv)); 

    return 0;
}

//=============================================================================================================

void create_client_thread (int client_number)
{
    char* fir_fifo_name = NULL;
    char* sec_fifo_name = NULL;

    if (client_number == 1)
    {
        fir_fifo_name = FIRST_FIFO;
        sec_fifo_name = SECOND_FIFO;
    }
    else if (client_number == 2)
    {
        fir_fifo_name = SECOND_FIFO;
        sec_fifo_name = FIRST_FIFO;
    }
    else 
    {
        fprintf (stderr, "error client name\n");
    }

    umask (0);

    if (mknod (fir_fifo_name, S_IFIFO | 0666, 0) == - 1)
    {
        if (errno != EEXIST)
        {
            fprintf (stderr, "Cant create fifo %d\n", __LINE__);
        }
    }
    if (mknod (sec_fifo_name, S_IFIFO | 0666, 0) == - 1)
    {
        if (errno != EEXIST)
        {
            fprintf (stderr, "Cant create fifo %d\n", __LINE__);
        }
    }

    pthread_t fir_thread = 0;
    pthread_t sec_thread = 0;

    if (pthread_create (&fir_thread, (pthread_attr_t*) NULL, read_message, (void*)fir_fifo_name))
    {
        fprintf (stderr, "error in pthread_create, %d\n", __LINE__);
    }

    if (pthread_create (&sec_thread, (pthread_attr_t*) NULL, write_message, (void*)sec_fifo_name))
    {
        fprintf (stderr, "error in pthread_create, %d\n", __LINE__);
    }

    pthread_join (fir_thread, (void **) NULL);
    pthread_join (sec_thread, (void **) NULL);
}

//=============================================================================================================

void* read_message (void* fifo_name)
{
    assert (fifo_name);

    int fd = open ((char*)fifo_name, O_RDONLY);
    char buffer [MAX_MESSAGE_LEN] = {};

    while (true)
    {
        read (fd, buffer, MAX_MESSAGE_LEN);
        printf ("%s", buffer);
    }
    
    close (fd);
    return NULL;
}

void* write_message (void* fifo_name)
{
    assert (fifo_name);

    int fd = open ((char*) fifo_name, O_WRONLY);
    char buffer [MAX_MESSAGE_LEN] = {};

    while (true)
    {
        fgets (buffer, MAX_MESSAGE_LEN, stdin);
        write (fd, buffer, MAX_MESSAGE_LEN);
    }
    
    close (fd);
    return NULL;
}

//=============================================================================================================

int processes_console_data (int argc, char** argv)
{
    char* cmd_name = console_input (argc, argv);
    assert (cmd_name);

    int client_number = atoi (cmd_name);
    printf ("%d client\n", client_number);
    
    return client_number;
}

char* console_input (int argc, char** argv)
{
    char* cmd_name = NULL;

    if (argc == 2)
    {
        cmd_name = argv[1];
        return cmd_name;
    }
    if (argc == 1)
    {
        fprintf (stderr, "You didn't enter the file name. Please return program and enter file name.\n");
        return NULL;
    }
    fprintf (stderr,"Error: to few or too many arguments.\n");
    return NULL;
}

//=============================================================================================================