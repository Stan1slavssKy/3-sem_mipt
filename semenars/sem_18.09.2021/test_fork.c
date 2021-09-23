#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
    int N = 10;

    for (int i = 0; i < N; ++i)
    {
        pid_t pid = fork ();
        
        if (pid == 0)
        {
            int status = 0;
            int pid = wait (&status);
            printf ("getppid = %d pid = %d status = %d\n", getppid (), pid, status); 
            exit (EXIT_SUCCESS);
        }
    }

    return 0;
}