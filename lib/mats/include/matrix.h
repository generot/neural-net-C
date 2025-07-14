#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

typedef struct mats_matrix mats_matrix;
typedef double mats_value;
typedef uint32_t mats_size;

struct mats_matrix {
    bool is_valid;

    mats_value *memptr;

    mats_size cols;
    mats_size rows;
};

int mats_allocate_matrix(mats_matrix *out, mats_size rows, mats_size cols);
void mats_free_matrix(mats_matrix *src);
void mats_print_matrix(mats_matrix src);
//Matrix must be allocated before calling this function.
void mats_init_from_arr(mats_matrix *src, mats_value *arr);
void mats_set_val(mats_matrix *src, mats_size row, mats_size col, mats_value val);
mats_value mats_get_val(mats_matrix *src, mats_size row, mats_size col);
mats_matrix mats_copy_matrix(mats_matrix src);

//NON-ACCELERATED FUNCTIONS
mats_matrix mats_add(mats_matrix *A, mats_matrix *B);
mats_matrix mats_mult(mats_matrix *A, mats_matrix *B);
mats_matrix mats_scale(mats_matrix *A, mats_value scalar);
//NON-ACCELERATED FUNCTIONS

//(TO-BE-)GPU-ACCELERATED FUNCTIONS
mats_matrix mats_add_GPU(mats_matrix A, mats_matrix B);
mats_matrix mats_mult_GPU(mats_matrix A, mats_matrix B);
mats_matrix mats_scale_GPU(mats_matrix A, mats_value scalar);
//(TO-BE-)GPU-ACCELERATED FUNCTIONS

#endif // __MATRIX_H__