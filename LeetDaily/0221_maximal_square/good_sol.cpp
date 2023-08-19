// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

// this is the accepted solution

class Solution {
public:
    int maximalSquare(vector<vector<char>>& matrix) {
        vector<vector<int>> dp(matrix.size(), vector<int>(matrix[0].size(), 0));
        int max_square = 0;

        for(int i = 0; i < matrix.size(); i++){
            for(int j = 0; j < matrix[0].size();j++){
                if(i == 0 || j == 0){
                    if(matrix[i][j]=='1') dp[i][j]=1;
                }else{
                    if(matrix[i][j]=='1'){
                        dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1]))+1;
                    }
                }
                max_square = max(max_square, dp[i][j]*dp[i][j]);
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