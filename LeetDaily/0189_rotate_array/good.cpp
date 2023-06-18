// Author: Jason Zhou
// hahahhahaha
#include "../general_include.h"

using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k  = k%nums.size() ;
        reverse(nums.begin()  , nums.begin()+(nums.size()-k)); 
        reverse(nums.begin()+(nums.size()-k) , nums.end()) ;
        reverse(nums.begin() , nums.end()) ;
    }
};


int main(){
    vector<int> nums = {1,2,3,4,5,6,7};
    int k = 3;

    Solution a;
    a.rotate(nums, k);
    
    for(int i = 0; i < nums.size(); i++){
        cout << nums[i] << " ";
    }

    return 0;
}