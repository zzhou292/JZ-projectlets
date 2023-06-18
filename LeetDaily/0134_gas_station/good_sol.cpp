
// Author: Jason Zhou
// This solution is both acceptable and good
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    vector<int> gain;
    for (int i = 0; i < gas.size(); i++) {
      gain.push_back(gas[i] - cost[i]);
    }

    int start_idx = 0;
    int cur_gas = 0;
    int gain_tot = 0;

    for (int i = 0; i < gas.size(); i++) {
      gain_tot += gain[i];
      cur_gas += gain[i];
      if (cur_gas < 0) {
        cur_gas = 0;
        start_idx = i + 1;
      }
    }

    if (gain_tot < 0) {
      return -1;
    } else {
      return start_idx;
    }
  }
};

int main() {
  vector<int> gas = {1, 2, 3, 4, 5};
  vector<int> cost = {3, 4, 5, 1, 2};

  Solution a;
  cout << a.canCompleteCircuit(gas, cost) << endl;

  return 0;
}