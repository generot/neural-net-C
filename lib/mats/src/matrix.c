#include "matrix.h"

int mats_allocate_matrix(mats_matrix *mat, mats_size rows, mats_size cols) {
    mat->memptr = calloc(rows * cols, sizeof(mats_value));
    mat->cols = cols;
    mat->rows = rows;
    mat->is_valid = true;

    return 0;
}

void mats_free_matrix(mats_matrix *src) {
    if(!src->is_valid) {
        return;
    }

    free(src->memptr);

    *src = (mats_matrix){0};
}

mats_matrix mats_copy_matrix(mats_matrix src) {
    if(!src.is_valid) {
        return (mats_matrix){0};
    }

    mats_matrix copy = {0};
    mats_size sz = src.rows * src.cols;

    copy.rows = src.rows;
    copy.cols = src.cols;
    copy.memptr = malloc(sz * sizeof(mats_value));
    copy.is_valid = true;

    if(NULL == copy.memptr) {
        return (mats_matrix){0};
    }

    if(NULL == memcpy(copy.memptr, src.memptr, sz * sizeof(mats_value))) {
        return (mats_matrix){0};
    }

    return copy;
}

void mats_init_from_arr(mats_matrix *src, mats_value *arr) {
    for(mats_size row = 0; row < src->rows; row++) {
        for(mats_size col = 0; col < src->cols; col++) {
            mats_set_val(src, row, col, arr[col + row * src->cols]);
        }
    }
}

void mats_print_matrix(mats_matrix src) {
    if(!src.is_valid) {
        return;
    }

    for(mats_size row = 0; row < src.rows; row++) {
        printf("[");

        for(mats_size col = 0; col < src.cols; col++) {
            printf("%.3lf ", mats_get_val(&src, row, col));
        }

        printf("]\n");
    }
}

//These functions will be much more frequently called than the others, so a pass-by-reference seems to be the
//logically more optimal option for the matrix struct.
mats_value mats_get_val(mats_matrix *src, mats_size row, mats_size col) {
    if(!src->is_valid) {
        return ~0;
    }

    if(row >= src->rows) {
        return ~0;
    }

    if(col >= src->cols) {
        return ~0;
    }

    return src->memptr[col + row * src->cols];
}

void mats_set_val(mats_matrix *src, mats_size row, mats_size col, mats_value val) {
    if(!src->is_valid) {
        return;
    }

    if(row >= src->rows) {
        return;
    }

    if(col >= src->cols) {
        return;
    }

#ifdef __DEBUG__
    printf("Row: %u, Col: %u, Val: %lf\n", row, col, val);
#endif
    src->memptr[col + row * src->cols] = val;
}

//NON-ACCELERATED FUNCTIONS
mats_matrix mats_add(mats_matrix *A, mats_matrix *B) {
    if(!A->is_valid && !B->is_valid) {
        return (mats_matrix){0};
    }

    if(A->cols != B->cols || A->rows != B->rows) {
        return (mats_matrix){0};
    }

    mats_matrix new_mat = {0};

    if(-1 == mats_allocate_matrix(&new_mat, A->rows, A->cols)) {
        return (mats_matrix){0};
    }

    for(mats_size row = 0; row < A->rows; row++) {
        for(mats_size col = 0; col < A->cols; col++) { 
            mats_value sum = mats_get_val(A, row, col) + mats_get_val(B, row, col);
            mats_set_val(&new_mat, row, col, sum);
        }
    }

    return new_mat;
}

mats_matrix mats_mult(mats_matrix *A, mats_matrix *B) {
    if(!A->is_valid && !B->is_valid) {
        return (mats_matrix){0};
    }

    if(A->cols != B->rows) {
        return (mats_matrix){0};
    }

    mats_matrix new_mat = {0};

    if(-1 == mats_allocate_matrix(&new_mat, A->rows, B->cols)) {
        return (mats_matrix){0};
    }

    for(mats_size row = 0; row < A->rows; row++) {
        for(mats_size col = 0; col < B->cols; col++) {
            mats_value sum = 0;

            for(mats_size row_b = 0; row_b < B->rows; row_b++) {
                mats_value prod = mats_get_val(A, row, row_b) * mats_get_val(B, row_b, col);
                
                sum += prod;
            }

            mats_set_val(&new_mat, row, col, sum);
        }
    }

    return new_mat;
}

mats_matrix mats_scale(mats_matrix *A, mats_value scalar) {
    if(!A->is_valid) {
        return (mats_matrix){0};
    }

    mats_matrix new_mat = mats_copy_matrix(*A);

    if(!new_mat.is_valid) {
        return (mats_matrix){0};
    }

    for(mats_size row = 0; row < new_mat.rows; row++) {
        for(mats_size col = 0; col < new_mat.cols; col++) {
            mats_value scaled_val = scalar * mats_get_val(&new_mat, row, col);

            mats_set_val(&new_mat, row, col, scaled_val);
        }
    }

    return new_mat;
}
//NON-ACCELERATED FUNCTIONS

//(TO-BE-)GPU-ACCELERATED FUNCTIONS
mats_matrix mats_add_GPU(mats_matrix A, mats_matrix B) {
    (void)A;
    (void)B;

    assert(0 && "Unimplemented.");
}

mats_matrix mats_mult_GPU(mats_matrix A, mats_matrix B) {
    (void)A;
    (void)B;
    
    assert(0 && "Unimplemented.");
}

mats_matrix mats_scale_GPU(mats_matrix A, mats_value scalar) {
    (void)A;
    (void)scalar;
    
    assert(0 && "Unimplemented.");
}
//(TO-BE-)GPU-ACCELERATED FUNCTIONS