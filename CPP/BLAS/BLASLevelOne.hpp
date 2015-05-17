/*
 * BLASLevelOne.hpp
 *
 *  Created on: May 4, 2015
 *      Author: zouzias
 */

#ifndef BLASLEVELONE_HPP_
#define BLASLEVELONE_HPP_

class DoubleVector;

class BLASLevelOne {

public:

    /**
     * Euclidean norm of vector
     *
     * @return
     */
    virtual double DNRM2() = 0;
    /**
     * DAXPY operation y <- y + alpha * x
     *
     * @param alpha
     * @param x
     */
    virtual void DAXPY(double alpha, const DoubleVector& x) = 0;
    /**
     * Dot product with vector x
     *
     * @param x
     * @return
     */
    virtual double DDOT(const DoubleVector& x) = 0;
};


#endif /* BLASLEVELONE_HPP_ */
