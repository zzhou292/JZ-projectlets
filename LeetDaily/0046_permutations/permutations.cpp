// Author: Jason Zhou
#include "../general_include.h"
using namespace std;

class Solution {
public:
  vector<vector<int>> permute(vector<int> &nums) {
    vector<vector<int>> res;
    vector<int> cur;
    backtracking(res, cur, nums);
    return res;
  }

  void backtracking(vector<vector<int>> &res, vector<int> &cur,
                    vector<int> &nums) {
    // if cur vector has the same size as number, we finished constructing an
    // array attach to the result pool
    if (cur.size() == nums.size()) {
      res.push_back(cur);
    } else {
      // search for all other possible numbers
      for (int i = 0; i < nums.size(); i++) {
        // if current num doesn't exist in the cur vector
        if (find(cur.begin(), cur.end(), nums[i]) == cur.end()) {
          cur.push_back(nums[i]); // add number
          backtracking(res, cur, nums);
          cur.pop_back(); // remove the last one
        }
      }
    }
  }
};

int main() {
  vector<int> nums = {1, 2, 3};
  Solution a;
  vector<vector<int>> res = a.permute(nums);

  for (int i = 0; i < res.size(); i++) {
    cout << "[";
    for (int j = 0; j < res[i].size(); j++) {
      cout << res[i][j] << " ";
    }
    cout << "]";
  }
}