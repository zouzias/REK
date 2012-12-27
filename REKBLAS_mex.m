% LSSOLVER_MEX  Randomized Extended Kaczmarz Algorithm
%
% Syntax:  [x, dt] = REKBLAS_mex(A, b, MAXITERS, TOL)
%
% Inputs:
%    A        - An m x n real matrix (sparse or dense)
%    b        - m-vector
%    MAXITERS - Maximum number of iterations
%    TOL      - Tolerance of algorithm   
%
% Outputs:
%    x - Approximate solution to the minimum Euclidean norm least squares solution of Ax=b
%
% Example: 
%    A = randn(1000, 50);
%    b = randn(1000,1);
%    xopt = A \ b;
%    norm( A * (x - xopt), 'inf' )
%
% Other m-files required: none
% Subfunctions: none
% MAT-files required: none
%
% See also: testREK

% Author: Anastasios Zouzias
% University of Toronto
% email: zouzias@cs.toronto.edu
% Website: http://www.cs.toronto.edu/~zouzias
% September 2012; Last revision: 27-December-2012
% Copyright (C) 2012, Anastasios Zouzias

%------------- BEGIN CODE --------------

% See REKBLAS_mex.c

%-------------  END  CODE --------------
