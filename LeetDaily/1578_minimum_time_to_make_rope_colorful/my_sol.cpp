// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int minCost(string colors, vector<int> &neededTime) {
    if (colors.size() == 1 || colors.size() == 0)
      return 0;
    vector<int> scan_head;
    char prev = colors[0];
    scan_head.push_back(0);
    for (int i = 0; i < colors.size(); i++) {
      if (colors[i] != prev)
        scan_head.push_back(i);
      prev = colors[i];
    }

    int res = 0;

    for (int i = 0; i < scan_head.size() - 1; i++) {
      int start = scan_head[i];
      int end = scan_head[i + 1];
      int len = end - start;
      if (len == 1)
        continue;
      int tot_cost = 0;
      int max_idx = start;
      int max_val = neededTime[start];
      for (int j = start; j < end; j++) {
        tot_cost += neededTime[j];
        if (neededTime[j] > max_val) {
          max_val = neededTime[j];
          max_idx = j;
        }
      }

      res += tot_cost - max_val;
    }

    // edge, count the last
    if (scan_head[scan_head.size() - 1] != colors.size() - 1) {
      int start = scan_head[scan_head.size() - 1];
      int end = colors.size();
      int tot_cost = 0;
      int max_idx = start;
      int max_val = neededTime[start];
      for (int j = start; j < end; j++) {
        tot_cost += neededTime[j];
        if (neededTime[j] > max_val) {
          max_val = neededTime[j];
          max_idx = j;
        }
      }
      cout << tot_cost - max_val << endl;
      res += tot_cost - max_val;
    }

    return res;
  }
};

int main() {
  Solution sol;
  string colors = "abaac";
  vector<int> neededTime = {1, 2, 3, 4, 5};
  cout << sol.minCost(colors, neededTime) << endl;
  return 0;
}