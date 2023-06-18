// Author: Jason Zhou
// this is an ok solution, not the cleanest or best
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // edge case
        sort(nums.begin(), nums.end());
        return nums[nums.size()/2];
    }
};

int main(){
    vector<int> input = {2,2,2,2,2,2,3,3,3};

    Solution a;
    cout << a.majorityElement(input) << endl;
    return 0;
}