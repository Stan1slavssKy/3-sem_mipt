#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "executer.h"

//------------------------------------------------------------------------------------------------

int main (int argc, char** argv)
{
    char* file_name = console_input (argc, argv);
    assert (file_name);

    commands_init (file_name);

    return 0;   
}

//------------------------------------------------------------------------------------------------