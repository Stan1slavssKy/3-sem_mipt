#ifndef EXECUTER_EXECUTER_H_INCLUDED
#define EXECUTER_EXECUTER_H_INCLUDED

#include "../split/split.h"
#include "../text/text.h"

//------------------------------------------------------------------------------------------------

void executer (struct string* str);
void commands_init (char* file_name);
void free_executer_memory (struct string* str, struct text* cmd_text);

//------------------------------------------------------------------------------------------------

#endif