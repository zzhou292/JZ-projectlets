function [dx,g_neq] = CarParking_Dynamics_Internal(x,u,p,t,vdat)
% Dynamics for Internal Model
%
% Syntax:  
%          [dx] = Dynamics(x,u,p,t,vdat)	(Dynamics Only)
%          [dx,g_eq] = Dynamics(x,u,p,t,vdat)   (Dynamics and Eqaulity Path Constraints)
%          [dx,g_neq] = Dynamics(x,u,p,t,vdat)   (Dynamics and Inqaulity Path Constraints)
%          [dx,g_eq,g_neq] = Dynamics(x,u,p,t,vdat)   (Dynamics, Equality and Ineqaulity Path Constraints)
% 
% Inputs:
%    x  - state vector
%    u  - input
%    p  - parameter
%    t  - time
%    vdat - structured variable containing the values of additional data used inside
%          the function%      
% Output:
%    dx - time derivative of x
%    g_eq - constraint function for equality constraints
%    g_neq - constraint function for inequality constraints
%
% Copyright (C) 2019 Yuanbo Nie, Omar Faqir, and Eric Kerrigan. All Rights Reserved.
% The contribution of Paola Falugi, Eric Kerrigan and Eugene van Wyk for the work on ICLOCS Version 1 (2010) is kindly acknowledged.
% This code is published under the MIT License.
% Department of Aeronautics and Department of Electrical and Electronic Engineering,
% Imperial College London London  England, UK 
% ICLOCS (Imperial College London Optimal Control) Version 2.5 
% 1 Aug 2019
% iclocs@imperial.ac.uk

auxdata = vdat.auxdata;
obs_data = auxdata.obs_data;
num_obs=size(obs_data,2);

posx = x(:,1);
posy = x(:,2);
v = x(:,3);
theta = x(:,4);
phi = x(:,5);
a=u(:,1);
u2=u(:,2);

posx_dot=v.*cos(theta);
posy_dot=v.*sin(theta);
v_dot=a;
theta_dot=v.*tan(phi)./auxdata.l_axes;
phi_dot=u2;

curvature_dot=u2./auxdata.l_axes./(cos(phi)).^2;
 
%% return dynamics and inequality constraints
dx = [posx_dot, posy_dot, v_dot, theta_dot, phi_dot];
g_neq(:,1) = curvature_dot;

for i=1:num_obs
    g_neq(:,i+1) = (posx-obs_data(1,i)).*(posx-obs_data(1,i))+(posy-obs_data(2,i)).*(posy-obs_data(2,i));
end

