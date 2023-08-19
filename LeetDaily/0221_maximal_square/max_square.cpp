// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

// this is my own solution
// it is correct, but very slow. not an acceptable solution./

class Solution {
public:
    int helper(int& i, int& j, vector<vector<char>>& matrix, vector<vector<int>>& dp){
        if(matrix[i][j] == '0') return 0;

        int res = dp[i][j];
        bool break_flag = false;

        for(int k = dp[i][j]; k < INT_MAX; k++){
            if(i+k >= matrix.size() || j+k >= matrix[i].size()) break;

            for(int a = i; a <= i+k; a++){
                for(int b = j; b <= j+k; b++){
                    if(matrix[a][b]!='1'){
                        break_flag=true;
                        break;
                    }
                }
                if(break_flag==true) break;
            }
            
            if(!break_flag){
                res++;
            }else{
                break;
            }
        } 

        if(break_flag){
            for(int a = i; a < i+res; a++){
                for(int b = j; b < j+res; b++){
                    dp[a][b] = res;
                }
            }
        }
        return res*res;
    }

    int maximalSquare(vector<vector<char>>& matrix) {
        int max_square = 0;
        vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 1));

        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[i].size(); j++){
                max_square = max(max_square, helper(i,j,matrix, dp));
            }
        }

        return max_square;
    }
};

int main(){
    vector<vector<char>> input = {{'1','0','1','0','0'},{'1','0','1','1','1'},{'1','1','1','1','1'},{'1','0','0','1','0'}};

    Solution a;
    cout << a.maximalSquare(input) << endl;

    return 0;
}