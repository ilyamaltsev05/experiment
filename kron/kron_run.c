#include <GraphBLAS.h>
#include <LAGraph.h>
#include <stdio.h>

void load(GrB_Matrix *A, const char *filepath) {
    FILE *f = fopen(filepath, "r");
    LAGraph_MMRead(A, f, NULL);
    fclose(f);
}

int main(int argc, char **argv) {
    GrB_init(GrB_BLOCKING);
    LAGraph_Init(NULL);
    printf("\ninitialized\n");

    GrB_Matrix A, B, M, C;
    load(&A, argv[1]);
    load(&B, argv[2]);
    load(&M, argv[3]);

    GrB_Index anrows, ancols, bnrows, bncols;

    GrB_Matrix_nrows(&anrows, A);
    GrB_Matrix_ncols(&ancols, A);

    GrB_Matrix_nrows(&bnrows, B);
    GrB_Matrix_ncols(&bncols, B);

    GrB_Matrix_new(&C, GrB_FP64, anrows * bnrows, ancols * bncols);

    GrB_Info code = GrB_kronecker(C, M, NULL, GrB_TIMES_FP64, A, B, NULL);
    printf("do kron\n");
    if (code != GrB_SUCCESS)
    {
        printf("kronecker error: %d\n", code);
    }
    printf("done kron\n");

    GrB_Matrix_free(&A);
    GrB_Matrix_free(&B);
    GrB_Matrix_free(&M);
    GrB_Matrix_free(&C);

    LAGraph_Finalize(NULL);
    GrB_finalize();

    return 0;
}
