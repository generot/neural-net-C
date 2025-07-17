#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct mt_matrix mt_matrix;
typedef double mt_value;
typedef uint64_t mt_size;
typedef mt_value (*mt_lambda)(mt_value);

struct mt_matrix {
    bool is_valid;

    mt_value *memptr;

    mt_size cols;
    mt_size rows;
};

int mt_allocate_matrix(mt_matrix *out, mt_size rows, mt_size cols);
void mt_free_matrix(mt_matrix *src);
void mt_print_matrix(mt_matrix src);
//Matrix must be allocated before calling this function.
void mt_init_from_arr(mt_matrix *src, mt_value *arr);
void mt_set_val(mt_matrix *src, mt_size row, mt_size col, mt_value val);
mt_value mt_get_val(mt_matrix *src, mt_size row, mt_size col);
mt_matrix mt_copy_matrix(mt_matrix *src);
mt_matrix mt_transpose(mt_matrix *src);
mt_matrix mt_apply_lambda(mt_matrix *src, mt_lambda lmb);

//NON-ACCELERATED FUNCTIONS
mt_matrix mt_add(mt_matrix *A, mt_matrix *B);
mt_matrix mt_mult(mt_matrix *A, mt_matrix *B);
mt_matrix mt_scale(mt_matrix *A, mt_value scalar);
//NON-ACCELERATED FUNCTIONS

//(TO-BE-)GPU-ACCELERATED FUNCTIONS
mt_matrix mt_add_GPU(mt_matrix A, mt_matrix B);
mt_matrix mt_mult_GPU(mt_matrix A, mt_matrix B);
mt_matrix mt_scale_GPU(mt_matrix A, mt_value scalar);
//(TO-BE-)GPU-ACCELERATED FUNCTIONS

#endif // __MATRIX_H__