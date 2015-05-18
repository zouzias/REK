#ifndef SPARSEVECTOR_HPP_
#define SPARSEVECTOR_HPP_

#include "DoubleVector.hpp"
#include <random>
#include <map>

class DoubleVector;

class SparseVector: public DoubleVector{
private:

std::map<int, double> _values;
int _size;

typedef std::map<int, double>::iterator values_iter;


public:

	SparseVector(): _values(){
		_size = DEFAULT_SIZE;
	};

	void random();

	int size() const;

	double get(int index) const;

	void set(int index, double value);

	void scale(double alpha);

	void minus(const DoubleVector& x);

	std::vector<double>& asList();
};

#endif
