#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

//==================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

//==================================================================================

#define MAX_NMB_WORDS 1000
#define MAX_NMB_SYMB  1000

//==================================================================================

struct string 
{
    char*  input_str;
    char** words;
    int    nmb_wrds;
};

//==================================================================================

void print_reslt (struct string* str);
void split       (struct string* str, char* delimiters);
void get_line    (struct string* str);
void free_split_str_memory (struct string* str);

//==================================================================================

#endif