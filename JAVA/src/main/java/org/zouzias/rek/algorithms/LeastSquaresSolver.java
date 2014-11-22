package org.zouzias.algorithms;

import org.zouzias.matrix.DoubleMatrix;
import org.zouzias.vector.DoubleVector;

/** Interface for Least Squares Solvers. Given a real matrix A and real vector b, solves the problem
 *  min ||Ax - b|| so that x has the minimum Euclidean norm.
 *
 */
public interface LeastSquaresSolver {
    
    /** The solver will only run for MaxSeconds seconds and then will terminate
     *
     * @param A
     * @param b
     * @param MaxSeconds
     * @return
     */
    public DoubleVector solve(DoubleMatrix A, DoubleVector b, double MaxSeconds);   
    
    /** The solver will perform only MaxIterations iterations
     *
     * @param A A real matrix A
     * @param b A 
     * @param MaxIterations
     * @return
     */
    public DoubleVector solve(DoubleMatrix A, DoubleVector b, long MaxIterations);    
}
