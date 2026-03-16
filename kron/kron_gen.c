#include <GraphBLAS.h>
#include <LAGraph.h>
#include <LAGraphX.h>
#include <stdio.h>

int main(int argc, char **argv) {
    GrB_init(GrB_BLOCKING);
    LAGraph_Init(NULL);

    GrB_Index m, n, seed;
    double m_density;
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) { return 1; }

    int count = fscanf(f, "%" SCNd64 " %" SCNd64 " %" SCNd64 " %lf", 
                       &m, &n, &seed, &m_density);
    if (count != 4) {
        return count;
    }
    fclose(f);

    GrB_Matrix Mask;
    GrB_Info code = LAGraph_Random_Matrix(&Mask, GrB_BOOL, m, n, m_density, seed, NULL);
    if (code != GrB_SUCCESS) {
        printf("error Mask: %d\n", code);
    }

    f = fopen("Mask.mtx", "w");
    LAGraph_MMWrite(Mask, f, NULL, NULL);
    fclose(f);
    GrB_Matrix_free(&Mask);
    
    LAGraph_Finalize(NULL);
    GrB_finalize();
    return 0;
}