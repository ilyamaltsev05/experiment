#include <GraphBLAS.h>
#include <LAGraph.h>
#include <stdio.h>
#include <string.h>

void load(GrB_Matrix *A, const char *filepath) {
    FILE *f = fopen(filepath, "r");
    LAGraph_MMRead(A, f, NULL);
    fclose(f);
}

int main(int argc, char **argv) {
    GrB_init(GrB_BLOCKING);
    LAGraph_Init(NULL);
    printf("\ninitialized\n");

    GrB_Descriptor desc;
    GrB_Descriptor_new(&desc);
    GrB_Descriptor_set(desc, GrB_MASK, GrB_STRUCTURE);


    GrB_Matrix mat;
    load(&mat, argv[1]);
    //GxB_print(mat, GxB_COMPLETE);

    GrB_Index matrows, matcols;

    GrB_Matrix_nrows(&matrows, mat);
    GrB_Matrix_ncols(&matcols, mat);

    GrB_Vector vec;
    GrB_Vector_new(&vec, GrB_FP64, matrows);
    GrB_Matrix_reduce_Monoid(vec, NULL, NULL, GrB_PLUS_MONOID_FP64, mat, NULL);

    printf("\nreduced\n");

    GrB_Vector id_final;
    GrB_Vector_new(&id_final, GrB_FP64, matcols);
    GrB_Vector_assign_BOOL(id_final, NULL, NULL, true, GrB_ALL, matcols, NULL);

    GrB_Matrix v_mat, id_mat;

    GrB_Matrix_new(&v_mat, GrB_FP64, matrows, 1);
    GrB_Col_assign(v_mat, NULL, NULL, vec, GrB_ALL, matrows, 0, NULL);

    GrB_Matrix_new(&id_mat, GrB_FP64, 1, matcols);
    GrB_Row_assign(id_mat, NULL, NULL, id_final, 0, GrB_ALL, matcols, NULL);

    GrB_Matrix SUMmat;
    GrB_Index nvals;
    GrB_Matrix_new(&SUMmat, GrB_FP64, matrows, matcols);
    GrB_Info code;
    if (strcmp(argv[2], "m") == 0) {
        code = GrB_mxm(SUMmat, mat, NULL, GxB_PLUS_TIMES_FP64, v_mat, id_mat, desc);
        if (code != GrB_SUCCESS) {
            printf("error mxm: %d\n", code);
        }
        //GxB_print(SUMmat, GxB_COMPLETE);
        FILE *m = fopen("MxM.mtx", "w");
        LAGraph_MMWrite(SUMmat, m, NULL, NULL);
        fclose(m);
        printf("\ndone mxm\n");
    }
    else if (strcmp(argv[2], "k") == 0) {
        code = GrB_kronecker(SUMmat, mat, NULL, GrB_TIMES_FP64, v_mat, id_mat, desc);
        if (code != GrB_SUCCESS) {
            printf("error kronecker: %d\n", code);
        }
        //GxB_print(SUMmat, GxB_COMPLETE);
        FILE *k = fopen("Kron.mtx", "w");
        LAGraph_MMWrite(SUMmat, k, NULL, NULL);
        fclose(k);
        printf("\ndone kronecker\n");
    }


    GrB_Matrix_free(&SUMmat);
    GrB_Matrix_free(&mat);
    GrB_Matrix_free(&v_mat);
    GrB_Matrix_free(&id_mat);

    LAGraph_Finalize(NULL);
    GrB_finalize();

    return 0;
}