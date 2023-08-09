// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    int helper(int idx, vector<int>& nums, vector<int>& memo){
        if(idx>=nums.size()) return 0;
        if(memo[idx]!=INT_MIN) return memo[idx];

        int num1 = helper(idx+1, nums, memo);
        int num2 = helper(idx+2, nums, memo) + nums[idx];
        memo[idx] = max(num1, num2);
        return memo[idx];
    }

    int rob(vector<int>& nums) {
        // edge
        if(nums.size() == 0) return 0;
        vector<int> memo(nums.size(), INT_MIN);
        memo[nums.size()-1] = nums[nums.size()-1];
        
        return helper(0, nums, memo);
    }
};

int main(){
    vector<int> input = {2,7,9,3,1};

    Solution a;
    cout << a.rob(input) << endl;
    
    return 0;
}