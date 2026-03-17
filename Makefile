src:
	gcc main.c -o main -I/usr/local/include/suitesparse -lgraphblas -llagraph

generate:
	gcc gen.c -o gen -I/usr/local/include/suitesparse -lgraphblas -llagraph -llagraphx

mxm_gen:
	gcc ./mxm_like/mxm_like_gen.c -o mxm_gen -I/usr/local/include/suitesparse -lgraphblas -llagraph -llagraphx

mxm_run:
	gcc ./mxm_like/mxm_like_run.c -o mxm_run -I/usr/local/include/suitesparse -lgraphblas -llagraph -llagraphx

kron_gen:
	gcc ./kron/kron_gen.c -o kron_gen -I/usr/local/include/suitesparse -lgraphblas -llagraph -llagraphx

kron_run:
	gcc ./kron/kron_run.c -o kron_run -I/usr/local/include/suitesparse -lgraphblas -llagraph -llagraphx

page_rank:
	gcc ./page_rank_like.c -o page_rank -I/usr/local/include/suitesparse -lgraphblas -llagraph
