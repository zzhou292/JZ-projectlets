// Author: Jason Zhou
// this is my solution, it is acceptable, but slow
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int removeDuplicates(vector<int> &nums) {
    // edge case
    if (nums.size() == 0)
      return 0;

    int prev = nums[0];
    for (int i = 1; i < nums.size(); i++) {
      if (prev == nums[i]) {
        nums.erase(nums.begin() + i);
        i--;
      } else {
        prev = nums[i];
      }
    }

    return nums.size();
  }
};

int main() {
  vector<int> nums = {1, 1, 2, 2, 3, 3, 3, 4, 5, 6};

  Solution a;
  cout << a.removeDuplicates(nums) << endl;

  return 0;
}