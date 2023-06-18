
// Author: Jason Zhou
// Acceptable solution, but it is really damn slow~~
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int canCompleteCircuit(vector<int> &gas, vector<int> &cost) {
    vector<int> gain;
    int tot;
    for (int i = 0; i < gas.size(); i++) {
      gain.push_back(gas[i] - cost[i]);
      tot += gain[i];
    }
    if (tot < 0)
      return -1;

    int start_idx = 0;
    int cur_gas = 0;

    while (start_idx < gain.size()) {
      for (int i = 0; i < gain.size(); i++) {
        cur_gas += gain[(start_idx + i) % gain.size()];
        if (cur_gas < 0) {
          cur_gas = 0;
          start_idx = start_idx + i + 1;
          break;
        }

        if (i == gain.size() - 1) {
          return start_idx;
        }
      }
    }
    return -1;
  }
};

int main() {
  vector<int> gas = {1, 2, 3, 4, 5};
  vector<int> cost = {3, 4, 5, 1, 2};

  Solution a;
  cout << a.canCompleteCircuit(gas, cost) << endl;

  return 0;
}