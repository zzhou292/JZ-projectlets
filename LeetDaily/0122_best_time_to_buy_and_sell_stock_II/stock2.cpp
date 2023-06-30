// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // edge case
        if(prices.size()<2) return 0;

        int profit = 0;
        for (int i = 1; i < prices.size();i++){
            profit+=max(0, prices[i] - prices[i-1]);
        }

        return profit;
    }
};

int main(){
    Solution a;
    vector<int> input = {7,1,5,3,6,4};
    cout << a.maxProfit(input) << endl;

    return 0;
}