#ifndef SPARSEVECTOR_HPP_
#define SPARSEVECTOR_HPP_

#include "DoubleVector.hpp"

class DoubleVector;

class SparseVector: public DoubleVector{

	public:

	void random();

	int size() const;

	double get(int index) const;

	void set(int index, double value);

	void scale(double alpha);

	void minus(DoubleVector& x);

	vector<double>& asList();
};

#endif
