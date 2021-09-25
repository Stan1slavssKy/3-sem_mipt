#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>

void pipe_sum ();

int main ()
{
    pipe_sum ();
    return 0;
}

void pipe_sum ()
{
    int fd1[2] = {};
    int fd2[2] = {};

    int a = 0;
    int b = 0;
    int res = 0;

    if (pipe (fd1) < 0)
    {
        fprintf (stderr, "Cant create pipe\n");
        exit (-1);
    }
    if (pipe (fd2) < 0)
    {
        fprintf (stderr, "Cant create pipe\n");
        exit (-1);
    }

    size_t pid = fork ();

    if (pid != 0)
    {
        a = 2;
        b = 3;

        close (fd1[0]);
        close (fd2[1]);

        write (fd1[1], &a, sizeof (a));
        write (fd1[1], &b, sizeof (b));

        read (fd2[0], &res, sizeof (res));
        printf ("%d\n", res);
    }
    else if (pid == 0)
    {
        read (fd1[0], &a, sizeof (a));
        read (fd1[0], &b, sizeof (b));

        res = a + b;

        write (fd2[1], &res, sizeof (res));
    }
    else 
        fprintf (stderr, "fork error\n");
}