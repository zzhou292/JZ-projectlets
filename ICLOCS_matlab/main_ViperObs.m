% main_CarParking - Main script to solve the Optimal Control Problem 
%
% Minimum Time Parallel Parking
% The problem was adapted from 
% B. Li, K. Wang, and Z. Shao, "Time-optimal maneuver planning in automatic parallel parking using a simultaneous dynamic optimization approach". IEEE Transactions on Intelligent Transportation Systems, 17(11), pp.3263-3274, 2016.
%
% Copyright (C) 2019 Yuanbo Nie, Omar Faqir, and Eric Kerrigan. All Rights Reserved.
% The contribution of Paola Falugi, Eric Kerrigan and Eugene van Wyk for the work on ICLOCS Version 1 (2010) is kindly acknowledged.
% This code is published under the MIT License.
% Department of Aeronautics and Department of Electrical and Electronic Engineering,
% Imperial College London London  England, UK 
% ICLOCS (Imperial College London Optimal Control) Version 2.5 
% 1 Aug 2019
% iclocs@imperial.ac.uk

%--------------------------------------------------------

clear all;close all;format compact;

obs_data=[2 -4 0 3 -3 7 4 -8 7.6 -8.1;
    0 -1 1.2 5 2 1 -7 5 -4 -2.3;
    1.5 1.5 1.5 1.5 1.5 1.5 1.5 1.5 1.5 1.5]; % obstacle data is formatted as a matrix, each column is 0 
% xcenter,ycenter,size
pos0_x = -5; % initial rover x location
pos0_y = -6; % initial rover y location
posf_x = 0; % final rover x location
posf_y = 8; % final rover y location
rot0 = 60;


[problem,guess]=ViperObs(obs_data, pos0_x, pos0_y, posf_x, posf_y, rot0);          % Fetch the problem definition
options= problem.settings(200);                  % Get options and solver settings 
[solution,MRHistory]=solveMyProblem( problem,guess,options);

%%
xx=linspace(solution.T(1,1),solution.tf,100);
posx=speval(solution,'X',1,xx);
posy=speval(solution,'X',2,xx);
theta=speval(solution,'X',4,xx);

%%
xx=linspace(solution.T(1,1),solution.tf,100);

figure
hold on
plot(solution.X(:,1),solution.X(:,2),'go','linewidth', 1)
grid on;
xlim([-10 10]);
ylim([-10 10]);
xlabel('Position x [m]');
ylabel('Position y [m]');

num_obs = size(obs_data,2);
for i = 1:num_obs
    %// radius
    r = obs_data(3,i);
    %// center
    c = [obs_data(1,i) obs_data(2,i)];
    pos = [c-r 2*r 2*r];
    rectangle('Position',pos,'Curvature',[1 1])
    axis equal
end

filename = 'traj_data.csv'; % Name of the CSV file to create
fid = fopen(filename, 'w'); % Open the file for writing

% Write the header row
fprintf(fid, 'x,y\n');

num_node=size(solution.X,1);
% Write the data rows
for i = 1:num_node
    fprintf(fid, '%f,%f\n', solution.X(i,1), solution.X(i,2));
end

fclose(fid); % Close the file


