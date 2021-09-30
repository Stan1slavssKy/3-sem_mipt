#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//==================================================================================

#define TEST_ON

//==================================================================================

void split (struct string* str, char* delimiters)
{
    if (delimiters == NULL)
        fprintf (stderr, "You didn't enter delimiters.\n");

    str -> words = (char**) calloc (MAX_NMB_WORDS, sizeof (char*));
    assert (str -> words);

    char* lexem = strtok (str -> input_str, delimiters);
    
    while (lexem != NULL)
    {
        str -> words[str -> number_words++] = lexem;
        lexem = strtok (NULL, delimiters);
    }

    #ifdef TEST_ON
        print_reslt (str);
    #endif
}

//==================================================================================

void get_line (struct string* str)
{
    str -> input_str = (char*) calloc (MAX_NMB_SYMB, sizeof (char));
    assert (str -> input_str);

    printf ("Please enter a string.\n");
    str -> input_str = fgets (str -> input_str, MAX_NMB_SYMB, stdin);
    
    if (str -> input_str == NULL)
        fprintf (stderr, "Error in fgets, %d", __LINE__);

    str -> input_str [strlen (str -> input_str) - 1] = '\0';
}

//==================================================================================

void print_reslt (struct string* str)
{
    printf ("=======RESULT=======\n");
    printf ("number of words: %d\n", str -> number_words);
    printf ("words:\n");

    for (int i = 0; i < str -> number_words; i++)
    {
        printf ("[%s]\n", str -> words[i]);
    }
    
    printf ("====================\n");
}

//==================================================================================

void free_split_str_memory (struct string* str)
{
    free (str -> words);
    str -> words = NULL;

    free (str -> input_str);
    str -> input_str = NULL;
}

//==================================================================================