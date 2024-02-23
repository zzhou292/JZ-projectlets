#include <algorithm>
#include <climits>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <random> // For std::random_device and std::mt19937
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
// =========================
// Definition form the system perspective
// =========================

using namespace std;

struct Net;

// cell data struture
struct Cell {
  std::vector<Net *> nets;
  int gain;
  std::string name;
  // int weight;

  bool partition; // true for P1, false for P2.

  // iterator
  std::list<Cell *>::iterator satellite;
};

// net data structure
struct Net {
  std::vector<Cell *> cells;
};

class FMPartitioner {
public:
  // Read the input file and store the data
  void readInput(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;

    // Read the balance factor
    if (getline(file, line)) {
      std::istringstream iss(line);
      iss >> balanceFactor;
      balanceFactor = balanceFactor;
    }

    unordered_map<std::string, Net *> netMap;

    // Read each net and cell, store them separately
    while (getline(file, line)) {
      if (line.substr(0, 3) == "NET") {
        std::istringstream iss(line);
        std::string netName, cellName;

        iss >> netName; // Skip the "NET" keyword
        iss >> netName; // Read the actual net name

        Net *newNet = new Net();
        netMap[netName] = newNet;
        _nets.push_back(newNet); // Store the net

        // Read cell names
        while (iss >> cellName && cellName != ";") {
          if (cellMap.find(cellName) == cellMap.end()) {
            Cell newCell;
            newCell.name = cellName;
            cellMap[cellName] = _cells.size();
            _cells.push_back(newCell);
          }
        }
      } else {
        std::istringstream iss(line);
        std::string cellName;
        while (iss >> cellName && cellName != ";") {
          if (cellMap.find(cellName) == cellMap.end()) {
            Cell newCell;
            newCell.name = cellName;
            cellMap[cellName] = _cells.size();
            _cells.push_back(newCell);
          }
        }
      }
    }

    file.close();

    // Link cells and nets
    file.open(filename); // Re-open the file to read again
    getline(file, line); // Skip the balance factor line
    std::string netName;
    while (getline(file, line)) {
      if (line.substr(0, 3) == "NET") {
        std::istringstream iss(line);
        std::string cellName;

        iss >> netName; // Skip the "NET" keyword
        iss >> netName; // Read the actual net name

        Net *currentNet = netMap[netName];

        while (iss >> cellName && cellName != ";") {
          int cellIdx = cellMap[cellName];
          _cells[cellIdx].nets.push_back(currentNet);
          currentNet->cells.push_back(&_cells[cellIdx]);
        }
      } else {
        std::istringstream iss(line);
        std::string cellName;
        Net *currentNet = netMap[netName];
        while (iss >> cellName && cellName != ";") {
          int cellIdx = cellMap[cellName];
          _cells[cellIdx].nets.push_back(currentNet);
          currentNet->cells.push_back(&_cells[cellIdx]);
        }
      }
    }

    file.close();

    std::cout << "net size: " << _nets.size() << std::endl;
    std::cout << "cell size: " << _cells.size() << std::endl;
    std::cout << "balance factor: " << balanceFactor << std::endl;
  }

  int calculateCutCost() {
    int cutCost = 0;
    for (int a = 0; a < _nets.size(); a++) {
      bool inP1 = false;
      bool inP2 = false;
      for (int i = 0; i < _nets[a]->cells.size(); i++) {
        if (_nets[a]->cells[i]->partition) {
          inP1 = true;
        } else {
          inP2 = true;
        }
        if (inP1 && inP2) {
          cutCost++;
          break; // Break the loop as the net is already cut
        }
      }
    }
    return cutCost;
  }

  void writeOutput(const std::string &filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
      std::cerr << "Failed to open output file: " << filename << std::endl;
      return;
    }

    // Write cut size
    outfile << "Cutsize = " << cur_cost << std::endl;

    // Iterate through each net and write the cells
    outfile << "G1 " << part_0_nodes << std::endl;
    for (int i = 0; i < _cells.size(); i++) {
      if (_cells[i].partition == true) {
        outfile << _cells[i].name << " ";
      }
    }
    outfile << ";" << std::endl;
    outfile << "G2 " << part_1_nodes << std::endl;
    for (int i = 0; i < _cells.size(); i++) {
      if (_cells[i].partition == false) {
        outfile << _cells[i].name << " ";
      }
    }
    outfile << ";" << std::endl;

    outfile.close();
  }

  void Initialize() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution dist(0.5); // Distribution for 50-50 chance

    int halfSize = _cells.size() / 2;
    int countForPart0 = 0;

    for (int i = 0; i < _cells.size(); i++) {
      if (dist(gen) && countForPart0 < halfSize) {
        _cells[i].partition = true; // Assign to part_0
        countForPart0++;
      } else {
        _cells[i].partition = false; // Assign to part_1
      }
    }

    // If not enough cells were assigned to part_0 due to random chance, fill
    // the rest
    for (int i = 0; countForPart0 < halfSize && i < _cells.size(); i++) {
      if (!_cells[i].partition) {
        _cells[i].partition = true;
        countForPart0++;
      }
    }

    part_0_nodes = countForPart0;
    part_1_nodes = _cells.size() - countForPart0;

    for (int i = 0; i < _cells.size(); i++) {
      if (_cells[i].nets.size() > max_gain) {
        max_gain = _cells[i].nets.size();
      }
    }

    int bucketRange = max_gain * 2 + 1; // Total range of gains
    _bktlist.resize(bucketRange);

    // Initialize gain
    for (int i = 0; i < _cells.size(); i++) {
      _cells[i].gain = 0;
      bool my_partition = _cells[i].partition;

      int FS = 0;
      int TE = 0;

      // iterate through the nets
      for (int j = 0; j < _cells[i].nets.size(); j++) {
        Net *net = _cells[i].nets[j];

        int same_partition = 0;

        for (int k = 0; k < net->cells.size(); k++) {
          if (net->cells[k]->partition == my_partition) {
            same_partition++;
          }
        }

        if (same_partition == net->cells.size()) {
          TE++;
        } else if (same_partition == 1) {
          FS++;
        }
      }

      _cells[i].gain = FS - TE;

      // Calculate bucket index and add cell to the corresponding bucket
      int bucketIndex = _cells[i].gain +
                        max_gain; // Offset by maxGain to handle negative gains

      _bktlist[bucketIndex].push_back(&_cells[i]);
      _cells[i].satellite = std::prev(_bktlist[bucketIndex].end());
    }

    cur_cost = calculateCutCost();
    std::cout << "Initial cut cost: " << cur_cost << std::endl;
  }

  void recalculateGain(Cell *movedCell) {
    bool my_partition = movedCell->partition;
    int oldGain = movedCell->gain;

    int FS = 0;
    int TE = 0;

    for (int i = 0; i < movedCell->nets.size(); i++) {
      Net *net = movedCell->nets[i];

      int same_partition = 0;

      for (int j = 0; j < net->cells.size(); j++) {
        if (net->cells[j]->partition == my_partition) {
          same_partition++;
        }
      }

      if (same_partition == net->cells.size()) {
        TE++;
      } else if (same_partition == 1) {
        FS++;
      }
    }

    movedCell->gain = FS - TE;

    // Remove the cell from its current bucket
    _bktlist[oldGain + max_gain].erase(movedCell->satellite);

    // Calculate bucket index and add cell to the corresponding bucket
    int bucketIndex = movedCell->gain +
                      max_gain; // Offset by maxGain to handle negative gains

    _bktlist[bucketIndex].push_back(movedCell);
    movedCell->satellite = std::prev(_bktlist[bucketIndex].end());
  }

  // Function to select and move the cell with the highest gain
  int moveHighestGainCell(unordered_map<string, int> &lockMap) {
    for (int gainIndex = _bktlist.size() - 1; gainIndex >= 0; gainIndex--) {
      if (gainIndex < max_gain) {
        break; // No cell with positive gain
      }
      auto &bucket = _bktlist[gainIndex];

      for (auto it = bucket.rbegin(); it != bucket.rend(); ++it) {
        Cell *cell = *it;

        if (lockMap[cell->name] > 0) {
          continue; // Cell is locked, check the next cell in the same bucket
        }
        lockMap[cell->name]++;

        int post_part_0_nodes = part_0_nodes;
        int post_part_1_nodes = part_1_nodes;

        if (cell->partition == true) {
          post_part_0_nodes--;
          post_part_1_nodes++;
        } else {
          post_part_0_nodes++;
          post_part_1_nodes--;
        }

        bool balance_check =
            _cells.size() * (1.0 - balanceFactor) / 2.0 < post_part_0_nodes &&
            post_part_0_nodes < _cells.size() * (1.0 + balanceFactor) / 2.0 &&
            _cells.size() * (1.0 - balanceFactor) / 2.0 < post_part_1_nodes &&
            post_part_1_nodes < _cells.size() * (1.0 + balanceFactor) / 2.0;

        if (!balance_check) {
          continue; // Skip this cell but keep it locked
        }

        // Move the cell to the opposite partition
        cell->partition = !cell->partition;
        if (cell->partition == false) {
          part_0_nodes--;
          part_1_nodes++;
        } else {
          part_0_nodes++;
          part_1_nodes--;
        }

        // recalculateGain(cell);
        int oldGain = cell->gain;
        _bktlist[oldGain + max_gain].erase(cell->satellite);

        updateNeighborGains(cell, lockMap);

        return 1; // Successful move
      }
    }

    return 0; // No cell was moved, possibly all are locked or balance factor
              // constraint
  }

  // Function to update the gains of neighbor cells
  void updateNeighborGains(Cell *movedCell,
                           unordered_map<string, int> &lockMap) {
    vector<Cell *> neighborCells;
    unordered_map<string, int> visitedMap;
    visitedMap[movedCell->name]++;
    for (Net *net : movedCell->nets) {
      for (Cell *neighborCell : net->cells) {
        if (neighborCell != movedCell) {
          if (visitedMap[neighborCell->name] == 0 &&
              lockMap[neighborCell->name] == 0) {
            neighborCells.push_back(neighborCell);
            visitedMap[neighborCell->name]++;
          }
        }
      }
    }

    for (Cell *neighborCell : neighborCells) {
      recalculateGain(neighborCell);
    }
  }

  void onePass(int history_size, int debug_step) {
    unordered_map<string, int> lockMap;
    std::deque<int> costHistory;
    int flag = 1;
    bool terminate = false;
    long long step = 0;

    while (flag && !terminate) {
      flag = moveHighestGainCell(lockMap);

      if (step % debug_step == 0) {
        cur_cost = calculateCutCost();
        std::cout << "Current cut cost: " << cur_cost << std::endl;

        // Add the current cost to the history
        costHistory.push_back(cur_cost);
        if (costHistory.size() > history_size) {
          costHistory.pop_front(); // Keep the history size to history_size
        }

        // Check if cost is increasing or plateauing
        if (costHistory.size() == history_size &&
            std::none_of(
                costHistory.begin(), costHistory.end(),
                [this](int past_cost) { return past_cost < cur_cost; })) {
          terminate = true; // Terminate if cost hasn't decreased in the last
                            // history_size iterations
        }

        std::cout << "part_0_nodes: " << part_0_nodes << std::endl;
        std::cout << "part_1_nodes: " << part_1_nodes << std::endl;
        std::cout << "ratio: "
                  << static_cast<float>(part_0_nodes) /
                         (part_1_nodes + part_0_nodes)
                  << std::endl;
        std::cout << "==================" << std::endl;
      }
      step++;
    }

    cur_cost = calculateCutCost();
  }

private:
  std::vector<Net *> _nets;
  std::vector<Cell> _cells;
  double balanceFactor;

  int max_gain = 0;
  int cur_cost;

  int part_0_nodes = 0; // count of nodes in partition false
  int part_1_nodes = 0; // count of nodes in partition true

  unordered_map<std::string, int> cellMap;

  // bucket list
  std::vector<std::list<Cell *>> _bktlist;
}; // end of definition pa1

// ================================
// Def from the application perspective
// ================================

int main(int argc, char *argv[]) {
  if (argc != 4) {
    std::cerr << "Usage: " << argv[0]
              << " [input file name] [history size] [debug_output_step]\n";
    return 1;
  }

  int min_cost = INT_MAX;
  int min_idx = -1;

  vector<FMPartitioner> partitioners(1, FMPartitioner());

  for (int i = 0; i < 1; i++) {
    partitioners[i].readInput(argv[1]);
    partitioners[i].Initialize();
    partitioners[i].onePass(atoi(argv[2]), atoi(argv[3]));
    int cost = partitioners[i].calculateCutCost();
    if (cost < min_cost) {
      min_cost = cost;
      min_idx = i;
    }
  }

  // display costs for all 10 partitioners
  for (int i = 0; i < 1; i++) {
    std::cout << "Partitioner " << i
              << " cost: " << partitioners[i].calculateCutCost() << std::endl;
  }

  partitioners[min_idx].writeOutput("output.dat");
}
