%% Solve with mesh refinement
clear all;close all;format compact;

obs = [5.0 -8.0 -5.0;
       0.0 -1.0 -10.0;
       5 3 3];


[problem,guess] = fp(obs);          % Fetch the problem definition
options= problem.settings(3000);                  % Get options and solver settings 
[solution,MRHistory]=solveMyProblem(problem,guess,options);
genSolutionPlots(options, solution);


figure;
plot(solution.X(:,1),solution.X(:,2));
grid on;
xlim([-25 25]);
ylim([-25 25]);
hold on;

size_obs_mat = size(obs);
n_obs = size_obs_mat(2);
for i = 1:n_obs
    rectangle('Position',[obs(1,i)-obs(3,i)/2 obs(2,i)-obs(3,i)/2 obs(3,i)*2 obs(3,i)*2])
end
