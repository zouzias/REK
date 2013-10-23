/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package org.zouzias.algorithms;

import org.junit.Test;
import static org.junit.Assert.assertTrue;
import org.zouzias.matrix.DenseMatrix;
import org.zouzias.matrix.DoubleMatrix;
import org.zouzias.matrix.SparseMatrix;
import org.zouzias.vector.DenseVector;
import org.zouzias.vector.DoubleVector;

/**
 *
 * @author azo
 */
public class REKSolverTest {
    
    private int m = 100, n = 10;
    private double maxSeconds = 3;
    private long MaxIterations = 10000;   

    /**
     * Test of solve method, of class REKSolver.
     */
    @Test
    public void testSolve_sparse() {
        System.out.println("solve(DoubleMatrix A, DoubleVector b, double MaxSeconds)");
        
        DoubleMatrix A    = new SparseMatrix(m, n);    A.random();
        DoubleVector xopt = new DenseVector(n);        xopt.random();
        DoubleVector b    = A.times(xopt);
        
               
        REKSolver instance = new REKSolver();
        
        DoubleVector x = instance.solve(A, b, maxSeconds);
        
        DoubleVector err = new DenseVector(x);
        err.minus(xopt);
        
        System.out.println("Error equals to " + err.DNRM2());      
        assertTrue("Error is not than 0.1\n Success", err.DNRM2() < 10e-1);
        
        A    = new SparseMatrix(m, n);    A.random();
        xopt = new DenseVector(n);        xopt.random();
        b    = A.times(xopt);
        x = instance.solve(A, b, MaxIterations);
        err = new DenseVector(x);
        err.minus(xopt);
        
        System.out.println("Error equals to " + err.DNRM2());
        assertTrue("Error is not than 0.1\n Success", err.DNRM2() < 10e-1);
    }

    /**
     * Test of solve method, of class REKSolver.
     */
    @Test
    public void testSolve_3args_2() {
        System.out.println("solve(DoubleMatrix A, DoubleVector b, long MaxIterations)");
        
        DoubleMatrix A    = new DenseMatrix(m, n);    A.random();
        DoubleVector xopt = new DenseVector(n);        xopt.random();
        DoubleVector b    = A.times(xopt);
        
        REKSolver instance = new REKSolver();
        
        DoubleVector x = instance.solve(A, b, maxSeconds);
        
        DoubleVector err = new DenseVector(x);
        err.minus(xopt);
        
        System.out.println("Error equals to " + err.DNRM2());      
        assertTrue("Error is not than 0.1\n Success", err.DNRM2() < 10e-1);
        
        A    = new DenseMatrix(m, n);    A.random();
        xopt = new DenseVector(n);        xopt.random();
        b    = A.times(xopt);
        x = instance.solve(A, b, MaxIterations);
        err = new DenseVector(x);
        err.minus(xopt);
        
        System.out.println("Error equals to " + err.DNRM2());
        assertTrue("Error is not than 0.1\n Success", err.DNRM2() < 10e-1);
       
    }
}