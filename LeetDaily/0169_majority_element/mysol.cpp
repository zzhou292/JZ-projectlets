// Author: Jason Zhou
#include "../general_include.h"

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        // edge case
        if(nums.size()==1) return nums[0];

        sort(nums.begin(),nums.end());

        int max = 0;
        int max_val = INT_MIN;
        int temp = 0;

        for(int i = 1; i < nums.size();i++){
            if(nums[i] == nums[i-1]){
                temp++;
            }else{
                temp=0;
            }
            if(max_val < temp){
                max = nums[i];
                max_val = temp;
            }
            
        }


        return max;
    }
};

int main(){
    vector<int> input = {2,2,2,2,2,2,3,3,3};

    Solution a;
    cout << a.majorityElement(input) << endl;
    return 0;
}