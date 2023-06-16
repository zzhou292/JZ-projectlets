// Author: Jason Zhou
#include "../general_include.h"
using namespace std;

class Solution {
public:
  void rotate(vector<vector<int>> &matrix) {
    // transpose
    for (int i = 0; i < matrix.size(); i++) {
      for (int j = 0; j < i; j++) {
        swap(matrix[i][j], matrix[j][i]);
      }
    }

    // swap column
    for (int i = 0; i < matrix.size() / 2; i++) {
      for (int j = 0; j < matrix.size(); j++) {
        swap(matrix[j][i], matrix[j][matrix.size() - 1 - i]);
      }
    }
  }
};

int main() {
  vector<int> row_1 = {5, 1, 9, 11};
  vector<int> row_2 = {2, 4, 8, 10};
  vector<int> row_3 = {13, 3, 6, 7};
  vector<int> row_4 = {15, 14, 12, 16};

  vector<vector<int>> input = {row_1, row_2, row_3, row_4};

  Solution a;
  a.rotate(input);

  for (int i = 0; i < input.size(); i++) {
    for (int j = 0; j < input[i].size(); j++) {
      cout << input[i][j] << ", ";
    }
    cout << endl;
  }

  return 0;
}