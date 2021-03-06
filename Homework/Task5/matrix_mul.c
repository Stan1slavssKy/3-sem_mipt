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

//==================================================================================================================

struct matrix
{
    double* data;
    size_t size;
};

enum choice_mul
{
    WITH_THREADS    = 1,
    WITHOUT_THREADS = 0
};

const double RAND_INT_TO_DOUBLE = 0.7;
const int    THREADS_NUMBER     = 100;

void create_multipliable_matrices(size_t matrix_size, int choice_mul);
void input_matrix_data(struct matrix* matrix);
void print_matrix(struct matrix* matrix);
void free_matrix_memory(struct matrix* matrix);
void matrix_mul(struct matrix* fir_matrix, struct matrix* sec_matrix);
struct matrix thread_matrix_mul(struct matrix* fir_matrix, struct matrix* sec_matrix);

//==================================================================================================================

int main()
{
    size_t matrix_size = 500;
    
    printf ("Let's measure the multiplication time of a square matrix %d x %d\n", matrix_size, matrix_size);
    printf ("Without threads: ");

    create_multipliable_matrices(matrix_size, WITHOUT_THREADS);

    printf ("Using   threads: ");
    printf ("\n");

    create_multipliable_matrices(matrix_size, WITH_THREADS);

    return 0;
}

//==================================================================================================================

void create_multipliable_matrices(size_t matrix_size, int choice_mul)
{
    struct matrix fir_matrix = {};
    struct matrix sec_matrix = {};

    fir_matrix.size = matrix_size;
    sec_matrix.size = matrix_size;

    input_matrix_data(&fir_matrix);
    input_matrix_data(&sec_matrix);

    if (choice_mul)
    {
        thread_matrix_mul(&fir_matrix, &sec_matrix);
    }
    else
    {
        matrix_mul(&fir_matrix, &sec_matrix);
    }

    free_matrix_memory(&fir_matrix);
    free_matrix_memory(&sec_matrix);
}

void input_matrix_data(struct matrix* matrix)
{
    assert(matrix);

    size_t size = matrix->size;
    if (size > 0)
    {
        matrix->data = (double*)calloc(size * size, sizeof(double));
        assert(matrix->data);
    }
    else
    {
        fprintf(stderr, "Error size <= 0\n");
        return;
    }

    for (size_t i = 0; i < size * size; i++)
    {
        matrix->data[i] = RAND_INT_TO_DOUBLE * (double)(rand() % 10);
    }
}

void print_matrix(struct matrix* matrix)
{
    assert(matrix);
    
    size_t size = matrix->size;

    printf("\n");
    for (size_t line = 0; line < size; line++)
    {
        for (size_t i = 0; i < size; i++)
        {
            printf("%lf ", matrix->data[line * size + i]);
        }
        printf("\n");
    }
    printf("\n");
}

void matrix_mul(struct matrix* fir_matrix, struct matrix* sec_matrix)
{
    assert (fir_matrix);
    assert (sec_matrix);

    size_t size = fir_matrix -> size;
    struct matrix result_matrix = {};

    result_matrix.data = (double*) calloc (size * size, sizeof(double));
    assert (result_matrix.data);

    result_matrix.size = size;

    clock_t start_mul = clock();

    for (size_t line = 0; line < size; line++)
    {
        for (size_t column = 0; column <  size; column++)
        {        
            double temp = 0;
            
            for (size_t i = 0; i < size; i++)
            {
                temp = temp + fir_matrix->data[line * size + i] * sec_matrix->data[column + i * size];
            }

            result_matrix.data[line * size + column] = temp;
        }
    }

    clock_t end_mul = clock();
    printf ("%lf\n", (double)(end_mul - start_mul) / CLOCKS_PER_SEC);

    free_matrix_memory(&result_matrix);
}

void free_matrix_memory(struct matrix* matrix)
{
    assert(matrix);
    assert(matrix->data);

    free(matrix->data);
    matrix->data = NULL;
}

//==================================================================================================================
/*
struct matrix thread_matrix_mul(struct matrix* fir_matrix, struct matrix* sec_matrix)
{
    assert(fir_matrix);
    assert(sec_matrix);

    int N = fir_matrix->size;
    
    struct matrix result_matrix = {};
    size_t thread_counter = 0;

    for(int i = 0; i < N; i++)
    {
        pthread_t thid = 0;
        pthread_create(&thid, (pthread_attr_t*) NULL, thread_mul, &result_matrix);
        
        thread_counter++;
    }

    return result_matrix;
}

//==================================================================================================================

void thread_mul(struct matrix* result_matrix)
{
    assert(result_matrix);

    for()
    {

    }
}
*/