// Author: Jason Zhou
// Attempted solution, really damn slow~~ and I don't think it is correct
#include "../general_include.h"

using namespace std;

class Solution {
public:
  int diffHelper(string &a, string &b) {
    int diff = 0;
    for (int i = 0; i < a.size(); i++) {
      if (a[i] != b[i]) {
        diff++;
      }
    }
    return diff;
  }

  int recurHelper(vector<string> &wordList, string &endWord, string &curWord,
                  int step, vector<bool> &recorder, int prev_min_step) {
    // termination
    if (curWord == endWord) {
      return step;
    }

    if (step >= prev_min_step) {
      return INT_MAX;
    }

    int min_step = INT_MAX;
    for (int i = 0; i < wordList.size(); i++) {
      if (recorder[i] == false) {
        int cur_diff = diffHelper(wordList[i], curWord);
        if (cur_diff == 1) {
          recorder[i] = true;
          min_step = min(min_step, recurHelper(wordList, endWord, wordList[i],
                                               step + 1, recorder, min_step));
          recorder[i] = false;
        }
      }
    }

    return min_step;
  }

  int ladderLength(string beginWord, string endWord, vector<string> &wordList) {
    // edge case
    if (wordList.size() == 0) {
      return 0;
    }

    vector<bool> recorder;
    for (int i = 0; i < wordList.size(); i++) {
      recorder.push_back(false);
    }

    // recur
    int res = recurHelper(wordList, endWord, beginWord, 1, recorder, INT_MAX);
    if (res == INT_MAX) {
      return 0;
    } else {
      return res;
    }
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
  string begin = string("qa");
  string end = string("sq");

  Solution a;
  cout << a.ladderLength(begin, end, input) << endl;
}