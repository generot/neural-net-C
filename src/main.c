#include "main.h"
#include "matrix.h"

#include <math.h>

mt_value activation(mt_value x) {
    return exp(-x) / (1 - exp(-x));
}

int main(void) {
    mt_matrix A = {0};
    mt_matrix B = {0};

    mt_value ex1[] = {
        1, 2,
        2, 3,
        3, 4
    };

    mt_value ex2[] = {
        2, 2,
        1, 3
    };

    mt_allocate_matrix(&A, 3, 2);
    mt_allocate_matrix(&B, 2, 2);

    mt_init_from_arr(&A, (mt_value*)ex1);
    mt_init_from_arr(&B, (mt_value*)ex2);

    printf("A = \n");
    mt_print_matrix(A);
    printf("B = \n");
    mt_print_matrix(B);

    mt_matrix C = mt_mult(&A, &B);

    printf("C = \n");
    mt_print_matrix(C);

    mt_matrix D = mt_add(&A, &A);

    printf("D = \n");
    mt_print_matrix(D);

    mt_matrix E = mt_scale(&A, -3.0);

    printf("E = \n");
    mt_print_matrix(E);

    mt_matrix E_Tr = mt_transpose(&E);
    mt_matrix E_f = mt_apply_lambda(&E_Tr, activation);

    printf("E^T = \n");
    mt_print_matrix(E_f);

    mt_free_matrix(&A);
    mt_free_matrix(&B);
    mt_free_matrix(&C);
    mt_free_matrix(&D);
    mt_free_matrix(&E);
    mt_free_matrix(&E_Tr);
    mt_free_matrix(&E_f);

    return 0;
}