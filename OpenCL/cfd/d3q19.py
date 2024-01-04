import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Data for velocity vectors in D3Q19 model
cxs = [0,1,-1,0,0,0,0,1,-1,-1,1,1,-1,0,0,-1,1,0,0]
cys = [0,0,0,1,-1,0,0,1,-1,1,-1,0,0,1,-1,0,0,-1,1]
czs = [0,0,0,0,0,1,-1,0,0,0,0,1,-1,1,-1,1,-1,1,-1]

# Create a 3D plot
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

# Plot each point and attach the index as text
for i, (x, y, z) in enumerate(zip(cxs, cys, czs)):
    ax.scatter(x, y, z, color='b')
    ax.text(x, y, z, f'{i}', color='red', fontsize=10)

# Setting labels
ax.set_xlabel('X Axis')
ax.set_ylabel('Y Axis')
ax.set_zlabel('Z Axis')
ax.set_title('D3Q19 Lattice Velocities')

# Show the plot
plt.show()
