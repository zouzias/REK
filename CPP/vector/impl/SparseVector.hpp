#ifndef SPARSEVECTOR_HPP_
#define SPARSEVECTOR_HPP_

#include "../DoubleVector.hpp"
#include <time.h>
#include <stdlib.h>
#include <map>

class DoubleVector;

class SparseVector: public DoubleVector{

private:
	std::map<int, double> _values;
	typedef std::map<int, double>::iterator values_iter;

public:

	SparseVector(): DoubleVector(DEFAULT_SIZE), _values(){};

	SparseVector(int size): DoubleVector(size), _values(){
		_size = size;
	};

	~SparseVector(){};

	void random();

	int size() const;

	double get(int index) const;

	void set(int index, double value);

	void scale(double alpha);

	void minus(const DoubleVector& x);

};

#endif
