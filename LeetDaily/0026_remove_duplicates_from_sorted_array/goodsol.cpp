// Author: Jason Zhou
// This is a good solution -> only three lines
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int removeDuplicates(vector<int> &nums) {
    int k = 1;
    for (int i = 1; i < nums.size(); i++)
      if (nums[i] != nums[i - 1])
        nums[k++] = nums[i];
    return k;
  }
};

int main() {
  vector<int> nums = {1, 1, 2, 2, 3, 3, 3, 4, 5, 6};

  Solution a;
  cout << a.removeDuplicates(nums) << endl;

  return 0;
}