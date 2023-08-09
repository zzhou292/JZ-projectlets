// Author: Jason Zhou
// three-dimensional dp
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int helper(vector<int>& prices, vector<vector<vector<int>>>& memo, int idx, int state, int cap){
        // termination
        if(idx >= prices.size() || cap <= 0) return 0;
        if(memo[idx][state][cap]!=INT_MIN) return memo[idx][state][cap]; 
        int res;

        // buy
        if(state == 0){
            res = max(helper(prices, memo, idx+1, 0, cap), -prices[idx]+helper(prices, memo, idx+1, 1, cap));
        }
        // sell
        if(state == 1){
            res = max(helper(prices, memo, idx+1, 1, cap), prices[idx]+helper(prices,memo,idx+1, 0, cap-1));
        }
        
        memo[idx][state][cap] = res;

        return memo[idx][state][cap];
    }

    int maxProfit(int k, vector<int>& prices) {
        // edge 
        if(k==0 || prices.size()==0) return 0;
        vector<vector<vector<int>>> memo(prices.size(), vector<vector<int>>(2, vector<int>(k+1, INT_MIN)));

        return helper(prices, memo, 0, 0, k);
    }
};

int main(){
    Solution a;
    vector<int> input = {3,3,5,0,0,3,1,4};
    cout << a.maxProfit(2, input) << endl;

    return 0;
}