
function [dx,g_neq] = fp_Dynamics_Internal(x,u,p,t,data)

obs = data.auxdata;


%------------- BEGIN CODE --------------
x1 = x(:,1);
x2 = x(:,2);
x3 = x(:,3);

u1 = u(:,1);
u2 = u(:,2);

dx(:,1) = cos(x3).*u1;
dx(:,2) = sin(x3).*u1;
dx(:,3) = u1.* tan(u2) / 0.75;

dx = [cos(x3).*u1, sin(x3).*u1,u1.* tan(u2) / 0.75];

size_obs_mat = size(obs);
n_obs = size_obs_mat(2);

for i = 1:n_obs
      g_neq(:,2*(i-1)+1) = abs(x1-obs(1,i));
      g_neq(:,2*(i-1)+2) = abs(x2-obs(2,i));
end

%------------- END OF CODE --------------