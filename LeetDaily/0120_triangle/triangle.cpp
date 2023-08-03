// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int minimumTotal(vector<vector<int>>& triangle) {
        // edge case
        if(triangle.size()==0 || triangle[0].size()==0) return 0;

        vector<vector<int>> dp;
        for(int i = 0; i < triangle.size(); i++){
            vector<int> temp;
            for(int j = 0; j < triangle[i].size(); j++){
                temp.push_back(triangle[i][j]);
            }
            dp.push_back(temp);
        }

        for(int i = triangle.size()-2; i >=0 ;i--){
            for(int j = 0; j < triangle[i].size(); j++){
                dp[i][j] = triangle[i][j] + min(dp[i+1][j], dp[i+1][j+1]);
            }
        }

        // print test
        //for(int i = 0; i < triangle.size(); i++){
        //    for(int j = 0; j < triangle[i].size(); j++){
        //        cout << dp[i][j] <<",";
        //    }
        //    cout << endl;
        //}


        return dp[0][0];
    }
};

int main(){
    Solution a;
    
    vector<vector<int>> triangle = {{2},{3,4},{6,5,7},{4,1,8,3}};

    cout << a.minimumTotal(triangle) << endl;
    
}