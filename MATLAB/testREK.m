function [myerr] = testREK(A, b, xopt)
% TESTREK  Test function for Randomized Kaczmarz Method 
%
% Syntax:  myerr = testREK(A, b, xopt)
%
% Inputs:
%    A - An m x n matrix
%    b - m-vector
%    xopt - xopt = A \ b
%
% Outputs:
%    myerr - A vector containing the error for different number of iterations
%
% Example: 
%    A = randn(3000, 100);
%    b = randn(3000,1);
%    xopt = A \ b;
%    myerr = testREK(A, b, xopt);
%
% Other m-files required: REKBLAS_mex
% Subfunctions: none
% MAT-files required: none
%
% See also: REKBLAS_mex

% Author: Anastasios Zouzias
% University of Toronto
% email: zouzias@cs.toronto.edu
% Website: http://www.cs.toronto.edu/~zouzias
% September 2012; Last revision: 27-December-2012
% Copyright (C) 2012, Anastasios Zouzias

%------------- BEGIN CODE --------------


REPS = 4;

TOL = (0.1).^[1:14];

myerr = zeros(numel( TOL), 1);

for i = 1 : numel(TOL)
    
    disp('**************************')
    disp( sprintf('Iters # %d out of %d', i, numel(TOL) ) );
    disp( sprintf('Stopping accuracy %f', TOL(i) ) );

    %avg = 0;
    %for i = 1 : REPS
        [x, dt] = REKBLAS_mex(A, b, TOL(i));
    %    avg = avg + dt;
    %end
    %avg = avg / REPS;
    
    myerr(i) = norm( A * (x - xopt), 'inf' );
end


end

%------------- END OF CODE --------------
