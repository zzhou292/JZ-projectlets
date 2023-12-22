// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int countCompleteSubstrings(string word, int k) {
    int n = word.size();
    int res = 0;

    for (int i = 0; i < n;) {
      int j = i + 1;
      while (j < n && abs(word[j] - word[j - 1]) <= 2) {
        j++;
      }
      res += helper(word.substr(i, j - i), k);
      i = j;
    }
    return res;
  }

  int helper(string s, int k) {
    int count = 0;
    set<char> my_set(s.begin(), s.end());
    for (int T = 1; T <= my_set.size(); T++) {
      int len = T * k;
      vector<int> freq(26, 0);

      int j = 0;
      for (int i = 0; i + len - 1 < s.size(); i++) {
        while (j <= i + len - 1) {
          freq[s[j] - 'a']++;
          j++;
        }

        if (check(freq, k))
          count++;
        freq[s[i] - 'a']--;
      }
    }

    return count;
  }

  bool check(vector<int> &freq, int k) {
    for (int f : freq) {
      if (f != k && f != 0) {
        return false;
      }
    }
    return true;
  }
};

int main() {
  Solution sol;
  cout << sol.countCompleteSubstrings("igigee", 2) << endl;
  cout << sol.countCompleteSubstrings("aaabbbccc", 3) << endl;
  return 0;
}
