#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>

void client_1 ();

int main ()
{
    (void) umask (0);

    if(mknod("fir_fifo", S_IFIFO | 0666, 0) == - 1)
    {
        if (errno != EEXIST)
        {
            fprintf (stderr, "Cant create fifo %d\n", __LINE__);
        }
    }

    if(mknod("sec_fifo", S_IFIFO | 0666, 0) == - 1)
    {
        if (errno != EEXIST)
        {
            fprintf (stderr, "Cant create fifo %d\n", __LINE__);
        }
    }

    client_1 ();
}

void client_1 ()
{
    pid_t pid = fork ();
    if (pid == 0)
    {
        int fd1 = open ("fir_fifo", O_WRONLY);
        
        char buffer[1000] = {};
        while (1)
        {
            fgets (buffer, 1000, stdin);
            write (fd1, buffer, 1000);
        }
        
        close (fd1);
    }
    else if (pid > 0)
    {
        int fd2 = open ("sec_fifo", O_RDONLY);
        
        char buffer[1000] = {};
        while (1)
        {
            read (fd2, buffer, 1000);
            printf ("%s\n", buffer);
        }

        close (fd2);
    }
    else if (pid == -1)
    {
        fprintf (stderr, "fork error %d", __LINE__);
        exit (0);
    }
}