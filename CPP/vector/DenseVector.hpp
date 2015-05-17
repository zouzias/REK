
#include "DoubleVector.hpp"
#include <assert.h>
#include <vector>


class DenseVector : public DoubleVector {

private:

const static int DEFAULT_SIZE = 10;
vector<double> vector_;

public:

	DenseVector(): vector_(DEFAULT_SIZE){
	};

	DenseVector(int size): vector_(size){
	};

	// Copy constructor
	DenseVector(const DoubleVector& vec): vector_(vec.size()){
		for (int i = 0; i < vector_.size(); i++){
			vector_[i] = vec.get(i);
		}
	};


	~DenseVector(){
	};

	void random();

	int size() const;

	double get(int index) const;

	void set(int index, double value);

	void scale(double alpha);

	void minus(const DoubleVector& x);

	std::vector<double>& asList();
};
