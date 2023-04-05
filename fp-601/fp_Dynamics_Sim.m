function [dx] = fp_Dynamics_Sim(x,u,p,t,data)

%------------- BEGIN CODE --------------
x1 = x(:,1);
x2 = x(:,2);
x3 = x(:,3);

u1 = u(:,1);
u2 = u(:,2);

dx = [cos(x3).*u1, sin(x3).*u1,u1.* tan(u2) / 0.75];

%------------- END OF CODE --------------