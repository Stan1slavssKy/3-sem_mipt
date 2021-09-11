#include "split.h"

//==================================================================================

int main ()
{
    struct string str = {};
    
    char input_string[] = "I have beautiful laptop";

    split       (&str, input_string, " \t");
    print_reslt (&str);
    free_memory (&str);

    return 0;   
}

//==================================================================================