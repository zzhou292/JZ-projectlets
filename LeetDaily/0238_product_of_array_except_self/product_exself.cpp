// Author: Jason Zhou
#include "../general_include.h"

using namespace std;


class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        vector<int> prefix(nums.size(),0);
        vector<int> postfix(nums.size(),0);
        vector<int> res;

        // edge case
        if(nums.size()==0) return res;

        prefix[0] = nums[0];
        postfix[nums.size()-1] = nums[nums.size()-1];

        for(int i = 1; i<nums.size(); i++){
            prefix[i] = nums[i]*prefix[i-1];
            postfix[nums.size()-1-i] = nums[nums.size()-1-i]*postfix[nums.size()-1-(i-1)];
        }

        for(int i = 0; i < nums.size(); i++){
            if(i==0){
                res.push_back(postfix[i+1]);
            }else if(i==nums.size()-1){
                res.push_back(prefix[i-1]);
            }else{
                res.push_back(prefix[i-1]*postfix[i+1]);
            }
        }

        return res;
    }
};

int main(){
    Solution a;
    vector<int> nums = {1,2,3,4};
    vector<int> res = a.productExceptSelf(nums);
    for(int i = 0; i < res.size(); i++){
        cout << res[i] << endl;
    }
    return 0;
}