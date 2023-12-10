class Solution {
public:
  long long f(const vector<int> &arr, int target, int k) {
    long long res = 0;
    long long cnt = 0;
    long long l = 0;
    for (long long i = 0; i < arr.size(); i++) {
      if (arr[i] == target)
        cnt++;

      while (cnt >= k) {
        res = res + (arr.size() - i);
        if (arr[l] == target)
          cnt--;
        l++;
      }
    }

    return res;
  }

  long long countSubarrays(vector<int> &nums, int k) {
    int maxi = *max_element(nums.begin(), nums.end());
    return f(nums, maxi, k);
  }
};