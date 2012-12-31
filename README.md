This directory contains an implementation of the algorithm described in [1] by Anastasios Zouzias.

[1]
Randomized Extended Kaczmarz for Solving Least-Squares.

Authors: Anastasios Zouzias and Nikolaos Freris

Available at http://arxiv.org/abs/1205.5770


Installation instructions
================================

This program requires MATLAB under Linux enviroment for testing. To run the randomized extended Kaczmarz (REK-BLAS) algorithm, type

<code>
compileMe
</code>

under your MATLAB enviroment. This MATLAB script will compile the mex implementation of REK-BLAS. Then, type

<code>
plotResults
</code>

under MATLAB to plot a sample execution (adjust the diemsionality of m, n depending on your CPU specs).

<code>
[x, dt] = REKBLAS_mex(A, b, MAXITERS, TOL);
</code>

Given any m x n real matrix A and m-dim vector b, the following instruction executes the randomized extended Kaczmarz algorithm with parameters:

+ MAXITERS - (Input) maximum number of iterations
+ TOL      - (Input) Tolerance parameter
+ x        - (Output) An estimation of the minimum Euclidean norm least-squares solution of Ax=b
+ dt       - Elapsed time using Unix routing ftime()


Operating instructions
================================

The current implementation has been tested under Linux running MATLAB 7.9 with GCC 4.7.2.

A file manifest (list of files included)
================================

* AliasSampler.{c,h} - <b> Alias sampling method for finite distributions</b>
* compileMe.m        - <b> Compile project under MATLAB </b>
* REKBLAS.{c,h}      - <b> Main Source files (implement the algorithm) </b>
* REKBLAS_mex.{c,h}  - <b> Wrapper for MATLAB using Mex technology </b>
* types.h            - <b> Data-structures </b>
* utils.{c,h}        - <b> Utilities </b>
* plotResults.m      - <b> Plot results in MATLAB </b>
* testREK.m          - <b> Auxiliary matlab script </b>

Copyright and licensing information
================================

See LICENSE file.


Contact information for the distributor or programmer
================================


Known bugs
================================

None yet.


Troubleshooting
================================

N/A

Credits and acknowledgments
================================

Credits to for the aliasing method (see files AliasSampler.{c,h})
