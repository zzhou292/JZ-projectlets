class Solution {
public:
  int recur(vector<int> &jobDifficulty, int i, int d, int cur_max,
            vector<vector<unordered_map<int, int>>> &memo) {
    if (i == jobDifficulty.size()) {
      if (d == 0)
        return 0; // end
      else
        return INT_MAX; // invalid
    }

    if (d == 0)
      return INT_MAX; // d is gone, but still have job - invalid

    // Check if the result is already in the cache
    if (memo[i][d].find(cur_max) != memo[i][d].end()) {
      return memo[i][d][cur_max];
    }

    cur_max = max(cur_max, jobDifficulty[i]);
    long long temp1 =
        recur(jobDifficulty, i + 1, d, cur_max, memo); // continue day
    long long temp2 =
        (long long)cur_max +
        (long long)recur(jobDifficulty, i + 1, d - 1, -1, memo); // end day
    int res = min(temp1, temp2);
    memo[i][d][cur_max] = res;

    return (int)res;
  }

  int minDifficulty(vector<int> &jobDifficulty, int d) {
    if (jobDifficulty.size() < d) {
      return -1;
    }

    // Initialize the memoization array
    vector<vector<unordered_map<int, int>>> memo(
        jobDifficulty.size() + 1, vector<unordered_map<int, int>>(d + 1));

    return recur(jobDifficulty, 0, d, -1, memo);
  }
};