#include "split.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//==================================================================================

#define TEST_OFF

//==================================================================================

void split (struct string* str, char* input_string, char* delimiters)
{
    if (delimiters == NULL)
        fprintf (stderr, "You didn't enter delimiters.\n");

    str -> words = (char**) calloc (MAX_NMB_WORDS, sizeof (char*));
    assert (str -> words);

    char* lexem = strtok (input_string, delimiters);
    
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

char* get_line (struct string* str)
{
    char* input_string = (char*) calloc (MAX_NMB_SYMB, sizeof (char));
    assert (input_string);

    printf ("Please enter a string.\n");
    input_string = fgets (input_string, MAX_NMB_SYMB, stdin);
    
    if (input_string == NULL)
        fprintf (stderr, "Error in fgets, %d", __LINE__);

    input_string [strlen (input_string) - 1] = '\0';

    return input_string;
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
}

//==================================================================================