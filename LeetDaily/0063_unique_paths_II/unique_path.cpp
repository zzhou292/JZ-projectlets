// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:

    int uniquePathsHelper(vector<vector<int>>& grid, vector<vector<int>>& dp, int pos_x, int pos_y){
        if(pos_x>=0 && pos_y>=0 && grid[pos_x][pos_y]==1) return 0;
        if(pos_x<0 || pos_y<0) return 0;
        if(pos_x==0 && pos_y==0) return 1;
        
        if(dp[pos_x][pos_y]!=-1) return dp[pos_x][pos_y];
        int up = uniquePathsHelper(grid, dp, pos_x-1, pos_y);
        int left = uniquePathsHelper(grid, dp, pos_x, pos_y-1);
        
        return dp[pos_x][pos_y]=left+up;
    }


    int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {

        vector<vector<int>> dp(obstacleGrid.size(), vector<int>(obstacleGrid[0].size(), -1));

        return uniquePathsHelper(obstacleGrid, dp, obstacleGrid.size()-1, obstacleGrid[0].size()-1);;
    }
};

int main(){
    vector<int> row_1 = {0,0,0};
    vector<int> row_2 = {0,1,0};
    vector<int> row_3 = {0,0,0};

    vector<vector<int>> input = {row_1, row_2, row_3};

    Solution a;
    cout<<a.uniquePathsWithObstacles(input)<<endl;

    return 0;
}