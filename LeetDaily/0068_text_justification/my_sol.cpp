// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
  string contruct_helper(vector<string> &st, int &maxWidth, bool endline) {
    string temp_res;
    if (st.size() != 0) {
      int act_size = 0;
      for (int j = 0; j < st.size(); j++) {
        act_size += st[j].size();
      }
      int remain_empt = maxWidth - act_size;
      int gap = 0;
      if (st.size() == 1) {
        gap = remain_empt;
      } else {
        gap = (remain_empt) / (st.size() - 1);
      }

      for (int j = 0; j < st.size(); j++) {
        temp_res += st[j];
        int space_num = 0;
        if (endline == true) {
          if (j != st.size() - 1) {
            space_num = 1;
          } else {
            space_num = remain_empt;
          }
        } else {
          if (st.size() == 1) {
            space_num = gap;
          } else if (j == st.size() - 1) {
            space_num = 0;
          } else if (gap * (st.size() - j - 1) < remain_empt) {
            space_num = gap + 1;
          } else {
            space_num = gap;
          }
        }
        remain_empt -= space_num;

        while (space_num != 0) {
          temp_res += " ";
          space_num--;
        }
      }
    }
    return temp_res;
  }

  vector<string> fullJustify(vector<string> &words, int maxWidth) {
    vector<string> res;
    int cur_size = 0;
    vector<string> st;
    for (int i = 0; i < words.size(); i++) {
      int gap_test = st.size();
      if (gap_test < 0)
        gap_test = 0;

      if (cur_size + words[i].size() + gap_test <= maxWidth) {
        st.push_back(words[i]);
        cur_size += words[i].size();
      } else {
        string temp_res = contruct_helper(st, maxWidth, false);
        cur_size = 0;
        st.clear();
        res.push_back(temp_res);
        i--;
      }
    }

    if (st.size() != 0) {
      string temp_res = contruct_helper(st, maxWidth, true);
      res.push_back(temp_res);
    }

    return res;
  }
};

int main() {
  Solution mysol;
  vector<string> words = {
      "Science", "is", "what",       "we",   "understand", "well",
      "enough",  "to", "explain",    "to",   "a",          "computer.",
      "Art",     "is", "everything", "else", "we",         "do"};

  vector<string> res = mysol.fullJustify(words, 20);

  for (int i = 0; i < res.size(); i++) {
    cout << res[i] << endl;
  }
  return 0;
}