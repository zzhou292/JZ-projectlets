// Author: Jason Zhou
// Attempted solution, really damn slow~~ and I don't think it is correct
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    unordered_set<string> st(wordList.begin(), wordList.end());
    queue<pair<string, int>> q;
    q.push(pair<string, int>{beginWord, 1});
    st.erase(beginWord);

    while (!q.empty()) {
      string cur_word = q.front().first;
      int cur_step = q.front().second;

      // termination
      if (cur_word == endWord) {
        return cur_step;
      }

      q.pop();

      for (int i = 0; i < cur_word.size(); i++) {
        string check_word = cur_word;
        for (char j = 'a'; j <= 'z'; j++) {
          check_word[i] = j;
          if (st.find(check_word) != st.end()) {
            q.push(pair<string, int>{check_word, cur_step + 1});
            st.erase(check_word);
          }
        }
      }
    }

    return 0;
  }
};

int main() {
  vector<string> input = {
      "si", "go", "se", "cm", "so", "ph", "mt", "db", "mb", "sb", "kr", "ln",
      "tm", "le", "av", "sm", "ar", "ci", "ca", "br", "ti", "ba", "to", "ra",
      "fa", "yo", "ow", "sn", "ya", "cr", "po", "fe", "ho", "ma", "re", "or",
      "rn", "au", "ur", "rh", "sr", "tc", "lt", "lo", "as", "fr", "nb", "yb",
      "if", "pb", "ge", "th", "pm", "rb", "sh", "co", "ga", "li", "ha", "hz",
      "no", "bi", "di", "hi", "qa", "pi", "os", "uh", "wm", "an", "me", "mo",
      "na", "la", "st", "er", "sc", "ne", "mn", "mi", "am", "ex", "pt", "io",
      "be", "fm", "ta", "tb", "ni", "mr", "pa", "he", "lr", "sq", "ye"};
  string begin = "qa";
  string end = "sq";

  Solution a;
  cout << a.ladderLength(begin, end, input) << endl;
}