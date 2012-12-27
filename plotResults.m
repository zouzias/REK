%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Plot Results
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

m = 20000;
n = 600;

A = 100 * sprandn(m, n, 0.01);
b = 100 * randn(m, 1);

precond = 1 ./ sqrt( sum(A.^2, 1) );
A = A * diag(precond); 

A = full(A);
A = sparse(A);

disp('**************************')
disp( sprintf('Matlab''s solver backslash '));
disp('**************************')

tic;
xopt = A\b;
toc

myerr = testREK(A, b, xopt);

figure;
hold on;
plot(1 : numel(myerr), myerr     , 'r-', 'LineWidth', 2, 'Markersize', 10); 

title('Convergence of Randomized Extended Kaczmarz Algorithm', 'fontsize', 16);
xlabel('# of iterations (t)', 'fontsize', 14);
ylabel('Error from x_{LS}', 'fontsize', 16);
legend('REK');

hold off;