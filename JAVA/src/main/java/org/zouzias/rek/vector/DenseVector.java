package org.zouzias.vector;

import java.util.ArrayList;
import java.util.List;
import org.zouzias.utils.NAUtils;

/** Implementation of a dense vector
 *
 */
public final class DenseVector extends DoubleVector {

    private double[] vector;

    /**
     *
     * @param vec
     */
    public DenseVector(DoubleVector vec) {
        int size = vec.size();
        vector = new double[size];

        for (int i = 0; i < size; i++)
            vector[i] = vec.get(i);
    }

    /**
     *
     * @param size
     */
    public DenseVector(int size) {
        vector = new double[size];
    }

    /**
     *
     * @param vector
     */
    public DenseVector(double[] vector) {
        this.vector = new double[vector.length];
        System.arraycopy(vector, 0, this.vector, 0, vector.length);
    }

    /**
     * Get the size
     * 
     * @return
     */
    @Override
    public int size() {
        return vector.length;
    }

    /**
     * Get the i-th entry
     *
     * @param i
     * @return
     */
    @Override
    public double get(int i) {
        return vector[i];
    }

    /**
     * Set the i-th entry 
     *
     * @param i
     * @param val
     */
    @Override
    public void set(int i, double val) {
        vector[i] = val;
    }

    /**
     * Scale vector by alpha
     *
     * @param alpha
     */
    @Override
    public void scale(double alpha) {
        for (int i = 0; i < vector.length; i++)
            vector[i] = alpha * vector[i];
    }

    /**
     * Fill in the vector with random entries
     *
     */
    @Override
    public void random() {
        for (int i = 0; i < size(); i++)
            vector[i] = Math.random();
    }

    /** 
     * Subtract vector x, i.e., vector = vector - x
     *
     * @param x
     */
    @Override
    public void minus(DoubleVector x) {
        DAXPY(-1, x);
    }

    /**
     * Dot product with x
     *
     * @param x
     * @return
     */
    @Override
    public double DDOT(DoubleVector x) {
        double dot = 0.0;
        if (size() != x.size())
            throw new IndexOutOfBoundsException();

        for (int i = 0; i < size(); i++)
            dot += get(i) * x.get(i);

        return dot;
    }

    /**
     * y <- y + alpha * x where y is the vector of *this*
     *
     * @param alpha
     * @param x
     */
    @Override
    public void DAXPY(double alpha, DoubleVector x) {
        if (size() != x.size())
            throw new IndexOutOfBoundsException();

        for (int i = 0; i < x.size(); i++)
            vector[i] += alpha * x.get(i);
    }

    /**
     * Get the 2-norm
     *
     * @return
     */
    @Override
    public double DNRM2() {
        double norm = 0.0;
        for (int i = 0; i < size(); i++)
            norm = NAUtils.hypot(norm, get(i));

        return norm;
    }

    /**
     * Return the vector as list
     *
     * @return
     */
    @Override
    public List<Double> asList() {
        List<Double> list = new ArrayList<Double>();
        for ( double s : vector)
            list.add(s);  
        
        return list;
    }
}
