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

obs_data=[2 -10 0 11 -3 17 20 -10 10 -20;
    0 -10 -10 4 10 7 -10 5 -15 15;
    4 4 3 2 2 3 5 3 2 2]; % obstacle data is formatted as a matrix, each column is 0 
% xcenter,ycenter,size
pos0_x = 0; % initial rover x location
pos0_y = -20; % initial rover y location
posf_x = 20; % final rover x location
posf_y = 20; % final rover y location
rot0 = 60;


[problem,guess]=CarParking(obs_data, pos0_x, pos0_y, posf_x, posf_y, rot0);          % Fetch the problem definition
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
plot(solution.X(:,1),solution.X(:,2),'go','linewidth', 2)
grid on;
xlim([-25 25]);
ylim([-25 25]);
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


