// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class MyCalendarTwo {
public:
  vector<pair<int, int>> pairs_vec;
  vector<pair<int, int>> overlaps_vec;
  MyCalendarTwo() {}

  bool book(int start, int end) {
    for (const auto &overlap_temp : overlaps_vec) {
      int max_temp = max(overlap_temp.first, start);
      int min_temp = min(overlap_temp.second, end);

      if (min_temp > max_temp)
        return false;
    }

    for (const auto &pair_temp : pairs_vec) {
      int max_temp = max(start, pair_temp.first);
      int min_temp = min(end, pair_temp.second);

      if (min_temp > max_temp) {
        overlaps_vec.emplace_back(max_temp, min_temp);
      }
    }

    pairs_vec.emplace_back(start, end);

    return true;
  }
};

int main() {
  MyCalendarTwo a;
  cout << a.book(10, 20) << endl;
  cout << a.book(50, 60) << endl;
  cout << a.book(10, 40) << endl;
  cout << a.book(5, 15) << endl;
  cout << a.book(5, 10) << endl;
  cout << a.book(25, 55) << endl;
  return 0;
}

/**
 * Your MyCalendarTwo object will be instantiated and called as such:
 * MyCalendarTwo* obj = new MyCalendarTwo();
 * bool param_1 = obj->book(start,end);
 */