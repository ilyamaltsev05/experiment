src:
	gcc main.c -o main -I/usr/local/include/suitesparse -lgraphblas -llagraph

generate:
	gcc gen.c -o gen -I/usr/local/include/suitesparse -lgraphblas -llagraph -llagraphx