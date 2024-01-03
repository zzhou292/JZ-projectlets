import numpy as np
from matplotlib import pyplot 

plot_every = 50

def distance(x1, y1, x2, y2):
    return np.sqrt((x1-x2)**2 + (y1-y2)**2)

def main():
    Nx = 400 # number of cells in x direction
    Ny = 100 # number of cells in y direction
    tau = 0.53  # kinematic viscosity
    Nt = 8000
    
    # lattice speeds and weights
    NL = 9
    cxs = np.array([0, 0, 1, 1, 1, 0, -1, -1, -1])
    cys = np.array([0, 1, 1, 0, -1, -1, -1, 0, 1])
    weights = np.array([4/9, 1/9, 1/36, 1/9, 1/36, 1/9, 1/36, 1/9, 1/36])
    
    # initial conditions
    F = np.ones((Ny, Nx, NL)) + .01*np.random.randn(Ny, Nx, NL)
    F[:,:,3] = 2.3
    
    cylinder = np.full((Ny, Nx), False)
    
    for x in range(Nx):
        for y in range(Ny):
            if distance(Nx//4, Ny//2, x, y) < 13:
                cylinder[y][x] = True
                
    # main loop
    for it in range(Nt):
        print(it)
        
        F[:,-1, [6,7,8]] = F[:,-2, [6,7,8]]
        F[:,0, [2,3,4]] = F[:,1, [2,3,4]]
        
        
        # streaming
        for i, cx, cy in zip(range(NL), cxs, cys):
            F[:,:,i] = np.roll(F[:,:,i], cx, axis=1)
            F[:,:,i] = np.roll(F[:,:,i], cy, axis=0)
            
        bndryF = F[cylinder,:]
        bndryF = bndryF[:,[0, 5, 6, 7, 8 ,1, 2, 3, 4]]
        
        # fluid variables
        rho = np.sum(F, 2)
        ux = np.sum(F*cxs, 2)/rho
        uy = np.sum(F*cys, 2)/rho
        
        F[cylinder,:] = bndryF
        ux[cylinder] = 0
        uy[cylinder] = 0
        
        # collision
        Feq = np.zeros(F.shape)
        for i, cx, cy, w in zip(range(NL), cxs, cys, weights):
            Feq[:,:,i] = rho*w*(1 + 3*(cx*ux + cy*uy) + 9*(cx*ux + cy*uy)**2/2 - 3*(ux**2 + uy**2)/2)
        F = F + 1/tau*(Feq - F)
            
            
        if(it%plot_every == 0):
            dfydx = ux[2:, 1:-1] - ux[0:-2, 1:-1]
            dfxdy = uy[1:-1, 2:] - uy[1:-1, 0:-2]
            curl = dfydx -dfxdy
            #pyplot.imshow(np.sqrt(ux**2 + uy**2))
            # Plot for curl
            pyplot.figure(1)  # Create a new figure for curl
            pyplot.imshow(curl, cmap="bwr")
            pyplot.title("Curl of the vector field")
            pyplot.pause(0.005)
            pyplot.cla()

            # Plot for magnitude of the vector field
            magnitude = np.sqrt(ux**2 + uy**2)
            pyplot.figure(2)  # Create a new figure for magnitude
            pyplot.imshow(magnitude, cmap="viridis")
            pyplot.title("Magnitude of the vector field")
            pyplot.pause(0.005)
            pyplot.cla()
        
        
    
    
if __name__ == "__main__":
    main()