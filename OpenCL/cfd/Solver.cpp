#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

const int Nx = 400;
const int Ny = 100;
const double tau = 0.53;
const int Nt = 8000;
const int NL = 9;

double distance(int x1, int y1, int x2, int y2) {
  return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

void saveToCSV(int timestep, const std::vector<std::vector<double>> &ux,
               const std::vector<std::vector<double>> &uy, int Nx, int Ny) {
  std::string filename = "velocity_data_" + std::to_string(timestep) + ".csv";
  std::ofstream outFile(filename);

  outFile << "x,y,velocity_magnitude_squared\n";

  for (int y = 0; y < Ny; ++y) {
    for (int x = 0; x < Nx; ++x) {
      double velocity_magnitude_squared =
          ux[y][x] * ux[y][x] + uy[y][x] * uy[y][x];
      outFile << x << "," << y << "," << velocity_magnitude_squared << "\n";
    }
  }

  outFile.close();
}

int main() {
  // Lattice speeds and weights
  std::vector<int> cxs = {0, 0, 1, 1, 1, 0, -1, -1, -1};
  std::vector<int> cys = {0, 1, 1, 0, -1, -1, -1, 0, 1};
  std::vector<double> weights = {4.0 / 9, 1.0 / 9,  1.0 / 36, 1.0 / 9, 1.0 / 36,
                                 1.0 / 9, 1.0 / 36, 1.0 / 9,  1.0 / 36};

  // Initialize F
  std::vector<std::vector<std::vector<double>>> F(
      Ny, std::vector<std::vector<double>>(Nx, std::vector<double>(NL, 1.0)));

  // Random number generation
  std::random_device rd;
  std::mt19937 gen(rd());
  std::normal_distribution<> dis(0, 0.01);

  for (int y = 0; y < Ny; ++y) {
    for (int x = 0; x < Nx; ++x) {
      for (int l = 0; l < NL; ++l) {
        F[y][x][l] += dis(gen);
        F[y][x][3] = 2.3;
      }
    }
  }

  // Initialize cylinder
  std::vector<std::vector<bool>> cylinder(Ny, std::vector<bool>(Nx, false));
  for (int x = 0; x < Nx; ++x) {
    for (int y = 0; y < Ny; ++y) {
      if (distance(Nx / 4, Ny / 2, x, y) < 13) {
        cylinder[y][x] = true;
      }
    }
  }

  for (int it = 0; it < Nt; it++) {
    std::cout << it << std::endl;

    // Boundary conditions
    for (int y = 0; y < Ny; ++y) {
      for (int i : {6, 7, 8}) {
        F[y][Nx - 1][i] = F[y][Nx - 2][i];
      }
      for (int i : {2, 3, 4}) {
        F[y][0][i] = F[y][1][i];
      }
    }

    // Streaming (Implementing np.roll equivalent)
    // This is a simplified version and needs to be adapted for your specific
    // needs

    for (int i = 0; i < NL; ++i) {
      int cx = cxs[i];
      int cy = cys[i];

      // Create a temporary copy of the current layer
      auto F_temp = F;

      // Roll in x-direction
      for (int y = 0; y < Ny; ++y) {
        for (int x = 0; x < Nx; ++x) {
          int rolled_x = (x + cx + Nx) % Nx;
          F_temp[y][rolled_x][i] = F[y][x][i];
        }
      }

      // Roll in y-direction
      for (int y = 0; y < Ny; ++y) {
        for (int x = 0; x < Nx; ++x) {
          int rolled_y = (y + cy + Ny) % Ny;
          F[y][x][i] = F_temp[rolled_y][x][i];
        }
      }
    }

    // bndryF and other computations

    std::vector<std::vector<std::vector<double>>> bndryF(
        Ny, std::vector<std::vector<double>>(Nx, std::vector<double>(NL, 0.0)));
    for (int y = 0; y < Ny; ++y) {
      for (int x = 0; x < Nx; ++x) {
        if (cylinder[y][x]) {
          for (int i = 0; i < NL; ++i) {
            bndryF[y][x][i] = F[y][x][i];
          }
        }
      }
    }

    // Now, rearrange elements within each row of bndryF
    std::vector<int> newOrder = {0, 5, 6, 7, 8, 1, 2, 3, 4};
    for (auto &row : bndryF) {
      std::vector<std::vector<double>> tempRow = row;
      for (int x = 0; x < Nx; ++x) {
        for (int i = 0; i < NL; ++i) {
          row[x][i] = tempRow[x][newOrder[i]];
        }
      }
    }

    // Calculating rho, ux, and uy
    std::vector<std::vector<double>> rho(Ny, std::vector<double>(Nx, 0.0));
    std::vector<std::vector<double>> ux(Ny, std::vector<double>(Nx, 0.0));
    std::vector<std::vector<double>> uy(Ny, std::vector<double>(Nx, 0.0));
    for (int y = 0; y < Ny; ++y) {
      for (int x = 0; x < Nx; ++x) {
        for (int i = 0; i < NL; ++i) {
          rho[y][x] += F[y][x][i];
          ux[y][x] += cxs[i] * F[y][x][i];
          uy[y][x] += cys[i] * F[y][x][i];
        }
        ux[y][x] /= rho[y][x];
        uy[y][x] /= rho[y][x];
      }
    }

    for (int y = 0; y < Ny; ++y) {
      for (int x = 0; x < Nx; ++x) {
        if (cylinder[y][x]) {
          // Replace the corresponding elements in F with those from bndryF
          for (int i = 0; i < NL; ++i) {
            F[y][x][i] = bndryF[y][x][i];
          }

          // Set ux and uy to 0 at this position
          ux[y][x] = 0;
          uy[y][x] = 0;
        }
      }
    }

    // Collision step

    std::vector<std::vector<std::vector<double>>> Feq(
        Ny, std::vector<std::vector<double>>(Nx, std::vector<double>(NL, 0.0)));
    for (int y = 0; y < Ny; ++y) {
      for (int x = 0; x < Nx; ++x) {
        for (int i = 0; i < NL; ++i) {
          double cu = 3 * (cxs[i] * ux[y][x] + cys[i] * uy[y][x]);
          Feq[y][x][i] = rho[y][x] * weights[i] *
                         (1 + cu + 0.5 * cu * cu -
                          1.5 * (ux[y][x] * ux[y][x] + uy[y][x] * uy[y][x]));
        }
      }
    }

    // Updating F

    for (int y = 0; y < Ny; ++y) {
      for (int x = 0; x < Nx; ++x) {
        for (int i = 0; i < NL; ++i) {
          F[y][x][i] += 1 / tau * (Feq[y][x][i] - F[y][x][i]);
        }
      }
    }

    // Output to CSV
    saveToCSV(it, ux, uy, Nx, Ny);
  }

  return 0;
}
