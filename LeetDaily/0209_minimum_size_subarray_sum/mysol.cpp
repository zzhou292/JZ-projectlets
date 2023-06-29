// Author: Jason Zhou
// my own sliding windows solution, O(n) space, good but not the best.
// the best solution isn't really easy to come with, I skipped
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        // edge case
        if(nums.size()==0) return 0;

        int l = 0; int r = 0;
        int min_len = INT_MAX;
        int sum = nums[0];

        while(r < nums.size()){
            if(sum<target || l>r){
                r++;
                if(r<nums.size()) sum += nums[r];
            }else{
                min_len = min(min_len, r-l+1);
                sum -= nums[l];
                l++;
            }
        }

        return (min_len != INT_MAX) ? min_len : 0;
        return 0;
    }
};

int main(){
    vector<int> input = {2,3,1,2,4,3};
    int target = 7;

    Solution a;
    cout << a.minSubArrayLen(target, input) << endl;

    return 0;
}