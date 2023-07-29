// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int search(vector<int> &nums, int target) {
    // first one we search for the pivot pt
    int p_l = 0;
    int p_r = nums.size() - 1;
    int p_mid = 0;

    while (p_l <= p_r) {
      p_mid = (p_l + p_r) / 2;

      if (nums[p_mid] > nums[p_r]) {
        // pivot is on the right part
        if (p_mid + 1 < nums.size() - 1 && nums[p_mid + 1] < nums[p_mid]) {
          p_mid = p_mid + 1;
          break;
        }
        p_l = p_mid + 1;
      } else {
        // pivot is on the left part
        if (p_mid - 1 >= 0 && nums[p_mid] < nums[p_mid - 1]) {
          break;
        }
        p_r = p_mid - 1;
      }
    }

    int pivot = p_mid;
    vector<int> temp;
    temp.assign(nums.begin() + pivot, nums.end());
    nums.erase(nums.begin() + pivot, nums.end());
    nums.insert(nums.begin(), temp.begin(), temp.end());

    // second we do binary search on restored array
    int l = 0;
    int r = nums.size() - 1;
    int mid;

    while (l <= r) {
      mid = (l + r) / 2;
      if (nums[mid] == target) {
        if (mid <= (nums.size() - pivot - 1)) {
          return pivot + mid;
        } else {
          return mid - (nums.size() - pivot);
        }
      } else {
        if (nums[mid] > target) {
          r = mid - 1;
        } else {
          l = mid + 1;
        }
      }
    }

    return -1;
  }
};

int main() {
  vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
  int target = 0;

  Solution a;
  cout << a.search(nums, target) << endl;

  return 0;
}