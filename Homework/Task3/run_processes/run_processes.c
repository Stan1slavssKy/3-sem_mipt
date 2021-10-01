#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <sys/wait.h>
#include "split.h"

//------------------------------------------------------------------------------------------------

struct command
{
    char*  string;
    int    working_time;
    struct string* cmd_arr;
};

//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[]);
void make_buffer_from_file (char* file_name, struct command* cmd, struct string* str);
void parsing_buffer (struct command* cmd, struct string* str);
void executer  (struct command* cmd, struct string* str);
void free_memory (struct command* cmd, struct string* str);

//------------------------------------------------------------------------------------------------

int main (int argc, char** argv)
{
    char* file_name = console_input (argc, argv);
    assert (file_name);

    struct command cmd = {};
    struct string  str = {};

    make_buffer_from_file (file_name, &cmd, &str);
    parsing_buffer (&cmd, &str);
    executer (&cmd, &str);
    
    free_memory (&cmd, &str);

    return 0;   
}

//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[])
{
    char* file_name = NULL;

    if (argc == 2)
    {
        file_name = argv[1];
        printf ("You want read \"%s\"\n", file_name);
        return file_name;
    }
    if (argc == 1)
    {
        printf ("You didn't enter the file name. Please return program and enter file name.\n");
        return NULL;
    }
    
    printf ("Error: to few or too many arguments.\n");
    return NULL;
}

//------------------------------------------------------------------------------------------------

void make_buffer_from_file (char* file_name, struct command* cmd, struct string* str)
{
    int number_of_file_bytes = MAX_NMB_SYMB;
    int file_descriptor = open (file_name, O_RDONLY);

    char* buffer = (char*) calloc (number_of_file_bytes, sizeof(char));
    assert (buffer);

    read (file_descriptor, buffer, number_of_file_bytes);
    cmd -> string = buffer;

    close (file_descriptor);
}

//------------------------------------------------------------------------------------------------

void parsing_buffer (struct command* cmd, struct string* str)
{
    split (str, cmd -> string, "\n");

    struct string* cmd_arr = (struct string*) calloc (str -> number_words, sizeof (struct string));
    assert (cmd_arr);

    cmd -> cmd_arr = cmd_arr;

    for (int i = 0; i < str -> number_words; i++)
    {
        split (cmd_arr + i, str -> words[i], " ");
    }
}

//------------------------------------------------------------------------------------------------

void executer (struct command* cmd, struct string* str)
{
    for (int i = 0; i < str -> number_words; i++)
    {
        pid_t pid = fork ();
        if (pid == 0)
        {
            execvp (str -> words[i], cmd -> cmd_arr[i].words);
        }
        else if (pid > 0)
        {
            wait (NULL);
        }
        else if (pid == -1)
        {
            fprintf (stderr, "fork error %d\n", __LINE__);
        }
    }
}

//------------------------------------------------------------------------------------------------

void free_memory (struct command* cmd, struct string* str)
{   
    for (int i = 0; i < str -> number_words; i++)
    {
        free_split_str_memory (&cmd -> cmd_arr[i]);
    }

    free_split_str_memory (str);
    free (cmd -> cmd_arr);
    free (cmd -> string);
}

//------------------------------------------------------------------------------------------------