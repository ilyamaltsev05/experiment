# Замеры потребления памяти реализацией Кронекера с маской (WIP)

Рассмотрены три вида входов:
 - Произведение Кронекера - изолированный шаг с masked mxm из PageRank_demo, на вход подается матрица из
 SuiteSparse Matrix Collection, она же служит маской.
 - Произведение Кронекера матриц, подобных тем, что
 встречаются в masked mxm PageRank_demo - матрица m-на-1 на матрицу
 1-на-n из единиц со случайной маской подходящего размера.
 - Произведение Кронекера некоторых матриц из SuiteSparse Matrix Collection с построенными с помощью LAGraph_Random_Matrix масками.
 
Замеры сделаны с помощью heaptrack.

Воспроизвести можно с помощью https://github.com/ilyamaltsev05/experiment

## 1) Вычисление, эквивалентное mxm в PageRank_demo, с маской из SuiteSparse MAtrix Collection.

### Peak memory consumption

| input\implementation | default | masked | masked mxm
|---|---|---|---|
| YaleB_10NN (17404 nnz) | 49,5 MB | 3,3 MB | 3,3 MB
| USpowerGrid (6594 nnz) | 197,6 MB | 2,3 MB | 2,9 MB
| p2p-Gnutella09 (26013 nnz) | 300,1 MB | 2,7 MB | 3,7 MB
| p2p-Gnutella31 (147892 nnz) | 12,3 GB | 14,2 MB | 14,5 MB
| Kohonen (12731 nnz) | 99,9 MB | 2,7 MB | 2,9 MB
| dixmaanl (179999 nnz) | out of memory | 27,4 MB | 27,4 MB
| Goodwin_030 (312814 nnz) | 832,7 MB | 27,2 MB | 27,2 MB

### Время исполнения

На 10 запусках

| input\implementation | masked | masked mxm
|---|---|---|
| YaleB_10NN (17404 nnz) | 1,019 $\pm$ 0,075 s | 1,320 $\pm$ 0,147 s
| USpowerGrid (6594 nnz) | 0,140 $\pm$ 0,023 s | 1,172 $\pm$ 0,170 s
| p2p-Gnutella09 (26013 nnz) | 0,205 $\pm$ 0,023 s | 1,304 $\pm$ 0,208 s
| p2p-Gnutella31 (147892 nnz) | 0,780 $\pm$ 0,126 s | 23,192 $\pm$ 0,428 s
| Kohonen (12731 nnz) | 0,157 $\pm$ 0,051 s | 0,338 $\pm$ 0,049 s
| dixmaanl (179999 nnz) | 7,557 $\pm$ 0,264 s | 87,414 $\pm$ 2,685 s
| Goodwin_030 (312814 nnz) | 6,869 $\pm$ 0,203 s | 9,135 $\pm$ 0,196 s

## 2) Вычисление, эквивалентное mxm в PageRank_demo.

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