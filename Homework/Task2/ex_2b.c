#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 
#include <sys/wait.h>

int main ()
{
    int N = 0;
   
    char test[100000];

    printf ("Please enter Number of processes: ");
    scanf ("%d", &N);

    for (int i = 0; i < N; i++)
    {
        size_t pid = fork ();
        if (pid == 0)
        {
            printf ("I was born %d, my parent is %d\n", getpid (), getppid ());
        }
        else if (pid > 0)
        {
            wait (NULL);
            printf ("My child completed, %d\n", pid);
            break;
        }
        else if (pid == -1)
        {
            fprintf (stderr, "Error");
        }
    }

    return 0;
}