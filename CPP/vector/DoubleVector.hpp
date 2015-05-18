

#ifndef DOUBLEVECTOR_HPP_
#define DOUBLEVECTOR_HPP_

#include <vector>

#include "../BLAS/BLASLevelOne.hpp"

using namespace std;

class DoubleVector : public BLASLevelOne{

protected:
	const static int DEFAULT_SIZE = 10;
public:

	DoubleVector();

	double DNRM2();

	/**
	 * DAXPY operation y <- y + alpha * x
	 *
	 * @param alpha
	 * @param x
	 */
	void DAXPY(double alpha, const DoubleVector& x);
	/**
	 * Dot product with vector x
	 *
	 * @param x
	 * @return
	 */
	double DDOT(const DoubleVector& x);

	/** Fill the vector with random entries
	 *
	 */
	virtual void random() = 0;

	/** The size of the vector
	 *
	 * @return
	 */
	virtual int size() const = 0;

	/** Get the i-th entry of the vector
	 *
	 * @param index
	 * @return
	 */
	virtual double get(int index) const = 0;

	/** Set the i-th entry of the vector
	 *
	 * @param index
	 * @param value
	 */
	virtual void set(int index, double value) = 0;

	/** Scale the vector by alpha
	 *
	 * @param alpha
	 */
	virtual void scale(double alpha) = 0 ;

	/** Substract from the vector x
	 *
	 * @param x
	 */
	virtual void minus(const DoubleVector& x)  = 0;

	/** Represent the vector as a list
	 *
	 * @return
	 */
	virtual vector<double>& asList()  = 0;
};

#endif
