class Solution {
public:
  int findDuplicate(vector<int> &nums) {
    int n = nums.size();

    int l = 1;
    int r = nums.size();

    while (l <= r) {
      int mid = l + (r - l) / 2; // guess
      int ct = 0;
      for (const auto &i : nums) {
        if (i <= mid)
          ct++;
      }

      if (ct > mid) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }

    return l;
  }
};