#include "matrix.h"

int mt_allocate_matrix(mt_matrix *mat, mt_size rows, mt_size cols) {
    mat->memptr = calloc(rows * cols, sizeof(mt_value));
    mat->cols = cols;
    mat->rows = rows;
    mat->is_valid = true;

    return 0;
}

void mt_free_matrix(mt_matrix *src) {
    if(!src->is_valid) {
        return;
    }

    free(src->memptr);

    *src = (mt_matrix){0};
}

mt_matrix mt_copy_matrix(mt_matrix *src) {
    if(!src->is_valid) {
        return (mt_matrix){0};
    }

    mt_matrix copy = {0};
    mt_size sz = src->rows * src->cols;

    copy.rows = src->rows;
    copy.cols = src->cols;
    copy.is_valid = true;
    copy.memptr = malloc(sz * sizeof(mt_value));

    if(NULL == copy.memptr) {
        return (mt_matrix){0};
    }

    if(NULL == memcpy(copy.memptr, src->memptr, sz * sizeof(mt_value))) {
        return (mt_matrix){0};
    }

    return copy;
}

void mt_init_from_arr(mt_matrix *src, mt_value *arr) {
    for(mt_size row = 0; row < src->rows; row++) {
        for(mt_size col = 0; col < src->cols; col++) {
            mt_set_val(src, row, col, arr[col + row * src->cols]);
        }
    }
}

void mt_print_matrix(mt_matrix src) {
    if(!src.is_valid) {
        return;
    }

    for(mt_size row = 0; row < src.rows; row++) {
        printf("[");

        for(mt_size col = 0; col < src.cols; col++) {
            printf("%.3lf ", mt_get_val(&src, row, col));
        }

        printf("]\n");
    }
}

//These functions will be much more frequently called than the others, so a pass-by-reference seems to be the
//logically more optimal option for the matrix struct.
mt_value mt_get_val(mt_matrix *src, mt_size row, mt_size col) {
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

void mt_set_val(mt_matrix *src, mt_size row, mt_size col, mt_value val) {
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

mt_matrix mt_transpose(mt_matrix *src) {
    if(!src->is_valid) {
        return (mt_matrix){0};
    }

    mt_matrix new_mat = {0};

    if(mt_allocate_matrix(&new_mat, src->cols, src->rows) != 0) {
        return (mt_matrix){0};
    }

    for(mt_size row = 0; row < new_mat.rows; row++) {
        for(mt_size col = 0; col < new_mat.cols; col++) {
            mt_value cross_val = mt_get_val(src, col, row);

            mt_set_val(&new_mat, row, col, cross_val);
        }
    }

    return new_mat;
}

mt_matrix mt_apply_lambda(mt_matrix *src, mt_lambda lmb) {
    if(!src->is_valid) {
        return (mt_matrix){0};
    }

    mt_matrix new_mat = mt_copy_matrix(src);

    for(mt_size row = 0; row < new_mat.rows; row++) {
        for(mt_size col = 0; col < new_mat.cols; col++) {
            mt_value val = mt_get_val(&new_mat, row, col);
            mt_value f_val = lmb(val);

            mt_set_val(&new_mat, row, col, f_val);
        }
    }

    return new_mat;
}

//NON-ACCELERATED FUNCTIONS
mt_matrix mt_add(mt_matrix *A, mt_matrix *B) {
    if(!A->is_valid && !B->is_valid) {
        return (mt_matrix){0};
    }

    if(A->cols != B->cols || A->rows != B->rows) {
        return (mt_matrix){0};
    }

    mt_matrix new_mat = {0};

    if(-1 == mt_allocate_matrix(&new_mat, A->rows, A->cols)) {
        return (mt_matrix){0};
    }

    for(mt_size row = 0; row < A->rows; row++) {
        for(mt_size col = 0; col < A->cols; col++) { 
            mt_value sum = mt_get_val(A, row, col) + mt_get_val(B, row, col);
            mt_set_val(&new_mat, row, col, sum);
        }
    }

    return new_mat;
}

mt_matrix mt_mult(mt_matrix *A, mt_matrix *B) {
    if(!A->is_valid && !B->is_valid) {
        return (mt_matrix){0};
    }

    if(A->cols != B->rows) {
        return (mt_matrix){0};
    }

    mt_matrix new_mat = {0};

    if(-1 == mt_allocate_matrix(&new_mat, A->rows, B->cols)) {
        return (mt_matrix){0};
    }

    for(mt_size row = 0; row < A->rows; row++) {
        for(mt_size col = 0; col < B->cols; col++) {
            mt_value sum = 0;

            for(mt_size row_b = 0; row_b < B->rows; row_b++) {
                mt_value prod = mt_get_val(A, row, row_b) * mt_get_val(B, row_b, col);
                
                sum += prod;
            }

            mt_set_val(&new_mat, row, col, sum);
        }
    }

    return new_mat;
}

mt_matrix mt_scale(mt_matrix *A, mt_value scalar) {
    if(!A->is_valid) {
        return (mt_matrix){0};
    }

    mt_matrix new_mat = mt_copy_matrix(A);

    if(!new_mat.is_valid) {
        return (mt_matrix){0};
    }

    for(mt_size row = 0; row < new_mat.rows; row++) {
        for(mt_size col = 0; col < new_mat.cols; col++) {
            mt_value scaled_val = scalar * mt_get_val(&new_mat, row, col);

            mt_set_val(&new_mat, row, col, scaled_val);
        }
    }

    return new_mat;
}
//NON-ACCELERATED FUNCTIONS

//(TO-BE-)GPU-ACCELERATED FUNCTIONS
mt_matrix mt_add_GPU(mt_matrix A, mt_matrix B) {
    (void)A;
    (void)B;

    assert(0 && "Unimplemented.");
}

mt_matrix mt_mult_GPU(mt_matrix A, mt_matrix B) {
    (void)A;
    (void)B;
    
    assert(0 && "Unimplemented.");
}

mt_matrix mt_scale_GPU(mt_matrix A, mt_value scalar) {
    (void)A;
    (void)scalar;
    
    assert(0 && "Unimplemented.");
}
//(TO-BE-)GPU-ACCELERATED FUNCTIONS