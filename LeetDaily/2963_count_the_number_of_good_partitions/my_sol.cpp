// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int numberOfGoodPartitions(vector<int> &nums) {
    // bd check
    if (nums.size() == 0)
      return 0;

    map<int, int> my_map;
    for (int i = 0; i < nums.size(); i++) {
      my_map[nums[i]] = i;
    }

    int res = 1;
    int mod = 1e9 + 7;
    int j = 0;
    for (int i = 0; i < nums.size(); i++) {
      if (i > j) {
        res = (res * 2) % mod;
      }

      if (my_map[nums[i]] > j)
        j = my_map[nums[i]];
    }

    return res;
  }
};

int main() {
  vector<int> input{2, 2, 1, 1, 1, 1, 1};
  Solution a;
  cout << a.numberOfGoodPartitions(input) << endl;

  return 0;
}
