#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

pid_t child_pid;

void handler1 ();
void handler2 ();

int main ()
{
    signal (SIGUSR1, handler1);
    signal (SIGUSR2, handler2);

    pid_t pid = fork();
    if (pid == 0)
    {
        while (1);
    }
    else
    {
        child_pid = pid;
        kill (child_pid, SIGUSR2);

		while (1);
    }

    return 0;
}

void handler1 ()
{
	printf ("RT\n");
	kill (child_pid, SIGUSR2);
}

void handler2 ()
{
	printf ("Champion!\n");
	kill (getppid (), SIGUSR1);
}