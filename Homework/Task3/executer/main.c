#include <stdio.h>
#include <stdlib.h>

#include "../text/text.h"
#include "../split/split.h"
#include "executer.h"

//------------------------------------------------------------------------------------------------

int main (int argc, char** argv)
{
    char* file_name = console_input (argc, argv);
    assert (file_name);

    struct text cmd_text = {};
    struct string str    = {};

    commands_init (&cmd_text, &str);

    return 0;   
}

//------------------------------------------------------------------------------------------------