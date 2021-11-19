#define _GNU_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include <pthread.h>
#include <time.h>
#include <dirent.h>
#include <string.h>

//========================================================================================================

const size_t MAX_FOUND_PATH_NUMBER = 100;
const size_t MAX_FOUND_PATH_LENGTH = 1000; 

void find_file(char* file_name, char* cur_dir, int depth, int* found_files_counter, char** found_path);

//========================================================================================================

int main()
{
    char current_dir[]       = "/home/stanislav/C_prog/3-sem_mipt/Homework";
    char file_name[]         = "file_finder.c";
    int  depth               = 10;
    int  found_files_counter = 0;

    char** found_path = (char**)calloc(MAX_FOUND_PATH_NUMBER, sizeof(char*));
    assert(found_path);

    find_file(file_name, current_dir, 10, &found_files_counter, found_path);

    if(found_files_counter > 0)
    {
        for(int idx = 0; idx < found_files_counter; idx++)
        {
            printf("%s\n", found_path[idx]);
            free(found_path[idx]);
        }
    }
    else
    {
        printf("No file named \"%s\" found.\n", file_name);
    }

    free(found_path);

    return 0;
}

//========================================================================================================

void find_file(char* file_name, char* cur_dir, int depth, int* found_files_counter, char** found_path)
{
    assert(file_name);
    assert(cur_dir);
    assert(found_path);

    if(depth <= 0)
    {
        fprintf(stderr, "depth <= 0\n");
        return;
    }

    struct dirent* file;

    DIR* dir = opendir(cur_dir);
    assert(dir);

    while((file = readdir(dir)) != NULL)
    {    
        if (strcmp(file->d_name, "..") && strcmp(file->d_name, "."))
        {
            char* new_dir = (char*)calloc(MAX_FOUND_PATH_LENGTH, sizeof(char));
            assert(new_dir);

            strcpy(new_dir, cur_dir);
            strcat(new_dir, "/");
            strcat(new_dir, file->d_name);
            
            if (file->d_type == DT_DIR)
            {
                find_file(file_name, new_dir, depth - 1, found_files_counter, found_path);
                free(new_dir);
            }
            else
            {
                if (!strcmp(file_name, file->d_name))
                {
                    found_path[*found_files_counter] = new_dir;
                    (*found_files_counter)++;
                }
                else
                {
                    free(new_dir);  
                }
            }
        }
    }

    closedir(dir);
}

//========================================================================================================
