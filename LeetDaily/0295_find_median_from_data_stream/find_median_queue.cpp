// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class MedianFinder {
public:
  priority_queue<int> left;                                       // max heap
  priority_queue<int, std::vector<int>, std::greater<int>> right; // min heap
  double mid = 0.0;
  int tot_size = 0;

  MedianFinder() {}

  void addNum(int num) {
    if (num <= mid) {
      left.push(num);
    } else {
      right.push(num);
    }
    tot_size++;

    if (((int)left.size() - (int)right.size()) > 1) {
      int val = left.top();
      left.pop();
      right.push(val);
    } else if (((int)right.size() - (int)left.size()) > 1) {
      int val = right.top();
      right.pop();
      left.push(val);
    }

    // odd or even, update mid
    if (tot_size == 1) {
      if (left.size() != 0) {
        mid = left.top();
      } else {
        mid = right.top();
      }
    } else if (tot_size % 2 == 0) {
      mid = (left.top() + right.top()) / 2.0;
    } else {
      if (left.size() > right.size()) {
        mid = left.top();
      } else {
        mid = right.top();
      }
    }
  }

  double findMedian() { return mid; }
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */