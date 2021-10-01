#ifndef EXECUTER_EXECUTER_H_INCLUDED
#define EXECUTER_EXECUTER_H_INCLUDED

#include "../split/split.h"
#include "../text/text.h"

//------------------------------------------------------------------------------------------------

struct command
{
    char*  cmd_string;
    char** flags;
    int number_of_flags;
};

//------------------------------------------------------------------------------------------------

void executer (struct string* str, struct command* commands);
void commands_init (char* file_name);
void free_executer_memory (struct string* str, struct text* cmd_text);

//------------------------------------------------------------------------------------------------

#endif