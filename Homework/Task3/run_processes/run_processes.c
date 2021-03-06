#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>

#include "split.h"

//------------------------------------------------------------------------------------------------

#define TIMEOUT 5

//------------------------------------------------------------------------------------------------

struct command
{
    char*  string;
    int*   working_time;
    struct string* cmd_arr;
};

//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[]);
void  make_buffer_from_file (char* file_name, struct command* cmd, struct string* str);
void  parsing_buffer (struct command* cmd, struct string* str);
void  execute        (struct command* cmd, int number_of_commands);
void  free_memory    (struct command* cmd, struct string* str);
void  sorting_working_time (struct command* cmd, int number_of_commands);
void  swap_times (int* fir_time, int* sec_time);
void  swap_struct_str (struct string* fir_str, struct string* sec_str);

//------------------------------------------------------------------------------------------------

int main (int argc, char** argv)
{
    char* file_name = console_input (argc, argv);
    assert (file_name);

    struct command cmd = {0};
    struct string  str = {0};

    make_buffer_from_file (file_name, &cmd, &str);
    parsing_buffer (&cmd, &str);
    sorting_working_time (&cmd, str.number_words);
    //make_relative_execution_time (cmd.working_time, str.number_words);
    
    execute (&cmd, str.number_words);
    
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

    cmd -> working_time = (int*) calloc (str -> number_words, sizeof (int));
    assert (cmd -> working_time);

    for (int i = 0; i < str -> number_words; i++)
    {
        split (cmd_arr + i, str -> words[i], " ");
        cmd -> working_time[i] = atoi (str -> words[i]);
    }
}

//------------------------------------------------------------------------------------------------

void execute (struct command* cmd, int number_of_commands)
{
    pid_t* pid_arr = (pid_t*) calloc (number_of_commands, sizeof (pid_t));
    assert (pid_arr);

    for (int i = 0; i < number_of_commands; i++)
    {
        int time = cmd -> working_time[i];

        pid_t pid1 = fork ();
        if (pid1 == 0)
        {
            pid_t pid2 = fork ();
            if (pid2 == 0)
            {
                sleep (time + TIMEOUT);
                kill (getppid(), SIGINT);
                exit (0);
            }
            else
            {
                sleep (time);
                if (time == 0)
                {
                    execvp (cmd -> cmd_arr[i].words[0], cmd -> cmd_arr[i].words);
                }
                else 
                {
                    execvp (cmd -> cmd_arr[i].words[1], cmd -> cmd_arr[i].words + 1);
                }
                exit (-1);
            }
        }
        pid_arr[i] = pid1;
    }

    for (size_t i = 0; i < number_of_commands; i++)
    {
        int status = 0;
        waitpid (pid_arr[i], &status, WUNTRACED);
    }

    free (pid_arr);
}

//------------------------------------------------------------------------------------------------

void sorting_working_time (struct command* cmd, int number_of_commands)
{
    int* time_arr = cmd -> working_time;

    for (int idx_1 = 0; idx_1 < number_of_commands; idx_1++)
    {
        for (int idx_2 = 0; idx_2 < number_of_commands - idx_1 - 1; idx_2++)
        {
            if (time_arr[idx_2] > time_arr[idx_2 + 1])
            {
                swap_times (&time_arr[idx_2], &time_arr[idx_2 + 1]);
                swap_struct_str (&cmd -> cmd_arr[idx_2], &cmd -> cmd_arr[idx_2 + 1]);
            }
        }   
    }    
}

//------------------------------------------------------------------------------------------------

void swap_times (int* fir_time, int* sec_time)
{
    int temp = *fir_time;
    *fir_time = *sec_time;
    *sec_time = temp;
}

//------------------------------------------------------------------------------------------------

void swap_struct_str (struct string* fir_str, struct string* sec_str)
{
    struct string temp = *fir_str;
    *fir_str = *sec_str;
    *sec_str = temp;  
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