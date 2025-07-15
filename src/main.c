#include "main.h"
#include "matrix.h"

int main(void) {
    mats_matrix A = {0};
    mats_matrix B = {0};

    mats_value ex1[] = {
        1, 2,
        2, 3,
        3, 4
    };

    mats_value ex2[] = {
        2, 2,
        1, 3
    };

    mats_allocate_matrix(&A, 3, 2);
    mats_allocate_matrix(&B, 2, 2);

    mats_init_from_arr(&A, (mats_value*)ex1);
    mats_init_from_arr(&B, (mats_value*)ex2);

    printf("A = \n");
    mats_print_matrix(A);
    printf("B = \n");
    mats_print_matrix(B);

    mats_matrix C = mats_mult(&A, &B);

    printf("C = \n");
    mats_print_matrix(C);

    mats_matrix D = mats_add(&A, &A);

    printf("D = \n");
    mats_print_matrix(D);

    mats_matrix E = mats_scale(&A, -3.0);

    printf("E = \n");
    mats_print_matrix(E);

    mats_free_matrix(&A);
    mats_free_matrix(&B);
    mats_free_matrix(&C);
    mats_free_matrix(&D);
    mats_free_matrix(&E);

    return 0;
}