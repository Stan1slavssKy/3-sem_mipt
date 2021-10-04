#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <sys/wait.h>
#include "split.h"
#include <signal.h>
#include <time.h>

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
void  make_relative_execution_time (int* time_arr, int number_of_commands);

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
    make_relative_execution_time (cmd.working_time, str.number_words);
    
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
        
        int time = atoi (str -> words[i]);

        cmd -> working_time[i] = time ? time : -1;
    }
}

//------------------------------------------------------------------------------------------------

void execute (struct command* cmd, int number_of_commands)
{
    for (int i = 0; i < number_of_commands; i++)
    {
        int time = cmd -> working_time[i];
        int if_timer = 0;

        pid_t pid = fork ();
        if (pid == 0)
        {
            if (time >= 0)
            {
                printf ("%d\n", time);
                sleep (time);
                if_timer++;
            }
            
            execvp (cmd -> cmd_arr[i].words[if_timer], cmd -> cmd_arr[i].words + if_timer);
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
// TODO: доделайте ещё проверку, что команда не должна работать дольше, чем заранее оговоренное время, например, 5 сек. Для проверки можете сами написать программу с одной строчкой
// sleep(10); в теле main и убедиться, что соответствующий процесс будет "убит" через 5 сек.

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

void make_relative_execution_time (int* time_arr, int number_of_commands)
{
    assert (time_arr);

    for (int i = 0; i < number_of_commands - 1; i++)
    {
        if (time_arr[i] == time_arr[i + 1])
        {
            time_arr[i + 1] = time_arr[i + 1] - time_arr[i];
            i++;

            while (time_arr[i] == time_arr[i + 1])
            {
                time_arr[i + 1] = 0;
                i++;
            }
        }
        else if (time_arr[i] < time_arr[i + 1])
        {
            time_arr[i + 1] = time_arr[i + 1] - time_arr[i];
        }
        else
        {
            fprintf (stderr, "error %d\n", __LINE__);
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