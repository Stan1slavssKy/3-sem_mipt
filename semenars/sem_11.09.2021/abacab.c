#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#define ASCII_SYM_A 'a'

void generate_string (int n, char* out_string);

int main ()
{
    int n = 0;

    printf ("Enter length of output line.\n");
    scanf ("%d", &n);

    char* out_string = (char*) calloc (1 << (n + 1) - 1, sizeof (char));
    assert (out_string);

    generate_string (n, out_string);
    printf ("out is [%s]\n", out_string);

    free (out_string);

    return 0;
}

void generate_string (int n, char* out_string)
{
    assert (out_string);

    char  temp_sym = ASCII_SYM_A;

    char* temp_str = (char*) calloc (1 << (n + 1) - 1, sizeof (char));
    assert (temp_str);

    strcpy (temp_str, "a");

    if (n == 0)
        strcpy (out_string, temp_str);

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        {
            strcpy (out_string, temp_str);
        }

        strcpy (temp_str, out_string);
        out_string [strlen(out_string)] = ++temp_sym;
        strcat (out_string, temp_str);  
    }
}