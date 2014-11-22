package org.zouzias.vector;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import org.zouzias.utils.NAUtils;

/** 
 * An implementation of a sparse vector
 *
 */
public final class SparseVector extends DoubleVector {

    Map<Integer, Double> values;
    private int size;
    
    /**
     *
     * @param size
     */
    public SparseVector(int size){
        values = new HashMap<Integer, Double>();
        this.size = size;       
    }

    /**
     *
     * @param vector
     */
    public SparseVector(double[] vector) {
        values = new HashMap<Integer, Double>();
        size = vector.length;

        for (int i = 0; i < size; i++)
            if (vector[i] != 0)
                values.put(i, vector[i]);
    }

    /**
     *
     * @return
     */
    public int nnz() {
        return values.size();
    }
    
    /**
     *
     * @param i
     * @return
     */
    @Override
    public double get(int i) {
        if (values.containsKey(i))
            return values.get(i);
        else
            return 0;
    }

    /**
     *
     * @return
     */
    @Override
    public int size() {
        return size;
    }
    

    /**
     *
     * @param i
     * @param val
     */
    @Override
    public void set(int i, double val) {
        values.put(i, val);
    }

    /**
     *
     * @param alpha
     */
    @Override
    public void scale(double alpha) {
        for (int key : values.keySet())
            values.put(key, alpha * values.get(key));
    }

    /**
     *
     */
    @Override
    public void random() {
        for (int key : values.keySet())
            values.put(key, Math.random());
    }

    /**
     *
     * @param x
     */
    @Override
    public void minus(DoubleVector x) {
        DAXPY(-1, x);
    }

    /**
     *
     * @return
     */
    @Override
    public double DNRM2() {
        double nrm = 0;
        for (double s : values.values())
            nrm = NAUtils.hypot(nrm, s);

        return nrm;
    }

    /**
     *
     * @param alpha
     * @param x
     */
    @Override
    public void DAXPY(double alpha, DoubleVector x) {
        if (x.size() != size)
            throw new IndexOutOfBoundsException();

        for (int i = 0; i < size; i++)
            values.put(i, get(i) + alpha * x.get(i));
    }

    /**
     *
     * @param x
     * @return
     */
    @Override
    public double DDOT(DoubleVector x) {
        double dot = 0;
        if (x.size() != size)
            throw new IndexOutOfBoundsException();

        for (int index : values.keySet())
            dot += values.get(index) * x.get(index);

        return dot;
    }
    
    /**
     *
     * @return
     */
    @Override
    public List<Double> asList() {
        List<Double> list = new ArrayList<Double>();
        for ( int i = 0 ; i < size ; i++)
            list.add(get(i));  
        
        return list;
    }
}
