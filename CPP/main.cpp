//============================================================================
// Name        : REK-CPP.cpp
// Author      : Anastasios Zouzias
// Version     :
// Copyright   : Apache 2.0 License
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>

#include "samplers/AliasSampler.hpp"
#include "algorithms/REKSolver.hpp"


#include "matrix/impl/DenseMatrix.hpp"
#include "vector/DenseVector.hpp"

using namespace std;

int main(void) {
	int m= 100, n = 10;

	DoubleMatrix* A = new DenseMatrix(m,n);
	DoubleVector* xopt = new DenseVector(n);
	xopt->random();
	A->random();
	DoubleVector* b = A->times(*xopt);

	REKSolver solver = REKSolver();

	long ITERS = 50000;
	DoubleVector* x = solver.solve(*A, *b, ITERS);

	cout<<"(x , xopt)"<<endl;
	for (int j = 0 ; j < A->getColumnDimension(); j++){
		cout<< x->get(j) << " , " << xopt->get(j) <<endl;
	}

	x->minus(*xopt);
	cout<< "LS error: " << x->DNRM2() << endl;

	return 0;
}