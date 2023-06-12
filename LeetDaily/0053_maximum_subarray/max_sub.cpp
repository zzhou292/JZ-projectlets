// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int cur_sum = nums[0];
        int best_sum = nums[0];

        for(int i = 1; i < nums.size(); i++){
            cur_sum = max(cur_sum+nums[i],nums[i]);
            best_sum = max(best_sum, cur_sum);
        }

        return best_sum;
    }
};

int main(){
    vector<int> input = {-2,1,-3,4,-1,2,1,-5,4};

    Solution a;
    auto output = a.maxSubArray(input);
    cout << output << endl;
    return 0;
}