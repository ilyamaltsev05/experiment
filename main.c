#include <GraphBLAS.h>
#include <LAGraph.h>
#include <stdio.h>
#include <stdbool.h>

bool load(GrB_Matrix *A, const char *filepath) {
    FILE *f = fopen(filepath, "r");
    LAGraph_MMRead(A, f, NULL);
    fclose(f);
    return true;
}

int main(int argc, char** argv) {
    GrB_init(GrB_BLOCKING);
    LAGraph_Init(NULL);

    GrB_Matrix A, B, M, C;
    if (!load(&A, argv[1])) { printf("Couldnt load A\n"); }
    if (!load(&B, argv[2])) { printf("Couldnt load B\n"); }
    if (!load(&M, argv[3])) { printf("Couldnt load M\n"); }

    GrB_Index anrows, ancols, bnrows, bncols;

    GrB_Matrix_nrows(&anrows, A);
    GrB_Matrix_ncols(&ancols, A);

    GrB_Matrix_nrows(&bnrows, B);
    GrB_Matrix_ncols(&bncols, B);

    GrB_Matrix_new(&C, GrB_FP64, anrows * bnrows, ancols * bncols);

    GrB_Info code = GrB_kronecker(C, M, NULL, GrB_TIMES_FP64, A, B, NULL);
    //GrB_Info code = GrB_mxm(C, M, NULL, GxB_PLUS_TIMES_FP64, A, B, NULL);
    if (code != GrB_SUCCESS)
    {
        printf("kronecker error: %d\n", code);
    }

    printf("alive here\n");

    GrB_Matrix_free(&A);
    printf("alive after A\n");
    GrB_Matrix_free(&B);
    printf("alive after B\n");
    GrB_Matrix_free(&M);
    printf("alive after M\n");
    GrB_Matrix_free(&C);
    printf("alive after C\n");

    LAGraph_Finalize(NULL);
    GrB_finalize();

    return 0;
}
