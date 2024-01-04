#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

const int Nx = 200;
const int Ny = 50;
const int Nz = 50;
const double tau = 0.53;
const int Nt = 8000;
const int NL = 19;

double distance(int x1, int y1, int z1, int x2, int y2, int z2) {
  return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2)) +
         std::pow(z1 - z2, 2);
}

void saveToCSV(int timestep,
               const std::vector<std::vector<std::vector<double>>> &ux,
               const std::vector<std::vector<std::vector<double>>> &uy,
               const std::vector<std::vector<std::vector<double>>> &uz, int Nx,
               int Ny, int Nz) {
  std::string filename = "velocity_data_" + std::to_string(timestep) + ".csv";
  std::ofstream outFile(filename);

  outFile << "x,y,z, velocity_magnitude_squared\n";

  /*
    for (int z = 0; z < Nz; ++z) {
      for (int y = 0; y < Ny; ++y) {
        for (int x = 0; x < Nx; ++x) {
          double velocity_magnitude_squared = ux[z][y][x] * ux[z][y][x] +
                                              uy[z][y][x] * uy[z][y][x] +
                                              uz[z][y][x] * uz[z][y][x];
          outFile << x << "," << y << "," << z << ","
                  << velocity_magnitude_squared << "\n";
        }
      }
    }
    */

  for (int y = 0; y < Ny; ++y) {
    for (int x = 0; x < Nx; ++x) {
      double velocity_magnitude_squared = ux[Nz / 2][y][x] * ux[Nz / 2][y][x] +
                                          uy[Nz / 2][y][x] * uy[Nz / 2][y][x] +
                                          uz[Nz / 2][y][x] * uz[Nz / 2][y][x];
      outFile << x << "," << y << "," << Nz / 2 << ","
              << velocity_magnitude_squared << "\n";
    }
  }

  outFile.close();
}

int main() {
  // Lattice speeds and weights for D3Q19
  // Lattice speeds for D3Q19
  std::vector<int> cxs = {0, 1, -1, 0, 0, 0,  0, 1, -1, -1,
                          1, 1, -1, 0, 0, -1, 1, 0, 0};
  std::vector<int> cys = {0,  0, 0, 1, -1, 0, 0, 1,  -1, 1,
                          -1, 0, 0, 1, -1, 0, 0, -1, 1};
  std::vector<int> czs = {0, 0, 0,  0, 0,  1, -1, 0, 0, 0,
                          0, 1, -1, 1, -1, 1, -1, 1, -1};

  // Weights for D3Q19
  std::vector<double> weights = {
      1.0 / 3,  1.0 / 18, 1.0 / 18, 1.0 / 18, 1.0 / 18, 1.0 / 18, 1.0 / 18,
      1.0 / 36, 1.0 / 36, 1.0 / 36, 1.0 / 36, 1.0 / 36, 1.0 / 36, 1.0 / 36,
      1.0 / 36, 1.0 / 36, 1.0 / 36, 1.0 / 36, 1.0 / 36};

  // Initialize F
  std::vector<std::vector<std::vector<std::vector<double>>>> F(
      Nz, std::vector<std::vector<std::vector<double>>>(
              Ny, std::vector<std::vector<double>>(
                      Nx, std::vector<double>(NL, 1.0))));

  // Random number generation
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(0, 0.01);

  for (int z = 0; z < Nz; ++z) {
    for (int y = 0; y < Ny; ++y) {
      for (int x = 0; x < Nx; ++x) {
        for (int l = 0; l < NL; ++l) {
          F[z][y][x][l] += dis(gen);
          F[z][y][x][1] = 3.3;
          // Adjust initialization as needed
        }
      }
    }
  }

  // Initialize sphere
  std::vector<std::vector<std::vector<bool>>> sphere(
      Nz, std::vector<std::vector<bool>>(Ny, std::vector<bool>(Nx, false)));
  for (int z = 0; z < Nz; ++z) {
    for (int y = 0; y < Ny; ++y) {
      for (int x = 0; x < Nx; ++x) {
        if (distance(Nx / 4, Ny / 2, Nz / 2, x, y, z) < 7) {
          sphere[z][y][x] = true;
        }
      }
    }
  }

  for (int it = 0; it < Nt; it++) {
    std::cout << it << std::endl;

    // Boundary conditions
    // Loop through all the boundaries and set the appropriate distribution
    // functions
    for (int z = 0; z < Nz; ++z) {
      for (int y = 0; y < Ny; ++y) {
        // Left and right boundaries in x-direction
        for (int i : {1, 7, 10, 11, 16}) { // Indices pointing right
          F[z][y][0][i] = F[z][y][1][i];   // Left boundary
        }
        for (int i : {2, 8, 9, 12, 15}) {          // Indices pointing left
          F[z][y][Nx - 1][i] = F[z][y][Nx - 2][i]; // Right boundary
        }
      }
      for (int x = 0; x < Nx; ++x) {
        // Top and bottom boundaries in y-direction
        for (int i : {3, 7, 9, 13, 18}) { // Indices pointing upwards
          F[z][0][x][i] = F[z][1][x][i];  // Bottom boundary
        }
        for (int i : {4, 8, 10, 14, 17}) {         // Indices pointing downwards
          F[z][Ny - 1][x][i] = F[z][Ny - 2][x][i]; // Top boundary
        }
      }
    }

    for (int y = 0; y < Ny; ++y) {
      for (int x = 0; x < Nx; ++x) {
        // Front and back boundaries in z-direction
        for (int i : {5, 11, 13, 15, 17}) { // Indices pointing outwards
          F[0][y][x][i] = F[1][y][x][i];    // Front boundary
        }
        for (int i : {6, 12, 14, 16, 18}) {        // Indices pointing inwards
          F[Nz - 1][y][x][i] = F[Nz - 2][y][x][i]; // Back boundary
        }
      }
    }

    // Streaming in 3D
    for (int i = 0; i < NL; ++i) {
      int cx = cxs[i];
      int cy = cys[i];
      int cz = czs[i];

      // Create a temporary copy of the current distribution
      auto F_temp = F;

      // Roll in x-direction
      for (int z = 0; z < Nz; ++z) {
        for (int y = 0; y < Ny; ++y) {
          for (int x = 0; x < Nx; ++x) {
            int rolled_x = (x + cx + Nx) % Nx;
            F_temp[z][y][rolled_x][i] = F[z][y][x][i];
          }
        }
      }

      // Roll in y-direction
      for (int z = 0; z < Nz; ++z) {
        for (int y = 0; y < Ny; ++y) {
          for (int x = 0; x < Nx; ++x) {
            int rolled_y = (y + cy + Ny) % Ny;
            F_temp[z][rolled_y][x][i] = F_temp[z][y][x][i];
          }
        }
      }

      // Roll in z-direction
      for (int z = 0; z < Nz; ++z) {
        for (int y = 0; y < Ny; ++y) {
          for (int x = 0; x < Nx; ++x) {
            int rolled_z = (z + cz + Nz) % Nz;
            F[rolled_z][y][x][i] = F_temp[z][y][x][i];
          }
        }
      }
    }

    // Boundary F and other computations for 3D

    std::vector<std::vector<std::vector<std::vector<double>>>> bndryF(
        Nz, std::vector<std::vector<std::vector<double>>>(
                Ny, std::vector<std::vector<double>>(
                        Nx, std::vector<double>(NL, 0.0))));

    for (int z = 0; z < Nz; ++z) {
      for (int y = 0; y < Ny; ++y) {
        for (int x = 0; x < Nx; ++x) {
          if (sphere[z][y]
                    [x]) { // Check if the current cell is inside the sphere
            for (int i = 0; i < NL; ++i) {
              bndryF[z][y][x][i] = F[z][y][x][i];
            }
          }
        }
      }
    }

    // Now, rearrange elements within each row of bndryF
    std::vector<int> newOrder = {0, 2,  1,  4,  3,  6,  5,  8,  7, 10,
                                 9, 12, 11, 14, 13, 16, 15, 18, 17};

    // Rearrange elements within each cell of bndryF for 3D
    for (int z = 0; z < Nz; ++z) {
      for (int y = 0; y < Ny; ++y) {
        for (int x = 0; x < Nx; ++x) {
          std::vector<double> tempCell = bndryF[z][y][x];
          for (int i = 0; i < NL; ++i) {
            bndryF[z][y][x][i] = tempCell[newOrder[i]];
          }
        }
      }
    }

    // Calculating rho, ux, uy, and uz in 3D
    std::vector<std::vector<std::vector<double>>> rho(
        Nz, std::vector<std::vector<double>>(Ny, std::vector<double>(Nx, 0.0)));
    std::vector<std::vector<std::vector<double>>> ux(
        Nz, std::vector<std::vector<double>>(Ny, std::vector<double>(Nx, 0.0)));
    std::vector<std::vector<std::vector<double>>> uy(
        Nz, std::vector<std::vector<double>>(Ny, std::vector<double>(Nx, 0.0)));
    std::vector<std::vector<std::vector<double>>> uz(
        Nz, std::vector<std::vector<double>>(Ny, std::vector<double>(Nx, 0.0)));

    for (int z = 0; z < Nz; ++z) {
      for (int y = 0; y < Ny; ++y) {
        for (int x = 0; x < Nx; ++x) {
          for (int i = 0; i < NL; ++i) {
            rho[z][y][x] += F[z][y][x][i];
            ux[z][y][x] += cxs[i] * F[z][y][x][i];
            uy[z][y][x] += cys[i] * F[z][y][x][i];
            uz[z][y][x] += czs[i] * F[z][y][x][i];
          }
          ux[z][y][x] /= rho[z][y][x];
          uy[z][y][x] /= rho[z][y][x];
          uz[z][y][x] /= rho[z][y][x];
        }
      }
    }

    for (int z = 0; z < Nz; ++z) {
      for (int y = 0; y < Ny; ++y) {
        for (int x = 0; x < Nx; ++x) {
          if (sphere[z][y][x]) {
            // Replace the corresponding elements in F with those from bndryF
            for (int i = 0; i < NL; ++i) {
              F[z][y][x][i] = bndryF[z][y][x][i];
            }

            // Set ux, uy, and uz to 0 at this position
            ux[z][y][x] = 0;
            uy[z][y][x] = 0;
            uz[z][y][x] = 0;
          }
        }
      }
    }

    // Collision step in 3D

    std::vector<std::vector<std::vector<std::vector<double>>>> Feq(
        Nz, std::vector<std::vector<std::vector<double>>>(
                Ny, std::vector<std::vector<double>>(
                        Nx, std::vector<double>(NL, 0.0))));

    for (int z = 0; z < Nz; ++z) {
      for (int y = 0; y < Ny; ++y) {
        for (int x = 0; x < Nx; ++x) {
          for (int i = 0; i < NL; ++i) {
            double cu = 3 * (cxs[i] * ux[z][y][x] + cys[i] * uy[z][y][x] +
                             czs[i] * uz[z][y][x]);
            Feq[z][y][x][i] =
                rho[z][y][x] * weights[i] *
                (1 + cu + 0.5 * cu * cu -
                 1.5 * (ux[z][y][x] * ux[z][y][x] + uy[z][y][x] * uy[z][y][x] +
                        uz[z][y][x] * uz[z][y][x]));
          }
        }
      }
    }

    // Updating F

    for (int z = 0; z < Nz; ++z) {
      for (int y = 0; y < Ny; ++y) {
        for (int x = 0; x < Nx; ++x) {
          for (int i = 0; i < NL; ++i) {
            F[z][y][x][i] += 1 / tau * (Feq[z][y][x][i] - F[z][y][x][i]);
          }
        }
      }
    }

    // Save data to CSV
    if (it % 10 == 0) {
      saveToCSV(it, ux, uy, uz, Nx, Ny, Nz);
    }
  }

  return 0;
}