#ifndef LIBS_SPLIT_H_INCLUDED
#define LIBS_SPLIT_H_INCLUDED

//==================================================================================

#define MAX_NMB_WORDS 1000
#define MAX_NMB_SYMB  1000

//==================================================================================

struct string 
{
    char** words;
    int    number_words;
    char*  beg_ptr;
};

//==================================================================================

void print_reslt (struct string* str);
void split       (struct string* str, char* input_string, char* delimiters);
char* get_line    (struct string* str);
void free_split_str_memory (struct string* str);

//==================================================================================

#endif
