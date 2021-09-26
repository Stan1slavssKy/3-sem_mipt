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

// я бы в вашем случае объединил char** words и int number_of_words в одну структуру, т.к. они вместо образуют output ф-и
// но output зависит не только от input_str, но ещё и от delimeters. поэтому включать input_str в структуру не очень правильно.
struct string 
{
    char*  input_str;
    char** words;
    // сейчас в средах разработки есть автодополнение, поэтому экономить на символах не стоит
    int    nmb_wrds;
};

//==================================================================================

void print_reslt (struct string* str);
void split       (struct string* str, char* delimiters);
void get_line    (struct string* str);
void free_split_str_memory (struct string* str);

//==================================================================================

#endif
