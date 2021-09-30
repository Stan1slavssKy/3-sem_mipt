#include "executer.h"
#include "../split/split.h"

//------------------------------------------------------------------------------------------------

void commands_init (struct text* cmd_text, struct string* str)
{
    split (str, "\n");
    
    
    free_executer_memory (str);
}

//------------------------------------------------------------------------------------------------

void executer ()
{
    commands_init ();
}

//------------------------------------------------------------------------------------------------

void free_executer_memory (struct string* str)
{
    free_split_str_memory (str);
}

//------------------------------------------------------------------------------------------------