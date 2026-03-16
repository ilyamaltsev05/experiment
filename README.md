# Эксперимент с реализацией Кронекера с маской

Рассмотрены два вида входов:
 - Произведение Кронекера матриц, подобных тем, что
 встречаются в masked mxm PageRank_demo - матрица m-by-1 из на матрицу
 1-by-n из единиц со случайной маской подходящего размера
 - Произведение Кронекера некоторых матриц из sparse collection и разными
 масками


## 1) Вычисление, эквивалентное mxm в PageRank_demo

Сравнение существующей реализации с применением маски после с новой на примере вычисления произведения Кронекера матрицы m на 1 и матрицы из единиц 1 на n.

### Peak memory consumption некоторых входов

| input\implementation | default | masked | masked mxm
|---|---|---|---|
| 10x10 | 2,0 MB | 2,0 MB |
| 50x50 | 2,0 MB | 2,0 MB |
| 100x100 | 2,0 MB | 2,0 MB |
| 500x500 | 2,2 MB | 2,2 MB |
| 1000x500 | 2,5 MB | 2,5 MB |
| 1000x1000 | 2,3 MB | 2,2 MB |
| 5000x5000 | 10,1 MB | 8,9 MB | 8,9 MB
| 7500x7500 | 15,9 MB | 4,2 MB | 4,2 MB
| 10000x10000 | 20,5 MB | 5,0 MB | 5,0 MB
| 15000x15000 | 58,2 MB | 11,0 MB | 11,0 MB
| 20000x20000 | 422,9 MB | 193,2 MB | 193,2 MB


## 2) Вычисление на некоторых матрицах из SuiteSparse Matrix Collection

### Peak memory consumption входов

| input\implementation | default | masked
|---|---|---|
| lap_25 (97 nnz), divorce (225 nnz), mask (density=0.1) | 3,1 MB | 3,1 MB
| lap_25 (97 nnz), divorce (225 nnz), mask (density=0.3) | 5,3 MB | 5,3 MB
| 08blocks (592 nnz), Trec8 (549 nnz), mask (density=0.1) | 836,6 MB | 836,6 MB
| 08blocks (592 nnz), Trec8 (549 nnz), mask (density=0.3) | 2,5 GB | 2,5 GB
| bcsstm08 (1074 nnz), rdb200 (1120 nnz), mask (density=0.000001) | 21,3 MB | 4,8 MB
| netscience (2742 nnz), small (3207 nnz), mask (density=0.000001) | 263,3 MB | 116,9 MB
