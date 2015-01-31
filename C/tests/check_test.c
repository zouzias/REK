#include <stdlib.h>
#include "../matrix/sparseMatrix.h"
#include "../matrix/matrix.h"
#include "../utils/utils.h"
#include "../algorithms/REK/REKBLAS.h"

#include<check.h>

double test_dense_gaussian_system(int m, int n, double TOL);

double test_sparse_gaussian_system(int m, int n, double sparsity, double TOL);

START_TEST (test_name)
{
  /* unit test code */
ck_assert_msg(0 != 1);
}
END_TEST

START_TEST (test_dense_gaussian)
{
	ck_assert_msg( test_dense_gaussian_system(1000, 100, 10e-7) < 10e-4 ); // Test if accuracy less than 5 digits
}
END_TEST

START_TEST (test_sparse_gaussian)
{
	ck_assert_msg( test_sparse_gaussian_system(1000, 100, 0.2, 10e-7) < 10e-4 ); // Test if accuracy less than 5 digits
}
END_TEST

double test_dense_gaussian_system(int m, int n, double TOL){
    printf("--->Test REK for dense (%dx%d)-matrix.\n", m, n);

    /* initialize random seed */
    srand(time(NULL));
    
    // Allocating space for unknown vector x, right size vector b, and solution vector xls, for Ax = b
    double *xls = gaussianVector(n);
    double* b = (double*) malloc( m * sizeof(double));
    double* x = (double*) malloc( n * sizeof(double));
    memset (x, 0, n * sizeof (double));
    
    // LS Error
    double error = 0.0;
    
    //**********************************************
    // Test the dense version of REK               *
    //**********************************************
    MAT *A = fillRandomEntries(m, n);
    
    memset (b, 0, m * sizeof (double));
    memset (x, 0, n * sizeof (double));
    myDGEMV(A,xls, b);
    denseREKBLAS(A, x, b, TOL);
    error = lsError(A, x, b);
    freeMAT(A);
    
    printf("Dense REK: LS error is : %e\n", error);

    free(xls);
    free(x);
    free(b);
    
    return error;
 }

  double test_sparse_gaussian_system(int m, int n, double sparsity, double TOL){
    printf("--->Test REK for sparse (%dx%d)-matrix with sparsity %f.\n", m, n, sparsity);

    /* initialize random seed */
    srand(time(NULL));
    
    // Allocating space for unknown vector x, right size vector b, and solution vector xls, for Ax = b
    double *xls = gaussianVector(n);
    double* b = (double*) malloc( m * sizeof(double));
    double* x = (double*) malloc( n * sizeof(double));
    memset (x, 0, n * sizeof (double));
    memset (b, 0, m * sizeof (double));
    
    // LS Error
    double error = 0.0;
    
    // Input matrix is sparse (REK_sparse)
    SMAT *As = fillSparseMat(m, n, sparsity);
    
    // Set b = As * x
    myDGEMVSparse(As,xls, b);
    
    //**********************************************
    // Test the sparse version of REK              *
    //**********************************************
    sparseREK (As, x, b, TOL);
    error = lsErrorSparse(As, x, b);
    freeSMAT(As);
    
    printf("Sparse REK: LS error is : %e\n", error);
    

    free(xls);
    free(x);
    free(b);
    
    return error;
 }




Suite * unit_test_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Unit_tests_temp");

    /* Core test case */
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_name);
    tcase_add_test(tc_core, test_dense_gaussian);
    tcase_add_test(tc_core, test_sparse_gaussian);
    suite_add_tcase(s, tc_core);

    return s;
}

 int main(void)
 {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = unit_test_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

