class Solution {
public:
  long long count(vector<int> &arr_l, vector<int> &arr_r) {
    int n1 = arr_l.size();
    int n2 = arr_r.size();

    long long result = 0;
    int i = 0, j = 0;

    while (i < n1 && j < n2) {
      if (arr_l[i] < arr_r[j]) {
        result += (n2 - j);
        i++;
      } else {
        j++;
      }
    }

    return result;
  }

  long long incremovableSubarrayCount(vector<int> &nums) {
    long long n = nums.size();

    if (n == 1)
      return 1;

    int i = 0;
    int j = n - 1;

    vector<int> arr_l;
    vector<int> arr_r;

    while ((i + 1) < n && nums[i] < nums[i + 1]) {
      arr_l.push_back(nums[i]);
      i++;
    }
    arr_l.push_back(nums[i]);

    while ((j - 1) >= 0 && nums[j] > nums[j - 1]) {
      arr_r.push_back(nums[j]);
      j--;
    }
    arr_r.push_back(nums[j]);

    reverse(arr_r.begin(), arr_r.end());

    // if full array is incremental
    if (j < i) {
      return (long long)(n) * (long long)(n + 1) / 2;
    }

    return arr_l.size() + arr_r.size() + count(arr_l, arr_r) + 1;
  }
};