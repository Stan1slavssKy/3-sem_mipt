#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>
#include <stdlib.h>

#define READ_LEN 10

void print_pieces_of_file ();

int main ()
{
    print_pieces_of_file ();

    return 0;
}

void print_pieces_of_file ()
{
    int f_descr = open ("test", O_RDONLY);
    if (f_descr == -1)
        fprintf (stderr, "Error cant open file\n");

    char* buffer = (char*) calloc (READ_LEN, sizeof (char));
    assert (buffer);

    int read_status = 0;
    while ((read_status = read (f_descr, buffer, READ_LEN)) != 0)
    {
        write (0, buffer, read_status);
        printf ("\n");
    }

    close (f_descr);
    free (buffer);
}