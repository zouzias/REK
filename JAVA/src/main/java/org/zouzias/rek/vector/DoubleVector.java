package org.zouzias.vector;

import java.util.Iterator;
import java.util.List;
import org.zouzias.BLAS.BLASLevelOne;

/**
 *
 */
public abstract class DoubleVector implements BLASLevelOne {

    /** Fill the vector with random entries
     *
     */
    public abstract void random();

    /** The size of the vector
     *
     * @return
     */
    public abstract int size();

    /** Get the i-th entry of the vector
     *
     * @param index
     * @return
     */
    public abstract double get(int index);

    /** Set the i-th entry of the vector
     *
     * @param index
     * @param value
     */
    public abstract void set(int index, double value);

    /** Scale the vector by alpha
     *
     * @param alpha
     */
    public abstract void scale(double alpha);

    /** Substract from the vector x
     *
     * @param x
     */
    public abstract void minus(DoubleVector x);
    
    /** Represent the vector as a list
     *
     * @return
     */
    public abstract List<Double> asList();

}
