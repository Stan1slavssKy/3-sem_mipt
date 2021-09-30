#include <stdio.h>        
#include <stdlib.h>                
#include <string.h>                
#include <sys/stat.h>              
#include <sys/types.h>                            
#include <ctype.h>
#include <assert.h>

#include "text.h"

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

char* read_file (char* file_name, int size_of_file)
{
    FILE* file = fopen (file_name, "rb");
    assert (file != NULL);

    char* file_buffer = (char*) calloc (size_of_file, sizeof(char));
    assert (file_buffer);

    fread  (file_buffer, sizeof (char), size_of_file, file);
    fclose (file);

    return file_buffer;
}

//------------------------------------------------------------------------------------------------

int counter_line (char* file_buffer)
{
    assert (file_buffer);

    char* beg_line     = file_buffer;
    char* end_line     = NULL;
    int   line_counter = 0;

    while ((end_line = strchr (beg_line, '\n')) != NULL)
    {
        beg_line = end_line + 1;
        line_counter++;
    }

    printf ("The number of rows is %d\n", line_counter);

    return line_counter;
}

//------------------------------------------------------------------------------------------------

int file_size (char* file_name)
{
    assert (file_name);

    struct stat information_buffer = {};

    stat (file_name, &information_buffer);
    printf ("Size of \"%s\" is: %ld bytes.\n", file_name, information_buffer.st_size);

    return information_buffer.st_size;
}

//------------------------------------------------------------------------------------------------

void input_inform (char* file_name, struct text* text_info)
{
    assert (file_name);
    assert (text_info);

    int  size_of_file = file_size (file_name);
    char* file_buffer = read_file (file_name, size_of_file);
    int   number_line = counter_line (file_buffer);

    text_info -> size_of_file = size_of_file;
    text_info -> number_line  = number_line;
    text_info -> file_buffer  = file_buffer;
}

//------------------------------------------------------------------------------------------------

void free_text_memory (struct text* text_info)
{
    assert (text_info);
    assert (text_info -> file_buffer);

    free (text_info -> file_buffer);   
    text_info -> file_buffer = NULL;
}

//------------------------------------------------------------------------------------------------