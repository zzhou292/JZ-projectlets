// Author: Jason Zhou
#include "../general_include.h"
using namespace std;


class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();
        int n = matrix[0].size();
        // do two binary search
        // row level
        int r_l = 0;
        int r_r = m-1;
        int r_mid = (r_l + r_r)/2;

        while(r_l <= r_r){
            r_mid = (r_l+r_r)/2;
            if(target<matrix[r_mid][0]){
                r_r = r_mid-1;
            }else if(target>matrix[r_mid][n-1]){
                r_l = r_mid+1;
            }else{
                break;
            }
        }

        int target_row = r_mid;

        int c_l = 0;
        int c_r = n-1;
        int c_mid = (c_l+c_r)/2;

        while(c_l <= c_r){
            c_mid = (c_l+c_r)/2;
            if(target < matrix[target_row][c_mid]){
                c_r = c_mid-1;
            }else if(target > matrix[target_row][c_mid]){
                c_l = c_mid+1;
            }else if(target == matrix[target_row][c_mid]){
                return true;
            }
        }

        return false;
    }
};

int main(){
    vector<int> row_1 = {1,3,5,7};
    vector<int> row_2 = {10,11,16,20};
    vector<int> row_3 = {23,30,34,60};
    vector<vector<int>> matrix = {row_1, row_2, row_3};

    Solution a;
    cout << a.searchMatrix(matrix, 13) << endl;

    return 0;
}