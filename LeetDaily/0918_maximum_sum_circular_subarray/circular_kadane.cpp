// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& nums) {
        // edge
        if(nums.size()==1) return nums[0];

        int max_cur = nums[0];
        int max_global = INT_MIN;

        int min_cur = nums[0];
        int min_global = INT_MAX;
        int sum = nums[0];

        for(int i = 1; i < nums.size(); i++){
            max_cur = max(nums[i], max_cur + nums[i]);
            max_global = max(max_global, max_cur);

            min_cur = min(nums[i], min_cur+nums[i]);
            min_global = min(min_global, min_cur);

            sum = sum+=nums[i];
        }

        if(sum == min_global) return max_global;
        return max(max_global, sum-min_global);
    }
};

int main(){
    vector<int> input = {1,-2,3,-2};

    Solution a;
    cout << a.maxSubarraySumCircular(input) << endl;

    return 0;
}