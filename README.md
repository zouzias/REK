This directory contains an implementation of the algorithm described in [1].

[1] Randomized Extended Kaczmarz for Solving Least-Squares.\\
    Authors: Anastasios Zouzias and Nikolaos Freris
    Available at http://arxiv.org/abs/1205.5770


======================
Installation instructions
======================

To run the randomized extended Kaczmarz (REK-BLAS) algorithm, type

compileMe

under your MATLAB enviroment. This MATLAB script will compile the mex implementation of REK-BLAS. Then, type

plotResults

under MATLAB to plot a sample execution (adjust the diemsionality of m, n depending on your CPU specs).

Given any m x n real matrix and m-dim vector b, the following instruction executes the randomized extended Kaczmarz algorithm with parameters:

*) MAXITERS - (Input) maximum number of iterations
*) TOL      - (Input) Tolerance parameter
*) x        - (Output) An estimation of the minimum Euclidean norm least-squares solution of Ax=b
*) dt       - Elapsed time using Unix routing ftime()

[x, dt] = REKBLAS_mex(A, b, MAXITERS, TOL);

======================
Operating instructions
======================

The current implementation has been tested under Linux.

============================================
A file manifest (list of files included)
============================================

AliasSampler.{c,h} - Alias sampling method for finite distributions

compileMe.m        - Compile project under MATLAB

REKBLAS.{c,h}      - Main Source files (implement the algorithm)

REKBLAS_mex.{c,h}  - Wrapper for MATLAB using Mex technology

types.h            - Data-structures

utils.{c,h}        - Utilities

plotResults.m      - Plot results in MATLAB

testREK.m          - Auxiliary matlab script

============================================
Copyright and licensing information
============================================

See LICENSE file.

============================================
Contact information for the distributor or programmer
============================================


======================
Known bugs
======================

None yet.

======================
Troubleshooting
======================
N/A

============================================
Credits and acknowledgments
============================================

Credits to TODO
