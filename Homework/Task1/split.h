#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

//==================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//==================================================================================

#define MAX_NMB_WORDS 512

//==================================================================================

struct string 
{
    char** words;
    int    nmb_wrds;
};

//==================================================================================

void print_reslt (struct string* str);
void free_memory (struct string* str);
void split       (struct string* str, char* string, char* space_characters);

//==================================================================================

#endif