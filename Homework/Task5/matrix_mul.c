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

//================================================================

struct matrix
{
    double* data;
    size_t size;
};

const double RAND_INT_TO_DOUBLE = 0.7;

void create_multipliable_matrices(size_t matrix_size);
void input_matrix_data(struct matrix* matrix);
void print_matrix(struct matrix* matrix);
void free_matrix_memory(struct matrix* matrix);
struct matrix matrix_mul(struct matrix* fir_matrix, struct matrix* sec_matrix);

//================================================================

int main()
{
    size_t matrix_size = 700;
    
    create_multipliable_matrices(matrix_size);
    
    printf ("gg\n");
    return 0;
}

//================================================================

void create_multipliable_matrices(size_t matrix_size)
{
    struct matrix fir_matrix = {};
    struct matrix sec_matrix = {};

    fir_matrix.size = matrix_size;
    sec_matrix.size = matrix_size;

    input_matrix_data(&fir_matrix);
    input_matrix_data(&sec_matrix);

    struct matrix result = matrix_mul(&fir_matrix, &sec_matrix);

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

struct matrix matrix_mul(struct matrix* fir_matrix, struct matrix* sec_matrix)
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
    printf ("matrix mul = %lf\n", (double)(end_mul - start_mul) / CLOCKS_PER_SEC);

    return result_matrix;
}

void free_matrix_memory(struct matrix* matrix)
{
    assert(matrix);
    assert(matrix->data);

    free(matrix->data);
    matrix->data = NULL;
}

//================================================================