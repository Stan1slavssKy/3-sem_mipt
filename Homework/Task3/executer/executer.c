#include "executer.h"
#include <assert.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

//------------------------------------------------------------------------------------------------

#define PROGRAM_WORKING_TIME 5
#define MAX_NUMBER_FLAGS 1000

//------------------------------------------------------------------------------------------------

void commands_init (char* file_name)
{
    struct text cmd_text = {};
    struct string str    = {};

    input_inform (file_name, &cmd_text);
    assert (cmd_text.file_buffer);

    split (&str, cmd_text.file_buffer, "\n");

    struct command cmd = {};
    
    struct command* commands = (struct command*) calloc (str.number_words, sizeof (struct command)); //создал массив из 
    assert (commands);

    executer (&str, commands);

    free_executer_memory (&str, &cmd_text);
}

//------------------------------------------------------------------------------------------------

void executer (struct string* str, struct command* commands)
{
    assert (str);
    assert (commands);

    char* string = NULL;

    for (int i = 0; i < str -> number_words; i++)
    {
        string = str -> words [i];
        
        for (int idx = 0; string[idx] != '\0'; idx++)
        {
            commands[i].flags = (char*) calloc (MAX_NUMBER_FLAGS, sizeof (char*));
            commands[i].cmd_string = string;
            
            if (idx == 0)
            {
                commands[i].flags [commands[i].number_of_flags] = string + idx;
            }
            if (string[idx] == ' ')
            {
                commands[i].flags [commands[i].number_of_flags] = string + idx + 1;
                commands[i].number_of_flags++;
                string[idx] = '\0';
            }    
        }
    }

//    execlp ();
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