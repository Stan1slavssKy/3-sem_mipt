#ifndef EXECUTER_EXECUTER_H_INCLUDED
#define EXECUTER_EXECUTER_H_INCLUDED

//------------------------------------------------------------------------------------------------

void executer ();
void commands_init (struct text* cmd_text, struct string* str);
void free_executer_memory (struct string* str);

//------------------------------------------------------------------------------------------------

#endif