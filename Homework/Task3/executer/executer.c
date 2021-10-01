#include "executer.h"
#include <assert.h>

//------------------------------------------------------------------------------------------------

void commands_init (char* file_name)
{
    struct text cmd_text = {};
    struct string str    = {};

    input_inform (file_name, &cmd_text);
    assert (cmd_text.file_buffer);

    split (&str, cmd_text.file_buffer, "\n");
    executer (&str);

    free_executer_memory (&str, &cmd_text);
}

//------------------------------------------------------------------------------------------------

void executer (struct string* str)
{
    return;
}

//------------------------------------------------------------------------------------------------

void free_executer_memory (struct string* str, struct text* cmd_text)
{
    assert (str);
    assert (cmd_text);

    free_split_str_memory (str);
    free_text_memory (cmd_text);
}

//------------------------------------------------------------------------------------------------