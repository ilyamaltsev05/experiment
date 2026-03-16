# Замеры потребления памяти реализацией Кронекера с маской (WIP)

Рассмотрены два вида входов:
 - Произведение Кронекера матриц, подобных тем, что
 встречаются в masked mxm PageRank_demo - матрица m-на-1 на матрицу
 1-на-n из единиц со случайной маской подходящего размера.
 - Произведение Кронекера некоторых матриц из SuiteSparse Matrix Collection с построенными с помощью LAGraph_Random_Matrix масками.
 
Замеры сделаны с помощью heaptrack.

Воспроизвести можно с помощью https://github.com/ilyamaltsev05/experiment

## 1) Вычисление, эквивалентное mxm в PageRank_demo.

Сравнение существующей реализации с применением маски после с новой на примере вычисления произведения Кронекера матрицы m-на-1 и матрицы из единиц 1-на-n. Матрица m-на-1 и маска построены с помощью LAGraph_Random_Matrix.

### Peak memory consumption некоторых входов

Матрица m-на-1 далее vec, маска - mask.

| input\implementation | default | masked | masked mxm
|---|---|---|---|
| 10x10 | 2,0 MB | 2,0 MB | -
| 50x50 | 2,0 MB | 2,0 MB | -
| 100x100 | 2,0 MB | 2,0 MB | -
| 500x500 | 2,2 MB | 2,2 MB | -
| 1000x500 | 2,5 MB | 2,5 MB | -
| 1000x1000 | 2,3 MB | 2,2 MB | -
| 5000x5000 (vec density = 0,3; mask density = 0,01) | 81,0 MB | 12,2 MB | 12,2 MB
| 5000x7500 (vec density = 0,3; mask density = 0,01) | 120,5 MB | 17,3 MB | 17,3 MB
| 7500x5000 (vec density = 0,3; mask density = 0,03) | 124,6 MB | 47,4 MB | 47,4 MB
| 7500x7500 (vec density = 0,3; mask density = 0,01) | 178,6 MB | 24,9 MB | 24,9 MB
| 10000x7500 (vec density = 0,3; mask density = 0,01) | 239,3 MB | 32,6 MB | 32,6 MB
| 10000x10000 (vec density = 0,3; mask density = 0,005) | 315,1 MB | 22,5 MB | 22,5 MB
| 10000x10000 (vec density = 0,3; mask density = 0,01) | 318,4 MB | 42,8 MB | 42,8 MB
| 10000x10000 (vec density = 0,3; mask density = 0,1) | 392,2 MB | 392,2 MB | 392,2 MB
| 15000x15000 (vec density = 0,2; mask density = 0,0001) | 495,4 MB | 2,8 MB | 4,4 MB
| 20000x20000 (vec density = 0,2; mask density = 0,0001) | 876,6 MB | 3,4 MB | 5,3 MB
| 50000x10000 (vec density = 0,2; mask density = 0,0001) | 1,1 GB | 4,1 MB | 4,9 MB

### Время исполнения

На 100 запусках

| input\implementation | default | masked
|---|---|---|
| 5000x5000 (vec density = 0,3; mask density = 0,01) | 0,714 $\pm$ 0,045 s | 0,391 $\pm$ 0,054 s
| 5000x7500 (vec density = 0,3; mask density = 0,01) | 1,179 $\pm$ 0,237 s | 0,545 $\pm$ 0,90 s
| 7500x5000 (vec density = 0,3; mask density = 0,03) | 2,140 $\pm$ 0,655 s | 1,468 $\pm$ 0,179 s
| 7500x7500 (vec density = 0,3; mask density = 0,01) | 1,188 $\pm$ 0,167 s | 0,776 $\pm$ 0,117s
| 10000x7500 (vec density = 0,3; mask density = 0,01) | 1,514 $\pm$ 0,196 s | 1,044 $\pm$ 0,159 s
| 10000x10000 (vec density = 0,3; mask density = 0,005) | 1,400 $\pm$ 0,208 s | 0,729 $\pm$ 0,123 s
| 15000x15000 (vec density = 0,2; mask density = 0,0001) | 1,217 $\pm$ 0,183 s | 0,127 $\pm$ 0,015 s
| 20000x20000 (vec density = 0,2; mask density = 0,0001) | 2,061 $\pm$ 0,218 s | 0,165 $\pm$ 0,021 s
| 50000x10000 (vec density = 0,2; mask density = 0,0001) | 2,424 $\pm$ 0,229 s | 0,200 $\pm$ 0,028 s

## 2) Вычисление на некоторых матрицах из SuiteSparse Matrix Collection

### Peak memory consumption входов

| input\implementation | default | masked
|---|---|---|
| YaleB_10NN (17404 nnz), email-EuAll (420045 nnz), mask (density=0.000001) | out of memory | 3,1 GB
| rdb200 (1120 nnz), small (3207 nnz), mask (density=0.000001) | 48 MB | 3.6 MB

### Время исполнения

На 5 запусках

| input\implementation | default | masked
|---|---|---|
| YaleB_10NN (17404 nnz), email-EuAll (420045 nnz), mask (density=0.000001) | - | 75,971 $\pm$ 1,215 s
| rdb200 (1120 nnz), small (3207 nnz), mask (density=0.000001) | 0,264 $\pm$ 0,017 s | 0,162 $\pm$ 0,006 s