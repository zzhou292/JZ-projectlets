#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>

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
    double balanceFactor;

    // Read the balance factor
    if (getline(file, line)) {
      std::istringstream iss(line);
      iss >> balanceFactor;
    }

    unordered_map<std::string, Net*> netMap;

    // Read each net and cell, store them separately
    while (getline(file, line)) {
      if (line.substr(0, 3) == "NET") {
        std::istringstream iss(line);
        std::string netName, cellName;

        iss >> netName; // Skip the "NET" keyword
        iss >> netName; // Read the actual net name

        Net* newNet = new Net();
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
      }
    }

    file.close();

    // Link cells and nets
    file.open(filename); // Re-open the file to read again
    while (getline(file, line)) {
      if (line.substr(0, 3) == "NET") {
        std::istringstream iss(line);
        std::string netName, cellName;

        iss >> netName; // Skip the "NET" keyword
        iss >> netName; // Read the actual net name

        Net* currentNet = netMap[netName];


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

  void Initialize() {
    // Initilize random cut
    for (int i = 0; i < _cells.size(); i++) {
      if(i < _cells.size() / 2) {
        _cells[i].partition = true;
      } else {
        _cells[i].partition = false;
      }
    }

    for(int i = 0; i < _cells.size(); i++) {
      if(_cells[i].nets.size() > max_gain) {
        max_gain = _cells[i].nets.size();
      }
    }

    std::cout << "max_gain: " << max_gain << std::endl;
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
      int bucketIndex = _cells[i].gain + max_gain; // Offset by maxGain to handle negative gains

      _bktlist[bucketIndex].push_back(&_cells[i]);
      _cells[i].satellite = std::prev(_bktlist[bucketIndex].end());
    }



    cur_cost = calculateCutCost();
    std::cout << "Initial cut cost: " << cur_cost << std::endl;

  }

private:
  std::vector<Net*> _nets;
  std::vector<Cell> _cells;

  int max_gain = 0;
  int cur_cost;

  unordered_map<std::string, int> cellMap;

  // bucket list
  std::vector<std::list<Cell *> > _bktlist;
}; // end of definition pa1

// ================================
// Def from the application perspective
// ================================

int main(int argc, char *argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: " << argv[0] << " [input file name]\n";
    return 1;
  }

  FMPartitioner partitioner;
  partitioner.readInput(argv[1]);
  partitioner.Initialize();

}
