#include <GraphBLAS.h>
#include <LAGraph.h>
#include <LAGraphX.h>
#include <stdio.h>

int main(void) {
    GrB_init(GrB_BLOCKING);
    LAGraph_Init(NULL);

    GrB_Matrix vert, ones, Mask;
    uint64_t seed = 42;

    GrB_Index m = 21000;
    GrB_Info code = LAGraph_Random_Matrix(&vert, GrB_FP64, m, 1, 0.08, seed, NULL);
    if (code != GrB_SUCCESS) {
        printf("error vert: %d\n", code);
    }

    GrB_Index n = 22000;
    GrB_Matrix_new(&ones, GrB_FP64, 1, n);
    for (GrB_Index j = 0; j < n; j++) {
        code = GrB_Matrix_setElement_FP64(ones, 1.0, 0, j);
        if (code != GrB_SUCCESS) {
            printf("error ones: %d\n", code);
        }
    }

    code = LAGraph_Random_Matrix(&Mask, GrB_FP64, m, n, 0.01, seed + 1, NULL);
    if (code != GrB_SUCCESS) {
        printf("error Mask: %d\n", code);
    }

    FILE *f = fopen("vert.mtx", "w");
    LAGraph_MMWrite(vert, f, NULL, NULL);
    fclose(f);
    GrB_Matrix_free(&vert);

    f = fopen("ones.mtx", "w");
    LAGraph_MMWrite(ones, f, NULL, NULL);
    fclose(f);
    GrB_Matrix_free(&ones);

    f = fopen("mask.mtx", "w");
    LAGraph_MMWrite(Mask, f, NULL, NULL);
    fclose(f);
    GrB_Matrix_free(&Mask);

    LAGraph_Finalize(NULL);
    GrB_finalize();
}
