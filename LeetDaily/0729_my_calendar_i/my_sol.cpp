// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class MyCalendar {
public:
  map<int, int> my_map;

  MyCalendar() {}

  bool book(int start, int end) {
    auto it = my_map.upper_bound(start);
    if (it == my_map.end() || it->second >= end) {
      my_map[end] = start;
      return true;
    } else {
      return false;
    }
  }
};

int main() {
  MyCalendar a;
  cout << a.book(10, 20) << endl;
  cout << a.book(15, 25) << endl;
  cout << a.book(20, 30) << endl;
  return 0;
}

/**
 * Your MyCalendar object will be instantiated and called as such:
 * MyCalendar* obj = new MyCalendar();
 * bool param_1 = obj->book(start,end);
 */