
#include "DoubleVector.hpp"
#include <assert.h>
#include <vector>

class DenseVector : public DoubleVector {

private:
std::vector<double> _vector;

public:

	DenseVector(): DoubleVector(DEFAULT_SIZE), _vector(DEFAULT_SIZE){
	};

	DenseVector(int size): DoubleVector(size), _vector(size){
	};

	DenseVector(const DoubleVector& vec): _vector(vec.size()){
		for (int i = 0; i < _vector.size(); i++){
			_vector[i] = vec.get(i);
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
