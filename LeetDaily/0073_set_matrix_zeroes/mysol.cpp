// Author: Jason Zhou
// this solution is not the best, but acceptable
#include "../general_include.h"

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        set<int> cul_idx_zero;
        set<int> row_idx_zero;
        
        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[i].size();j++){
                if(matrix[i][j]==0){
                    row_idx_zero.insert(i);
                    cul_idx_zero.insert(j);
                }
            }
        }

        for(const int& row_num:row_idx_zero){
            for(int j = 0; j < matrix[0].size();j++){
                matrix[row_num][j] = 0;
            }
        }

        for(const int& cul_num: cul_idx_zero){
            for(int i = 0; i < matrix.size();i++){
                matrix[i][cul_num] = 0;
            }
        }
    }
};

int main(){
    vector<int> input1 = {0,1,2,0};
    vector<int> input2 = {3,4,5,2};
    vector<int> input3 = {1,3,1,5};
    vector<vector<int>> input = {input1, input2, input3};

    Solution a;
    a.setZeroes(input);

    for(int i = 0; i < input.size(); i++){
        for(int j = 0; j < input[i].size();j++){
            cout << input[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}