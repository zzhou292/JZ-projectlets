
// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int largestPerimeter(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        for(int i = nums.size()-3; i >= 0; i--)
        {
            if(nums[i]+nums[i+1]>nums[i+2]){
                return nums[i]+nums[i+1]+nums[i+2];
            }
        }
        return 0;
    }
};

int main(){
    vector<int> input = {2,1,2};

    Solution a;
    cout << a.largestPerimeter(input) << endl;

    return 0;
}