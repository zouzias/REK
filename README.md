<h2> Randomized Extended Kaczmarz </h2>
<h3> Overview </h3>
This directory contains an implementation of the algorithm described in [1] by Anastasios Zouzias.


* [1] - <b>Randomized Extended Kaczmarz for Solving Least-Squares.</b>

Authors: Anastasios Zouzias and Nikolaos Freris

Available at http://arxiv.org/abs/1205.5770


<h2>
Installation instructions
</h2>
This program requires MATLAB under Linux enviroment for testing. To run the randomized extended Kaczmarz (REK-BLAS) algorithm, type

<code>
compileMe
</code>

under your MATLAB enviroment. This MATLAB script will compile the mex implementation of REK-BLAS. Then, type

<code>
plotResults
</code>

under MATLAB to plot a sample execution (adjust the diemsionality of m, n depending on your CPU specs).

<p>
After compilation, you can execute the <b>randomized extended Kaczmarz</b> using the following command:

<code>
[x, dt] = REKBLAS_mex(A, b, MAXITERS, TOL);
</code>

where the <b>input/output</b> parameters are : 

+ A        - <b>(Input) An m x n real matrix
+ b        - <b>(Input) An m dimensional vector
+ MAXITERS - <b>(Input) maximum number of iterations
+ TOL      - <b>(Input) Tolerance parameter
+ x        - <b>(Output) An estimation of the minimum Euclidean norm least-squares solution of Ax=b
+ dt       - <b>(Output) Elapsed time using Unix routing ftime()

<h2>
Operating instructions
</h2>

The current implementation has been tested under Linux running MATLAB 7.9 with GCC 4.7.2.

<h2>
A file manifest (list of files included)
</h2>

* AliasSampler.{c,h} - <b> Alias sampling method for finite distributions</b>
* compileMe.m        - <b> Compile project under MATLAB </b>
* REKBLAS.{c,h}      - <b> Main Source files (implement the algorithm) </b>
* REKBLAS_mex.{c,h}  - <b> Wrapper for MATLAB using Mex technology </b>
* types.h            - <b> Useful structures </b>
* utils.{c,h}        - <b> Utilities </b>
* plotResults.m      - <b> Plot results in MATLAB </b>
* testREK.m          - <b> Auxiliary MATLAB script </b>

<h2>
Copyright and licensing information
</h2>

See LICENSE file.

<h2>
Contact information for the distributor or programmer
</h2>

<h2>
Known bugs
</h2>

None yet.

<h2>
Troubleshooting
</h2>

N/A

<h2>
Credits and acknowledgments
</h2>

Credits to for the aliasing method (see files AliasSampler.{c,h})
