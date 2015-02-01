<h2> Randomized Extended Kaczmarz</h2>
Java: <img src="https://travis-ci.org/zouzias/REK.svg?branch=master"/>
<h3> Overview </h3>
The current project contains an implementation of the algorithm described in the research paper [1]. The Randomized Extended Kaczmarz algorithm is a randomized algorithm for solving least-squares/linear regression problems. The current project provides implementations of REK in C, Java and Matlab (wriiten in C with mex-files integrations).

<br>
[<b>Randomized Extended Kaczmarz for Solving Least-Squares.</b>](http://dx.doi.org/10.1137/120889897)
<br>
SIAM. J. Matrix Anal. & Appl., 34(2), 773–793. (21 pages) 
<br>
Authors: [Anastasios Zouzias](https://github.com/zouzias) and Nikolaos Freris 
<br>
<h3>
Installation
</h3>
<h4>
C
</h4>

Clone the project. Move to the C directory, and then type

<code>make</code>
<br>
<code>./REK</code>

The above code runs a simple instance of least-squares for a gaussian random matrix A and gaussian vector b. See 'main.c' for more details.
<h4>
Java
</h4>

Clone the project. Move to the Java directory, and then type

<code>mvn compile test</code>

To run a few simple tests. See `TestREKSolverIT.java` for an example how to use the REK least-squares solver.

<h4>
Bugs
</h4>
Please report bugs by opening a new [issue](https://github.com/zouzias/REK/issues/new).

<h4>
Implementation Details
</h4>
The algorithm (REK-BLAS) has been implemented in C and Java. REK-BLAS is an implementation of REK with two additional technical features. First, REK-BLAS utilizes level-1 BLAS routines for 
all operations of REK and second REK-BLAS additionally stores explicitly the transpose of A for more efficiently 
memory access of both the rows and columns of A using BLAS (see the above paper for more details). 

The sampling operations of REK are implemented using the so-called ``alias method'' for generating samples 
from any given discrete distribution [Vos91]. In particular, the alias method, assuming access 
to a uniform random variable on [0,1] in constant time and linear time preprocessing, generates one sample
of a given distribution in constant time. We use an implementation of W. D. Smith and Keith Schwarz (htiek@cs.stanford.edu) for C and Java, respectively.

<h4>
Credits and acknowledgments
</h4>

Credits go to Warren D. Smith and Keith Schwarz for implementing the aliasing method [Vos91] in C and Java, respectively.
<br><br>
[Vos91] M. D. Vose. A Linear Algorithm for Generating Random Numbers with a given Distribution. 
<br>
IEEE Trans. Softw. Eng., 17(9):972–975, September 1991.
