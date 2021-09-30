#ifndef TEXT_TEXT_H_INCLUDED
#define TEXT_TEXT_H_INCLUDED

//------------------------------------------------------------------------------------------------

struct text
{
    int   size_of_file;
    int   number_line;
    char* file_buffer;
};

//------------------------------------------------------------------------------------------------

char* console_input (int argc, char* argv[]);
char* read_file     (char* file_name, int size_of_file);
int   file_size     (char* file_name);

void input_inform (char* file_name, struct text* text_info);
void free_text_memory  (struct text* text_info);

//------------------------------------------------------------------------------------------------

#endif 