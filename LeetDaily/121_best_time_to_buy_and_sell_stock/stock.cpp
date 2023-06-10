// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // edge check
        if (prices.size() < 2){
            return 0;
        }

        int max_profit = 0; // buy pointer
        
        int l = 0; 
        int r = 1;

        while (r < prices.size()){
            int cur_profit = prices[r] - prices[l];

            if(cur_profit >= 0){
                if (cur_profit > max_profit){
                    max_profit = cur_profit;
                }
                r++;
            }else{
                l=r;
                r=l+1;
            }
        }

        return max_profit;
    }
};

int main(){
    vector<int> prices = {7,1,5,3,6,4};
    Solution a;
    cout << a.maxProfit(prices) << endl;
}