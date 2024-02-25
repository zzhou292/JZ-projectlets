class Solution {
public:
  vector<int> fathers;

  int find_my_father(int x) {
    if (fathers[x] != x)
      fathers[x] = find_my_father(fathers[x]);
    return fathers[x];
  }

  void lets_union(int x, int y) {
    x = find_my_father(x);
    y = find_my_father(y);
    if (x < y)
      fathers[y] = fathers[x];
    else
      fathers[x] = fathers[y];
  }

  vector<int> find_all_primes(int n) {
    vector<int> q(n + 1, 0);
    vector<int> primes;
    for (int i = 2; i <= sqrt(n); i++) {
      if (q[i] == 1)
        continue;
      int j = i * 2;
      while (j <= n) {
        q[j] = 1;
        j += i;
      }
    }
    for (int i = 2; i <= n; i++) {
      if (q[i] == 0)
        primes.push_back(i);
    }
    return primes;
  }

  bool canTraverseAllPairs(vector<int> &nums) {
    int n = nums.size();
    vector<int> primes =
        find_all_primes(*max_element(nums.begin(), nums.end()));
    int n_primes = primes.size();
    unordered_map<int, int> num_to_idx; // get idx from value;

    for (int i = 0; i < primes.size(); i++) {
      num_to_idx[primes[i]] = i;
    }

    fathers.resize(n + n_primes);
    for (int i = 0; i < n + n_primes; i++) {
      fathers[i] = i;
    }

    for (int i = 0; i < n; i++) {
      int val = nums[i];
      for (int j = 0; j < n_primes; j++) {
        long long p = primes[j];
        if (p > val)
          break;
        if (p * p > val) {
          // val is a prime
          if (find_my_father(i) != find_my_father(num_to_idx[val] + n))
            lets_union(i, num_to_idx[val] + n);
          break;
          `
        }
        if (val % primes[j] == 0) {
          if (find_my_father(i) != find_my_father(n + j)) {
            lets_union(i, n + j);
          }
        }
        while (val % primes[j] == 0) {
          val /= primes[j];
        }
      }
    }
    for (int i = 0; i < n; i++) {
      if (find_my_father(i) != 0)
        return false;
    }
    return true;
  }
};