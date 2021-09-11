#include "split.h"

//==================================================================================

void split (struct string* str, char* string, char* space_characters)
{
    if (string == NULL)
    {
        printf ("you didn't enter a string.\n");
        return;
    }
    if (space_characters == NULL)
    {
        printf ("you didn't enter space_characters.\n");
        return;
    }

    str -> words = (char**) calloc (MAX_NMB_WORDS, sizeof (char*));
    assert (str -> words);

    char* lexem = strtok (string, space_characters);

    while (lexem != NULL)
    {
        str -> words[str -> nmb_wrds++] = lexem;
        lexem = strtok (NULL, space_characters);
    }
}

//==================================================================================

void print_reslt (struct string* str)
{
    printf ("=======RESULT=======\n");
    printf ("number of words: %d\n", str -> nmb_wrds);
    printf ("words:\n");

    for (int i = 0; i < str -> nmb_wrds; i++)
    {
        printf ("[%s]\n", str -> words[i]);
    }
    
    printf ("====================\n");
}

//==================================================================================

void free_memory (struct string* str)
{
    free (str -> words);
    str -> words = NULL;
}

//==================================================================================