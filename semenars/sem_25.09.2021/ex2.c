#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>

void pipe_length ();

int main ()
{
    pipe_length ();
    return 0;
}

void pipe_length ()
{
    int fd[2] = {};

    if (pipe (fd) < 0)
    {
        fprintf (stderr, "Cant create pipe\n");
        exit (-1);
    }

    const char buf[] = "a";
    
    int pipe_len = 0; 

    while (1)
    {
        write (fd[1], buf, 1);
        pipe_len++;
        printf ("%d\n", pipe_len);
    }

    printf ("%d", pipe_len);
}