% This script compiles the REKBLAS_mex.c file

mex -v -largeArrayDims -ldl CFLAGS='$CFLAGS -O3 -Wall -fPIC' -lmwblas REKBLAS_mex.c REKBLAS.c AliasSampler.c utils.c

% [x, dt] = REKBLAS_mex(A, b, MAXITERS, TOL);
%
%
% Given any m x n real matrix and m-dim vector b, the following instruction executes the randomized extended Kaczmarz algorithm with parameters:
% 
% *) MAXITERS - (Input) maximum number of iterations
% *) TOL      - (Input) Tolerance parameter
% *) x        - (Output) An estimation of the minimum Euclidean norm least-squares solution of Ax=b
% *) dt       - Elapsed time using Unix routing ftime()