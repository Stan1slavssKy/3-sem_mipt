#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{   
    int pid = fork ();

    if (pid == 0)
    {
        execlp ("gcc", "gcc", "hello_wrd.c", "-o", "hello", NULL);
    }
    else
    {  
        int source = 0;
        int pid    = wait (&source);
        execlp ("./hello", "./hello", NULL); 
    }
    
    return 0;
}
