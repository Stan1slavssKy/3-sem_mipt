#include "split.h"

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
        str -> words[str -> nmb_wrds++] = lexem;
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
    
    printf ("AAA {%s}\n", str -> input_str);
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

void free_split_str_memory (struct string* str)
{
    free (str -> words);
    str -> words = NULL;

    free (str -> input_str);
    str -> input_str = NULL;
}

//==================================================================================